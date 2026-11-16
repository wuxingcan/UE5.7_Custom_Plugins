// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonEFXExporter.h"

#include "CommonEFXSnapshotV2.h"

#include "AssetRegistry/AssetData.h"
#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "DesktopPlatformModule.h"
#include "IAssetTools.h"
#include "IContentBrowserSingleton.h"
#include "Dom/JsonObject.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_Niagara.h"
#include "FileHelpers.h"
#include "HAL/FileManager.h"
#include "IDesktopPlatform.h"
#include "Logging/LogMacros.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "NiagaraEmitter.h"
#include "NiagaraEmitterHandle.h"
#include "NiagaraGraph.h"
#include "NiagaraNodeAssignment.h"
#include "NiagaraNodeFunctionCall.h"
#include "NiagaraNodeOutput.h"
#include "NiagaraScript.h"
#include "NiagaraScriptSource.h"
#include "NiagaraScriptSourceBase.h"
#include "NiagaraSystem.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UnrealType.h"

DEFINE_LOG_CATEGORY_STATIC(LogCommonEFX, Log, All);

namespace
{
	constexpr int32 LegacySnapshotVersion = 1;

	struct FGraphEntry
	{
		UNiagaraScript* Script = nullptr;
		UNiagaraGraph* Graph = nullptr;
	};

	FString GetUsageName(ENiagaraScriptUsage Usage)
	{
		if (const UEnum* UsageEnum = StaticEnum<ENiagaraScriptUsage>())
		{
			return UsageEnum->GetNameStringByValue(static_cast<int64>(Usage));
		}
		return TEXT("Unknown");
	}

	FString MakeGraphKey(const FGraphEntry& Entry, int32 GraphIndex)
	{
		const UNiagaraScript* Script = Entry.Script;
		if (!Script)
		{
			return FString::Printf(TEXT("Unknown|%d"), GraphIndex);
		}

		return FString::Printf(
			TEXT("%s|%s|%s|%d"),
			*GetUsageName(Script->GetUsage()),
			*Script->GetUsageId().ToString(EGuidFormats::DigitsWithHyphens),
			*Script->GetName(),
			GraphIndex);
	}

	void CollectGraphs(UNiagaraSystem* System, TArray<FGraphEntry>& OutGraphs)
	{
		OutGraphs.Reset();
		if (!System)
		{
			return;
		}

		TSet<UNiagaraGraph*> SeenGraphs;
		auto AddScript = [&OutGraphs, &SeenGraphs](UNiagaraScript* Script, const FGuid& VersionGuid)
		{
			if (!Script)
			{
				return;
			}

			UNiagaraScriptSourceBase* SourceBase = VersionGuid.IsValid() ? Script->GetSource(VersionGuid) : nullptr;
			if (!SourceBase)
			{
				SourceBase = Script->GetLatestSource();
			}

			UNiagaraScriptSource* Source = Cast<UNiagaraScriptSource>(SourceBase);
			UNiagaraGraph* Graph = Source ? Source->NodeGraph.Get() : nullptr;
			if (!Graph || SeenGraphs.Contains(Graph))
			{
				return;
			}

			SeenGraphs.Add(Graph);
			FGraphEntry& Entry = OutGraphs.AddDefaulted_GetRef();
			Entry.Script = Script;
			Entry.Graph = Graph;
		};

		AddScript(System->GetSystemSpawnScript(), FGuid());
		AddScript(System->GetSystemUpdateScript(), FGuid());

		for (const FNiagaraEmitterHandle& Handle : System->GetEmitterHandles())
		{
			if (FVersionedNiagaraEmitterData* EmitterData = Handle.GetEmitterData())
			{
				const FGuid EmitterVersion = Handle.GetInstance().Version;
				EmitterData->ForEachScript([&AddScript, EmitterVersion](UNiagaraScript* Script)
					{
						AddScript(Script, EmitterVersion);
					});
			}
		}
	}

	FString GetStringField(const TSharedPtr<FJsonObject>& Object, const TCHAR* FieldName)
	{
		FString Value;
		if (Object.IsValid())
		{
			Object->TryGetStringField(FieldName, Value);
		}
		return Value;
	}

	bool GetBoolField(const TSharedPtr<FJsonObject>& Object, const TCHAR* FieldName)
	{
		bool bValue = false;
		if (Object.IsValid())
		{
			Object->TryGetBoolField(FieldName, bValue);
		}
		return bValue;
	}

	int32 GetIntField(const TSharedPtr<FJsonObject>& Object, const TCHAR* FieldName)
	{
		double Value = 0.0;
		if (Object.IsValid() && Object->TryGetNumberField(FieldName, Value))
		{
			return static_cast<int32>(Value);
		}
		return INDEX_NONE;
	}

	UEdGraphPin* FindPin(UEdGraphNode* Node, const TSharedPtr<FJsonObject>& PinObject)
	{
		if (!Node)
		{
			return nullptr;
		}

		const FString DirectionString = GetStringField(PinObject, TEXT("Direction"));
		const EEdGraphPinDirection Direction = DirectionString == TEXT("Output") ? EGPD_Output : EGPD_Input;
		const FName PinName(*GetStringField(PinObject, TEXT("Name")));

		if (UEdGraphPin* Pin = Node->FindPin(PinName, Direction))
		{
			return Pin;
		}

		FGuid PersistentGuid;
		if (FGuid::Parse(GetStringField(PinObject, TEXT("PersistentGuid")), PersistentGuid))
		{
			for (UEdGraphPin* Pin : Node->Pins)
			{
				if (Pin && Pin->Direction == Direction && Pin->PersistentGuid == PersistentGuid)
				{
					return Pin;
				}
			}
		}

		return nullptr;
	}

	void ApplyNodeProperties(UEdGraphNode* Node, const TSharedPtr<FJsonObject>& NodeObject)
	{
		const TArray<TSharedPtr<FJsonValue>>* Properties = nullptr;
		if (!NodeObject->TryGetArrayField(TEXT("Properties"), Properties) || !Properties)
		{
			return;
		}

		for (const TSharedPtr<FJsonValue>& Value : *Properties)
		{
			const TSharedPtr<FJsonObject> PropertyObject = Value->AsObject();
			if (!PropertyObject.IsValid())
			{
				continue;
			}

			const FString PropertyName = GetStringField(PropertyObject, TEXT("Name"));
			FProperty* Property = FindFProperty<FProperty>(Node->GetClass(), FName(*PropertyName));
			if (!Property || Property->HasAnyPropertyFlags(CPF_Transient | CPF_Deprecated))
			{
				continue;
			}

			const FString ValueText = GetStringField(PropertyObject, TEXT("Value"));
			Property->ImportText_InContainer(*ValueText, Node, Node, PPF_None);
		}
	}

	void ApplyNodePins(UEdGraphNode* Node, const TSharedPtr<FJsonObject>& NodeObject)
	{
		const TArray<TSharedPtr<FJsonValue>>* Pins = nullptr;
		if (!NodeObject->TryGetArrayField(TEXT("Pins"), Pins) || !Pins)
		{
			return;
		}

		for (const TSharedPtr<FJsonValue>& Value : *Pins)
		{
			const TSharedPtr<FJsonObject> PinObject = Value->AsObject();
			if (!PinObject.IsValid() || GetBoolField(PinObject, TEXT("bLinked")))
			{
				continue;
			}

			FString RecordedDefaultValue;
			if (!PinObject->TryGetStringField(TEXT("DefaultValue"), RecordedDefaultValue))
			{
				continue;
			}

			UEdGraphPin* Pin = FindPin(Node, PinObject);
			if (!Pin || Pin->LinkedTo.Num() > 0 || Pin->bDefaultValueIsIgnored)
			{
				continue;
			}

			if (const UEdGraphSchema_Niagara* Schema = Cast<UEdGraphSchema_Niagara>(Node->GetSchema()))
			{
				Schema->TrySetDefaultValue(*Pin, RecordedDefaultValue, true);
			}
			else
			{
				Pin->DefaultValue = RecordedDefaultValue;
				Node->PinDefaultValueChanged(Pin);
			}
		}
	}

	void ApplyGraph(UNiagaraGraph* Graph, const TSharedPtr<FJsonObject>& GraphObject)
	{
		if (!Graph || !GraphObject.IsValid())
		{
			return;
		}

		Graph->Modify();

		TMap<FGuid, UEdGraphNode*> NodesByGuid;
		for (const TObjectPtr<UEdGraphNode>& NodePtr : Graph->Nodes)
		{
			UEdGraphNode* Node = NodePtr.Get();
			if (Node)
			{
				NodesByGuid.Add(Node->NodeGuid, Node);
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* Nodes = nullptr;
		if (!GraphObject->TryGetArrayField(TEXT("Nodes"), Nodes) || !Nodes)
		{
			return;
		}

		for (const TSharedPtr<FJsonValue>& Value : *Nodes)
		{
			const TSharedPtr<FJsonObject> NodeObject = Value->AsObject();
			if (!NodeObject.IsValid())
			{
				continue;
			}

			UEdGraphNode* Node = nullptr;
			FGuid NodeGuid;
			if (FGuid::Parse(GetStringField(NodeObject, TEXT("Guid")), NodeGuid))
			{
				Node = NodesByGuid.FindRef(NodeGuid);
			}

			if (!Node)
			{
				const int32 NodeIndex = GetIntField(NodeObject, TEXT("Index"));
				if (NodeIndex >= 0 && NodeIndex < Graph->Nodes.Num())
				{
					UEdGraphNode* Candidate = Graph->Nodes[NodeIndex].Get();
					if (Candidate && Candidate->GetClass()->GetPathName() == GetStringField(NodeObject, TEXT("Class")))
					{
						Node = Candidate;
					}
				}
			}

			if (!Node)
			{
				continue;
			}

			Node->Modify();
			ApplyNodeProperties(Node, NodeObject);
			ApplyNodePins(Node, NodeObject);
		}

		Graph->NotifyGraphChanged();
	}

	bool ChooseSaveFile(UNiagaraSystem* System, FString& OutFile)
	{
		IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
		if (!DesktopPlatform || !System)
		{
			return false;
		}

		const FString DefaultDirectory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("CommonEFX"));
		IFileManager::Get().MakeDirectory(*DefaultDirectory, true);

		TArray<FString> SelectedFiles;
		const bool bSelected = DesktopPlatform->SaveFileDialog(
			nullptr,
			TEXT("导出 Niagara 参数"),
			DefaultDirectory,
			FString::Printf(TEXT("%s.niagara.json"), *System->GetName()),
			TEXT("Niagara Parameter Snapshot (*.json)|*.json|All Files (*.*)|*.*"),
			static_cast<uint32>(EFileDialogFlags::None),
			SelectedFiles);

		if (!bSelected || SelectedFiles.Num() == 0)
		{
			return false;
		}

		OutFile = SelectedFiles[0];
		if (FPaths::GetExtension(OutFile).IsEmpty())
		{
			OutFile += TEXT(".json");
		}
		return true;
	}

	bool ChooseOpenFile(FString& OutFile)
	{
		IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
		if (!DesktopPlatform)
		{
			return false;
		}

		const FString DefaultDirectory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("CommonEFX"));
		IFileManager::Get().MakeDirectory(*DefaultDirectory, true);

		TArray<FString> SelectedFiles;
		const bool bSelected = DesktopPlatform->OpenFileDialog(
			nullptr,
			TEXT("导入 Niagara 参数"),
			DefaultDirectory,
			TEXT(""),
			TEXT("Niagara Parameter Snapshot (*.json)|*.json|All Files (*.*)|*.*"),
			static_cast<uint32>(EFileDialogFlags::None),
			SelectedFiles);

		if (!bSelected || SelectedFiles.Num() == 0)
		{
			return false;
		}

		OutFile = SelectedFiles[0];
		return true;
	}
}

bool FCommonEFXExporter::ExportSelectedSystemToFile(FString& OutFile, FString& OutError)
{
	TArray<FAssetData> SelectedAssets;
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);

	UNiagaraSystem* System = nullptr;
	for (const FAssetData& AssetData : SelectedAssets)
	{
		if (AssetData.IsInstanceOf<UNiagaraSystem>())
		{
			System = Cast<UNiagaraSystem>(AssetData.GetAsset());
			if (System)
			{
				break;
			}
		}
	}

	if (!System)
	{
		OutError = TEXT("请在内容浏览器中选择一个 Niagara System 资产。");
		return false;
	}

	return ExportSystemToFileWithDialog(System, OutFile, OutError);
}

bool FCommonEFXExporter::ExportSystemToFileWithDialog(UNiagaraSystem* System, FString& OutFile, FString& OutError)
{
	if (!System)
	{
		OutError = TEXT("未找到要导出的 Niagara System。");
		return false;
	}

	if (!ChooseSaveFile(System, OutFile))
	{
		return false;
	}

	return ExportSystemToFile(System, OutFile, OutError);
}

bool FCommonEFXExporter::ExportSystemToFile(UNiagaraSystem* System, const FString& FileName, FString& OutError)
{
	if (!System)
	{
		OutError = TEXT("未找到要导出的 Niagara System。");
		return false;
	}

	return FCommonEFXSnapshotV2::Export(System, FileName, OutError);
}

bool FCommonEFXExporter::ImportSystemFromFileWithDialog(FString& OutNewAssetPath, FString& OutError, const FString& DestinationPath)
{
	FString FileName;
	if (!ChooseOpenFile(FileName))
	{
		return false;
	}

	UNiagaraSystem* NewSystem = ImportSystemFromFile(FileName, OutError, DestinationPath);
	if (!NewSystem)
	{
		return false;
	}

	OutNewAssetPath = NewSystem->GetPathName();
	return true;
}

UNiagaraSystem* FCommonEFXExporter::ImportSystemFromFile(const FString& FileName, FString& OutError, const FString& DestinationPath)
{
	FString JsonText;
	if (!FFileHelper::LoadFileToString(JsonText, *FileName))
	{
		OutError = FString::Printf(TEXT("读取文件失败：%s"), *FileName);
		return nullptr;
	}

	TSharedPtr<FJsonObject> RootObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);
	if (!FJsonSerializer::Deserialize(Reader, RootObject) || !RootObject.IsValid())
	{
		OutError = TEXT("参数文件格式无效，无法解析 JSON。");
		return nullptr;
	}

	const int32 SnapshotVersion = GetIntField(RootObject, TEXT("Version"));
	if (SnapshotVersion == FCommonEFXSnapshotV2::Version)
	{
		return FCommonEFXSnapshotV2::Import(RootObject, OutError, DestinationPath);
	}

	if (SnapshotVersion != LegacySnapshotVersion)
	{
		OutError = FString::Printf(TEXT("不支持的参数文件版本：%d（当前支持 %d、%d）。"),
			SnapshotVersion, LegacySnapshotVersion, FCommonEFXSnapshotV2::Version);
		return nullptr;
	}

	const FString SourceSystemPath = GetStringField(RootObject, TEXT("SourceSystem"));
	if (SourceSystemPath.IsEmpty())
	{
		OutError = TEXT("参数文件中没有记录原始 Niagara System 路径。");
		return nullptr;
	}

	const TArray<TSharedPtr<FJsonValue>>* GraphValues = nullptr;
	if (!RootObject->TryGetArrayField(TEXT("Graphs"), GraphValues) || !GraphValues || GraphValues->Num() == 0)
	{
		OutError = TEXT("参数文件中没有可还原的 Graphs 数据。");
		return nullptr;
	}

	UNiagaraSystem* SourceSystem = LoadObject<UNiagaraSystem>(nullptr, *SourceSystemPath);
	if (!SourceSystem)
	{
		OutError = FString::Printf(
			TEXT("无法加载参数文件记录的原始 Niagara System：%s\n")
			TEXT("该文件是旧版格式（Version %d），只记录节点参数，无法脱离原资产重建渲染器/材质等数据。\n")
			TEXT("请先从回收站/版本控制恢复原资产，用当前版本插件重新导出为新版格式，之后再删除原资产。"),
			*SourceSystemPath, LegacySnapshotVersion);
		return nullptr;
	}

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	IAssetTools& AssetTools = AssetToolsModule.Get();

	const FString SourcePackageName = FPackageName::ObjectPathToPackageName(SourceSystemPath);
	const FString SourcePackagePath = FPackageName::GetLongPackagePath(SourcePackageName);
	const FString SourceAssetName = FPackageName::GetShortName(SourcePackageName);
	const FString BasePackageName = FString::Printf(TEXT("%s/%s_Restored"), *SourcePackagePath, *SourceAssetName);

	FString UniquePackageName;
	FString UniqueAssetName;
	AssetTools.CreateUniqueAssetName(BasePackageName, TEXT(""), UniquePackageName, UniqueAssetName);

	const FString NewPackagePath = FPackageName::GetLongPackagePath(UniquePackageName);
	UObject* NewObject = AssetTools.DuplicateAsset(UniqueAssetName, NewPackagePath, SourceSystem);
	UNiagaraSystem* NewSystem = Cast<UNiagaraSystem>(NewObject);
	if (!NewSystem)
	{
		OutError = TEXT("复制 Niagara System 失败，无法创建新资产。");
		return nullptr;
	}

	TArray<UPackage*> PackagesToSave;
	if (UPackage* SystemPackage = NewSystem->GetOutermost())
	{
		PackagesToSave.Add(SystemPackage);
	}

	// Duplicating a system keeps its emitter handles pointing at the original emitter assets.
	// Duplicate those emitters as well, otherwise restoring the snapshot would modify the source.
	NewSystem->Modify();
	for (FNiagaraEmitterHandle& Handle : NewSystem->GetEmitterHandles())
	{
		FVersionedNiagaraEmitter Instance = Handle.GetInstance();
		UNiagaraEmitter* Emitter = Instance.Emitter;
		if (!Emitter || Emitter->GetOutermost() == NewSystem->GetOutermost())
		{
			continue;
		}

		const FString BaseEmitterPackageName = FString::Printf(TEXT("%s/%s"), *NewPackagePath, *Emitter->GetName());
		FString UniqueEmitterPackageName;
		FString UniqueEmitterName;
		AssetTools.CreateUniqueAssetName(BaseEmitterPackageName, TEXT(""), UniqueEmitterPackageName, UniqueEmitterName);

		UObject* DuplicatedEmitterObject = AssetTools.DuplicateAsset(
			UniqueEmitterName, FPackageName::GetLongPackagePath(UniqueEmitterPackageName), Emitter);
		UNiagaraEmitter* DuplicatedEmitter = Cast<UNiagaraEmitter>(DuplicatedEmitterObject);
		if (!DuplicatedEmitter)
		{
			UE_LOG(LogCommonEFX, Warning,
				TEXT("Failed to duplicate emitter %s. The restored system still references the source emitter."),
				*Emitter->GetPathName());
			continue;
		}

		Instance.Emitter = DuplicatedEmitter;
		Handle.GetInstance() = Instance;

		if (UPackage* EmitterPackage = DuplicatedEmitter->GetOutermost())
		{
			PackagesToSave.Add(EmitterPackage);
		}
	}

	TArray<FGraphEntry> CurrentGraphs;
	CollectGraphs(NewSystem, CurrentGraphs);

	TMap<FString, int32> GraphKeyToIndex;
	for (int32 GraphIndex = 0; GraphIndex < CurrentGraphs.Num(); ++GraphIndex)
	{
		GraphKeyToIndex.Add(MakeGraphKey(CurrentGraphs[GraphIndex], GraphIndex), GraphIndex);
	}

	int32 AppliedGraphs = 0;
	for (const TSharedPtr<FJsonValue>& GraphValue : *GraphValues)
	{
		const TSharedPtr<FJsonObject> GraphObject = GraphValue->AsObject();
		if (!GraphObject.IsValid())
		{
			continue;
		}

		int32 CurrentGraphIndex = INDEX_NONE;
		const int32 RecordedIndex = GetIntField(GraphObject, TEXT("Index"));
		if (RecordedIndex >= 0 && RecordedIndex < CurrentGraphs.Num())
		{
			const FString RecordedUsage = GetStringField(GraphObject, TEXT("Usage"));
			const FString CurrentUsage = GetUsageName(CurrentGraphs[RecordedIndex].Script->GetUsage());
			if (RecordedUsage == CurrentUsage)
			{
				CurrentGraphIndex = RecordedIndex;
			}
		}

		if (CurrentGraphIndex == INDEX_NONE)
		{
			if (const int32* FoundIndex = GraphKeyToIndex.Find(GetStringField(GraphObject, TEXT("Key"))))
			{
				CurrentGraphIndex = *FoundIndex;
			}
		}

		if (CurrentGraphIndex == INDEX_NONE)
		{
			UE_LOG(LogCommonEFX, Warning, TEXT("Skipping graph that no longer exists in the duplicated system: %s"), *GetStringField(GraphObject, TEXT("ScriptPath")));
			continue;
		}

		ApplyGraph(CurrentGraphs[CurrentGraphIndex].Graph, GraphObject);
		++AppliedGraphs;
	}

	NewSystem->RequestCompile(false);
	NewSystem->MarkPackageDirty();

	if (PackagesToSave.Num() > 0)
	{
		const FEditorFileUtils::EPromptReturnCode SaveResult =
			FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, false, false);
		if (SaveResult != FEditorFileUtils::PR_Success)
		{
			UE_LOG(LogCommonEFX, Warning, TEXT("The restored asset could not be saved: %s"), *NewSystem->GetPathName());
		}
	}

	UE_LOG(LogCommonEFX, Display, TEXT("Restored Niagara snapshot into %s | graphs applied=%d"), *NewSystem->GetPathName(), AppliedGraphs);
	return NewSystem;
}

namespace
{
	UNiagaraGraph* GetGraphFromScript(UNiagaraScript* Script, const FGuid& VersionGuid = FGuid())
	{
		if (!Script)
		{
			return nullptr;
		}

		UNiagaraScriptSourceBase* SourceBase = VersionGuid.IsValid() ? Script->GetSource(VersionGuid) : nullptr;
		if (!SourceBase)
		{
			SourceBase = Script->GetLatestSource();
		}

		UNiagaraScriptSource* Source = Cast<UNiagaraScriptSource>(SourceBase);
		return Source ? Source->NodeGraph.Get() : nullptr;
	}

	FString GetCompileStatusName(ENiagaraScriptCompileStatus Status)
	{
		if (const UEnum* StatusEnum = StaticEnum<ENiagaraScriptCompileStatus>())
		{
			return StatusEnum->GetNameStringByValue(static_cast<int64>(Status));
		}
		return FString::FromInt(static_cast<int32>(Status));
	}

	/** Counts the module nodes reachable from an output node through pin links (the stack chain). */
	int32 CountReachableModules(const UNiagaraNodeOutput* Output)
	{
		if (!Output)
		{
			return 0;
		}

		TSet<const UEdGraphNode*> Visited;
		TArray<const UEdGraphNode*> Pending;
		Pending.Add(Output);

		int32 ModuleCount = 0;
		while (Pending.Num() > 0)
		{
			const UEdGraphNode* Node = Pending.Pop(EAllowShrinking::No);
			if (!Node || Visited.Contains(Node))
			{
				continue;
			}
			Visited.Add(Node);

			for (const UEdGraphPin* Pin : Node->GetAllPins())
			{
				if (!Pin)
				{
					continue;
				}

				for (const UEdGraphPin* LinkedPin : Pin->LinkedTo)
				{
					const UEdGraphNode* LinkedNode = LinkedPin ? LinkedPin->GetOwningNode() : nullptr;
					if (!LinkedNode || Visited.Contains(LinkedNode))
					{
						continue;
					}

					if (Cast<UNiagaraNodeFunctionCall>(LinkedNode))
					{
						++ModuleCount;
					}
					Pending.Add(LinkedNode);
				}
			}
		}

		return ModuleCount;
	}

	void LogGraphContents(UNiagaraGraph* Graph, const FString& Label)
	{
		if (!Graph)
		{
			UE_LOG(LogCommonEFX, Warning, TEXT("%s | graph=<null>"), *Label);
			return;
		}

		int32 FunctionCalls = 0;
		int32 NullScripts = 0;
		int32 Assignments = 0;
		int32 NullAssignments = 0;
		int32 Outputs = 0;
		int32 EmitterNodes = 0;

		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (!Node)
			{
				continue;
			}

			// UNiagaraNodeAssignment derives from UNiagaraNodeFunctionCall, so test it first.
			if (const UNiagaraNodeAssignment* Assignment = Cast<UNiagaraNodeAssignment>(Node))
			{
				++Assignments;
				if (!Assignment->FunctionScript)
				{
					++NullAssignments;
				}
			}
			else if (const UNiagaraNodeFunctionCall* FunctionCall = Cast<UNiagaraNodeFunctionCall>(Node))
			{
				++FunctionCalls;
				if (!FunctionCall->FunctionScript)
				{
					++NullScripts;
				}
			}

			if (Cast<UNiagaraNodeOutput>(Node))
			{
				++Outputs;
			}

			if (Node->GetClass()->GetName() == TEXT("NiagaraNodeEmitter"))
			{
				++EmitterNodes;
			}
		}

		TArray<FString> Chains;
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (const UNiagaraNodeOutput* Output = Cast<UNiagaraNodeOutput>(Node))
			{
				Chains.Add(FString::Printf(TEXT("%s=%d"), *GetUsageName(Output->GetUsage()), CountReachableModules(Output)));
			}
		}

		UE_LOG(LogCommonEFX, Display,
			TEXT("%s | nodes=%d outputs=%d modules=%d nullScripts=%d assignments=%d nullAssignments=%d emitterNodes=%d scriptVars=%d chains[%s]"),
			*Label, Graph->Nodes.Num(), Outputs, FunctionCalls, NullScripts, Assignments, NullAssignments, EmitterNodes,
			Graph->GetAllMetaData().Num(), *FString::Join(Chains, TEXT(",")));
	}
}

void FCommonEFXExporter::LogSystemContents(UNiagaraSystem* System, const FString& Label)
{
	if (!System)
	{
		UE_LOG(LogCommonEFX, Warning, TEXT("%s | system=<null>"), *Label);
		return;
	}

	TArray<FNiagaraVariable> ExposedParameters;
	System->GetExposedParameters().GetParameters(ExposedParameters);

	UE_LOG(LogCommonEFX, Display,
		TEXT("%s | %s | handles=%d userParams=%d effectType=%s readyToRun=%d"),
		*Label, *System->GetPathName(), System->GetEmitterHandles().Num(), ExposedParameters.Num(),
		System->GetEffectType() ? *System->GetEffectType()->GetPathName() : TEXT("None"),
		System->IsReadyToRun() ? 1 : 0);

	LogGraphContents(GetGraphFromScript(System->GetSystemSpawnScript()), FString::Printf(TEXT("%s/SystemGraph"), *Label));

	for (const FNiagaraEmitterHandle& Handle : System->GetEmitterHandles())
	{
		const FVersionedNiagaraEmitterData* EmitterData = Handle.GetEmitterData();
		if (!EmitterData)
		{
			UE_LOG(LogCommonEFX, Warning, TEXT("%s/%s | emitter data missing for version %s"),
				*Label, *Handle.GetName().ToString(), *Handle.GetInstance().Version.ToString());
			continue;
		}

		const UNiagaraEmitter* Emitter = Handle.GetInstance().Emitter;
		UE_LOG(LogCommonEFX, Display,
			TEXT("%s/%s | enabled=%d inheritable=%d version=%s renderers=%d eventHandlers=%d simStages=%d"),
			*Label, *Handle.GetName().ToString(), Handle.GetIsEnabled() ? 1 : 0, Emitter && Emitter->bIsInheritable ? 1 : 0,
			*Handle.GetInstance().Version.ToString(), EmitterData->GetRenderers().Num(),
			EmitterData->EventHandlerScriptProps.Num(), EmitterData->GetSimulationStages().Num());

		EmitterData->ForEachScript([Label, &Handle](UNiagaraScript* Script)
			{
				if (!Script)
				{
					return;
				}

				UE_LOG(LogCommonEFX, Display, TEXT("%s/%s/%s | usage=%s compile=%s synced=%d rapid=%d"),
					*Label, *Handle.GetName().ToString(), *Script->GetName(), *GetUsageName(Script->GetUsage()),
					*GetCompileStatusName(Script->GetLastCompileStatus()),
					Script->AreScriptAndSourceSynchronized(Handle.GetInstance().Version) ? 1 : 0,
					Script->RapidIterationParameters.Num());
			});

		LogGraphContents(GetGraphFromScript(EmitterData->EmitterUpdateScriptProps.Script, Handle.GetInstance().Version),
			FString::Printf(TEXT("%s/%s/Graph"), *Label, *Handle.GetName().ToString()));
	}
}

bool FCommonEFXExporter::RunRoundTripCheck(const FString& AssetPath, const FString& OutputDirectory, FString& OutSourceFile, FString& OutRebuiltFile, FString& OutError)
{
	FString ObjectPath = AssetPath;
	if (!ObjectPath.Contains(TEXT(".")))
	{
		ObjectPath = FString::Printf(TEXT("%s.%s"), *AssetPath, *FPaths::GetBaseFilename(AssetPath));
	}

	UNiagaraSystem* Source = LoadObject<UNiagaraSystem>(nullptr, *ObjectPath);
	if (!Source)
	{
		OutError = FString::Printf(TEXT("无法加载 Niagara System：%s"), *ObjectPath);
		return false;
	}

	IFileManager::Get().MakeDirectory(*OutputDirectory, true);

	const FString BaseName = FPaths::GetBaseFilename(AssetPath);
	OutSourceFile = FPaths::Combine(OutputDirectory, FString::Printf(TEXT("%s.src.json"), *BaseName));
	OutRebuiltFile = FPaths::Combine(OutputDirectory, FString::Printf(TEXT("%s.rebuilt.json"), *BaseName));

	LogSystemContents(Source, TEXT("RoundTrip/Source"));

	if (!ExportSystemToFile(Source, OutSourceFile, OutError))
	{
		return false;
	}

	UNiagaraSystem* Rebuilt = ImportSystemFromFile(OutSourceFile, OutError);
	if (!Rebuilt)
	{
		return false;
	}

	LogSystemContents(Rebuilt, TEXT("RoundTrip/Rebuilt"));
	return ExportSystemToFile(Rebuilt, OutRebuiltFile, OutError);
}
