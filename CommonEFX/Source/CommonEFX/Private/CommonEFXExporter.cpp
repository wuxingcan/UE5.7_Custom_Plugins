// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonEFXExporter.h"

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
	constexpr int32 SnapshotVersion = 1;

	struct FGraphEntry
	{
		UNiagaraScript* Script = nullptr;
		UNiagaraGraph* Graph = nullptr;
	};

	struct FExportStats
	{
		int32 Graphs = 0;
		int32 Nodes = 0;
		int32 Pins = 0;
		int32 ModifiedPins = 0;
		int32 Properties = 0;
		int32 ModifiedProperties = 0;
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

	bool ShouldSkipProperty(const FProperty* Property)
	{
		static const TSet<FName> SkipNames =
		{
			TEXT("Pins"),
			TEXT("NodePosX"),
			TEXT("NodePosY"),
			TEXT("NodeWidth"),
			TEXT("NodeHeight"),
			TEXT("AdvancedPinDisplay"),
			TEXT("bHasCompilerMessage"),
			TEXT("ErrorType"),
			TEXT("ErrorMsg"),
			TEXT("bCommentBubbleVisible"),
			TEXT("bCommentBubblePinned"),
		};

		if (!Property)
		{
			return true;
		}

		if (SkipNames.Contains(Property->GetFName()))
		{
			return true;
		}

		if (Property->HasAnyPropertyFlags(CPF_Transient | CPF_Deprecated))
		{
			return true;
		}

		return (Property->PropertyFlags & CPF_Edit) == 0;
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

	TSharedPtr<FJsonObject> ExportPin(UEdGraphPin* Pin, FExportStats& Stats)
	{
		TSharedPtr<FJsonObject> PinObject = MakeShared<FJsonObject>();
		if (!Pin)
		{
			return PinObject;
		}

		const bool bLinked = Pin->LinkedTo.Num() > 0;
		const bool bModified = !bLinked && !Pin->bDefaultValueIsIgnored && Pin->DefaultValue != Pin->AutogeneratedDefaultValue;

		PinObject->SetStringField(TEXT("Name"), Pin->PinName.ToString());
		PinObject->SetStringField(TEXT("Direction"), Pin->Direction == EGPD_Input ? TEXT("Input") : TEXT("Output"));
		PinObject->SetStringField(TEXT("PersistentGuid"), Pin->PersistentGuid.ToString(EGuidFormats::DigitsWithHyphens));
		PinObject->SetStringField(TEXT("DefaultValue"), Pin->DefaultValue);
		PinObject->SetStringField(TEXT("AutogeneratedDefaultValue"), Pin->AutogeneratedDefaultValue);
		const UObject* PinDefaultObject = Pin->DefaultObject.Get();
		PinObject->SetStringField(TEXT("DefaultObject"), PinDefaultObject ? PinDefaultObject->GetPathName() : FString());
		PinObject->SetBoolField(TEXT("bModified"), bModified);
		PinObject->SetBoolField(TEXT("bLinked"), bLinked);
		PinObject->SetBoolField(TEXT("bDefaultValueIsIgnored"), Pin->bDefaultValueIsIgnored != 0);
		PinObject->SetBoolField(TEXT("bOrphanedPin"), Pin->bOrphanedPin != 0);

		PinObject->SetStringField(TEXT("Category"), Pin->PinType.PinCategory.ToString());
		PinObject->SetStringField(TEXT("SubCategory"), Pin->PinType.PinSubCategory.ToString());
		PinObject->SetStringField(TEXT("SubCategoryObject"), Pin->PinType.PinSubCategoryObject.IsValid() ? Pin->PinType.PinSubCategoryObject->GetPathName() : FString());
		PinObject->SetStringField(TEXT("ContainerType"), StaticEnum<EPinContainerType>()->GetNameStringByValue(static_cast<int64>(Pin->PinType.ContainerType)));
		PinObject->SetBoolField(TEXT("bIsReference"), Pin->PinType.bIsReference != 0);
		PinObject->SetBoolField(TEXT("bIsConst"), Pin->PinType.bIsConst != 0);

		TArray<TSharedPtr<FJsonValue>> Links;
		for (UEdGraphPin* LinkedPin : Pin->LinkedTo)
		{
			if (!LinkedPin)
			{
				continue;
			}

			const UEdGraphNode* LinkedNode = LinkedPin->GetOwningNodeUnchecked();
			TSharedPtr<FJsonObject> LinkObject = MakeShared<FJsonObject>();
			LinkObject->SetStringField(TEXT("NodeGuid"), LinkedNode ? LinkedNode->NodeGuid.ToString(EGuidFormats::DigitsWithHyphens) : FString());
			LinkObject->SetStringField(TEXT("PinName"), LinkedPin->PinName.ToString());
			Links.Add(MakeShared<FJsonValueObject>(LinkObject));
		}
		PinObject->SetArrayField(TEXT("Links"), Links);

		++Stats.Pins;
		if (bModified)
		{
			++Stats.ModifiedPins;
		}

		return PinObject;
	}

	TSharedPtr<FJsonObject> ExportNode(UEdGraphNode* Node, int32 NodeIndex, FExportStats& Stats)
	{
		TSharedPtr<FJsonObject> NodeObject = MakeShared<FJsonObject>();
		if (!Node)
		{
			return NodeObject;
		}

		NodeObject->SetStringField(TEXT("Guid"), Node->NodeGuid.ToString(EGuidFormats::DigitsWithHyphens));
		NodeObject->SetStringField(TEXT("Class"), Node->GetClass()->GetPathName());
		NodeObject->SetStringField(TEXT("Name"), Node->GetName());
		NodeObject->SetNumberField(TEXT("Index"), NodeIndex);

		TArray<TSharedPtr<FJsonValue>> Properties;
		UObject* CDO = Node->GetClass()->GetDefaultObject();
		for (TFieldIterator<FProperty> It(Node->GetClass()); It; ++It)
		{
			FProperty* Property = *It;
			if (ShouldSkipProperty(Property))
			{
				continue;
			}

			FString Value;
			FString DefaultValue;
			Property->ExportText_InContainer(0, Value, Node, Node, Node, PPF_None);
			if (CDO)
			{
				Property->ExportText_InContainer(0, DefaultValue, CDO, CDO, CDO, PPF_None);
			}

			const bool bModified = Value != DefaultValue;

			TSharedPtr<FJsonObject> PropertyObject = MakeShared<FJsonObject>();
			PropertyObject->SetStringField(TEXT("Name"), Property->GetName());
			PropertyObject->SetStringField(TEXT("Type"), Property->GetCPPType());
			PropertyObject->SetStringField(TEXT("Value"), Value);
			PropertyObject->SetStringField(TEXT("DefaultValue"), DefaultValue);
			PropertyObject->SetBoolField(TEXT("bModified"), bModified);
			Properties.Add(MakeShared<FJsonValueObject>(PropertyObject));

			++Stats.Properties;
			if (bModified)
			{
				++Stats.ModifiedProperties;
			}
		}
		NodeObject->SetArrayField(TEXT("Properties"), Properties);

		TArray<TSharedPtr<FJsonValue>> Pins;
		for (UEdGraphPin* Pin : Node->Pins)
		{
			Pins.Add(MakeShared<FJsonValueObject>(ExportPin(Pin, Stats)));
		}
		NodeObject->SetArrayField(TEXT("Pins"), Pins);

		++Stats.Nodes;
		return NodeObject;
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

	TArray<FGraphEntry> Graphs;
	CollectGraphs(System, Graphs);

	FExportStats Stats;
	Stats.Graphs = Graphs.Num();

	TSharedRef<FJsonObject> RootObject = MakeShared<FJsonObject>();
	RootObject->SetNumberField(TEXT("Version"), SnapshotVersion);
	RootObject->SetStringField(TEXT("SourceSystem"), System->GetPathName());
	RootObject->SetStringField(TEXT("SourceSystemClass"), System->GetClass()->GetPathName());
	RootObject->SetStringField(TEXT("ExportedAt"), FDateTime::UtcNow().ToIso8601());

	TArray<TSharedPtr<FJsonValue>> GraphValues;
	GraphValues.Reserve(Graphs.Num());

	for (int32 GraphIndex = 0; GraphIndex < Graphs.Num(); ++GraphIndex)
	{
		const FGraphEntry& Entry = Graphs[GraphIndex];
		TSharedPtr<FJsonObject> GraphObject = MakeShared<FJsonObject>();
		GraphObject->SetNumberField(TEXT("Index"), GraphIndex);
		GraphObject->SetStringField(TEXT("Key"), MakeGraphKey(Entry, GraphIndex));
		GraphObject->SetStringField(TEXT("ScriptPath"), Entry.Script ? Entry.Script->GetPathName() : FString());
		GraphObject->SetStringField(TEXT("ScriptName"), Entry.Script ? Entry.Script->GetName() : FString());
		GraphObject->SetStringField(TEXT("Usage"), Entry.Script ? GetUsageName(Entry.Script->GetUsage()) : FString());
		GraphObject->SetStringField(TEXT("UsageId"), Entry.Script ? Entry.Script->GetUsageId().ToString(EGuidFormats::DigitsWithHyphens) : FString());
		GraphObject->SetStringField(TEXT("GraphPath"), Entry.Graph->GetPathName());

		TArray<TSharedPtr<FJsonValue>> NodeValues;
		NodeValues.Reserve(Entry.Graph->Nodes.Num());
		for (int32 NodeIndex = 0; NodeIndex < Entry.Graph->Nodes.Num(); ++NodeIndex)
		{
			UEdGraphNode* Node = Entry.Graph->Nodes[NodeIndex].Get();
			if (Node)
			{
				NodeValues.Add(MakeShared<FJsonValueObject>(ExportNode(Node, NodeIndex, Stats)));
			}
		}
		GraphObject->SetArrayField(TEXT("Nodes"), NodeValues);
		GraphValues.Add(MakeShared<FJsonValueObject>(GraphObject));
	}

	RootObject->SetArrayField(TEXT("Graphs"), GraphValues);

	FString JsonText;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonText);
	if (!FJsonSerializer::Serialize(RootObject, Writer))
	{
		OutError = TEXT("序列化 Niagara 参数失败。");
		return false;
	}

	const FString Directory = FPaths::GetPath(FileName);
	if (!Directory.IsEmpty())
	{
		IFileManager::Get().MakeDirectory(*Directory, true);
	}

	if (!FFileHelper::SaveStringToFile(JsonText, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		OutError = FString::Printf(TEXT("写入文件失败：%s"), *FileName);
		return false;
	}

	UE_LOG(LogCommonEFX, Display,
		TEXT("Exported Niagara snapshot: %s | graphs=%d nodes=%d pins=%d modifiedPins=%d properties=%d modifiedProperties=%d"),
		*FileName, Stats.Graphs, Stats.Nodes, Stats.Pins, Stats.ModifiedPins, Stats.Properties, Stats.ModifiedProperties);

	return true;
}

bool FCommonEFXExporter::ImportSystemFromFileWithDialog(FString& OutNewAssetPath, FString& OutError)
{
	FString FileName;
	if (!ChooseOpenFile(FileName))
	{
		return false;
	}

	UNiagaraSystem* NewSystem = ImportSystemFromFile(FileName, OutError);
	if (!NewSystem)
	{
		return false;
	}

	OutNewAssetPath = NewSystem->GetPathName();
	return true;
}

UNiagaraSystem* FCommonEFXExporter::ImportSystemFromFile(const FString& FileName, FString& OutError)
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

	if (GetIntField(RootObject, TEXT("Version")) != SnapshotVersion)
	{
		OutError = FString::Printf(TEXT("不支持的参数文件版本：%d（当前支持 %d）。"),
			GetIntField(RootObject, TEXT("Version")), SnapshotVersion);
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
		OutError = FString::Printf(TEXT("无法加载参数文件记录的原始 Niagara System：%s"), *SourceSystemPath);
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
