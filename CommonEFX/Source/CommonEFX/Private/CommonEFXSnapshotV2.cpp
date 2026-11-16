// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonEFXSnapshotV2.h"

#include "AssetToolsModule.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"
#include "Factories.h"
#include "FileHelpers.h"
#include "HAL/FileManager.h"
#include "IAssetTools.h"
#include "Misc/App.h"
#include "Misc/Base64.h"
#include "Misc/Char.h"
#include "Misc/DateTime.h"
#include "Misc/EngineVersion.h"
#include "Misc/FileHelper.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "NiagaraParameterMapHistory.h"
#include "NiagaraDataInterface.h"
#include "NiagaraTypes.h"
#include "NiagaraEffectType.h"
#include "NiagaraEmitter.h"
#include "NiagaraEmitterFactoryNew.h"
#include "NiagaraEmitterHandle.h"
#include "NiagaraGraph.h"
#include "NiagaraNodeAssignment.h"
#include "NiagaraNodeFunctionCall.h"
#include "NiagaraNodeInput.h"
#include "NiagaraNodeOutput.h"
#include "NiagaraOverviewNode.h"
#include "NiagaraParameterStore.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraScript.h"
#include "NiagaraScriptSource.h"
#include "NiagaraScriptSourceBase.h"
#include "NiagaraScriptVariable.h"
#include "NiagaraSimulationStageBase.h"
#include "NiagaraSystem.h"
#include "NiagaraSystemEditorData.h"
#include "NiagaraSystemFactoryNew.h"
#include "NiagaraUserRedirectionParameterStore.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UnrealType.h"
#include "ViewModels/Stack/NiagaraParameterHandle.h"
#include "NiagaraStackFunctionInputBinder.h"
#include "ViewModels/Stack/NiagaraStackGraphUtilities.h"

DEFINE_LOG_CATEGORY_STATIC(LogCommonEFXSnapshotV2, Log, All);

namespace
{
	// ---------------------------------------------------------------------------
	// JSON helpers
	// ---------------------------------------------------------------------------

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
		return 0;
	}

	FGuid GetGuidField(const TSharedPtr<FJsonObject>& Object, const TCHAR* FieldName)
	{
		FGuid Value;
		FGuid::Parse(GetStringField(Object, FieldName), Value);
		return Value;
	}

	TSharedPtr<FJsonObject> GetObjectField(const TSharedPtr<FJsonObject>& Object, const TCHAR* FieldName)
	{
		const TSharedPtr<FJsonObject>* Found = nullptr;
		if (Object.IsValid() && Object->TryGetObjectField(FieldName, Found) && Found)
		{
			return *Found;
		}
		return nullptr;
	}

	const TArray<TSharedPtr<FJsonValue>>* GetArrayField(const TSharedPtr<FJsonObject>& Object, const TCHAR* FieldName)
	{
		const TArray<TSharedPtr<FJsonValue>>* Found = nullptr;
		if (Object.IsValid())
		{
			Object->TryGetArrayField(FieldName, Found);
		}
		return Found;
	}

	FString MakeGuidString(const FGuid& Guid)
	{
		return Guid.IsValid() ? Guid.ToString(EGuidFormats::DigitsWithHyphens) : FString();
	}

	bool IsUserParameterVariable(const FNiagaraVariable& Variable)
	{
		return Variable.GetName().ToString().StartsWith(TEXT("User."));
	}

	// ---------------------------------------------------------------------------
	// Reflection helpers
	// ---------------------------------------------------------------------------

	bool ShouldExportProperty(const FProperty* Property, const TSet<FName>& SkipNames, bool bRequireEdit)
	{
		if (!Property)
		{
			return false;
		}

		if (SkipNames.Contains(Property->GetFName()))
		{
			return false;
		}

		if (Property->HasAnyPropertyFlags(CPF_Transient | CPF_Deprecated | CPF_DuplicateTransient))
		{
			return false;
		}

		if (bRequireEdit && !Property->HasAnyPropertyFlags(CPF_Edit))
		{
			return false;
		}

		// Instanced sub-objects need dedicated handling; the JSON stores asset paths for hard references only.
		if (Property->HasAnyPropertyFlags(CPF_InstancedReference | CPF_ContainsInstancedReference))
		{
			return false;
		}

		return true;
	}

	void ExportProperty(const FProperty* Property, const void* ValuePtr, UObject* Parent, TArray<TSharedPtr<FJsonValue>>& OutProperties, FString& OutValue)
	{
		OutValue.Reset();
		Property->ExportText_InContainer(0, OutValue, ValuePtr, ValuePtr, Parent, PPF_None);
	}

	void ExportPropertiesFromObject(
		UObject* Object,
		const TSet<FName>& SkipNames,
		bool bRequireEdit,
		TArray<TSharedPtr<FJsonValue>>& OutProperties)
	{
		if (!Object)
		{
			return;
		}

		for (TFieldIterator<FProperty> It(Object->GetClass()); It; ++It)
		{
			FProperty* Property = *It;
			if (!ShouldExportProperty(Property, SkipNames, bRequireEdit))
			{
				continue;
			}

			FString Value;
			ExportProperty(Property, Object, Object, OutProperties, Value);

			TSharedPtr<FJsonObject> PropertyObject = MakeShared<FJsonObject>();
			PropertyObject->SetStringField(TEXT("Name"), Property->GetName());
			PropertyObject->SetStringField(TEXT("Type"), Property->GetCPPType());
			PropertyObject->SetStringField(TEXT("Value"), Value);
			OutProperties.Add(MakeShared<FJsonValueObject>(PropertyObject));
		}
	}

	void ExportPropertiesFromStruct(
		const UStruct* Struct,
		const void* ValuePtr,
		UObject* Parent,
		const TSet<FName>& SkipNames,
		bool bRequireEdit,
		TArray<TSharedPtr<FJsonValue>>& OutProperties)
	{
		if (!Struct || !ValuePtr)
		{
			return;
		}

		for (TFieldIterator<FProperty> It(Struct); It; ++It)
		{
			FProperty* Property = *It;
			if (!ShouldExportProperty(Property, SkipNames, bRequireEdit))
			{
				continue;
			}

			FString Value;
			ExportProperty(Property, ValuePtr, Parent, OutProperties, Value);

			TSharedPtr<FJsonObject> PropertyObject = MakeShared<FJsonObject>();
			PropertyObject->SetStringField(TEXT("Name"), Property->GetName());
			PropertyObject->SetStringField(TEXT("Type"), Property->GetCPPType());
			PropertyObject->SetStringField(TEXT("Value"), Value);
			OutProperties.Add(MakeShared<FJsonValueObject>(PropertyObject));
		}
	}

	FString NormalizeObjectPathText(const FString& InText)
	{
		FString Text = InText.TrimStartAndEnd();

		// ExportText may wrap object paths as Class'/Game/Asset.Asset' or '/Game/Asset.Asset'.
		int32 QuoteStart = INDEX_NONE;
		if (Text.FindChar(TEXT('\''), QuoteStart))
		{
			int32 QuoteEnd = INDEX_NONE;
			if (Text.FindLastChar(TEXT('\''), QuoteEnd) && QuoteEnd > QuoteStart)
			{
				Text = Text.Mid(QuoteStart + 1, QuoteEnd - QuoteStart - 1);
			}
		}

		return Text;
	}

	UObject* LoadObjectFromExportText(const FString& ValueText)
	{
		const FString ObjectPath = NormalizeObjectPathText(ValueText);
		if (ObjectPath.IsEmpty() || ObjectPath.Equals(TEXT("None"), ESearchCase::IgnoreCase))
		{
			return nullptr;
		}

		return LoadObject<UObject>(nullptr, *ObjectPath);
	}

	void RecordMissingObject(const FProperty* Property, const void* ValuePtr, const FString& Context, const FString& Value, TArray<FString>& OutMissingAssets)
	{
		const FObjectPropertyBase* ObjectProperty = CastField<FObjectPropertyBase>(Property);
		if (!ObjectProperty || Value.IsEmpty())
		{
			return;
		}

		const FString ObjectPath = NormalizeObjectPathText(Value);
		if (ObjectPath.IsEmpty() || ObjectPath.Equals(TEXT("None"), ESearchCase::IgnoreCase))
		{
			return;
		}

		if (ObjectProperty->GetObjectPropertyValue_InContainer(ValuePtr) == nullptr)
		{
			OutMissingAssets.Add(FString::Printf(TEXT("%s:%s=%s"), *Context, *Property->GetName(), *Value));
		}
	}

	void ResolveObjectPropertyAfterImport(FProperty* Property, void* ValuePtr, const FString& ValueText)
	{
		FObjectPropertyBase* ObjectProperty = CastField<FObjectPropertyBase>(Property);
		if (!ObjectProperty)
		{
			return;
		}

		if (ObjectProperty->GetObjectPropertyValue_InContainer(ValuePtr) != nullptr)
		{
			return;
		}

		if (UObject* Loaded = LoadObjectFromExportText(ValueText))
		{
			ObjectProperty->SetObjectPropertyValue_InContainer(ValuePtr, Loaded);
		}
	}

	void ImportPropertiesIntoObject(
		UObject* Object,
		const TArray<TSharedPtr<FJsonValue>>* Properties,
		const FString& Context,
		TArray<FString>& OutMissingAssets,
		const TSet<FName>& SkipNames = TSet<FName>())
	{
		if (!Object || !Properties)
		{
			return;
		}

		for (const TSharedPtr<FJsonValue>& Value : *Properties)
		{
			const TSharedPtr<FJsonObject> PropertyObject = Value.IsValid() ? Value->AsObject() : nullptr;
			if (!PropertyObject.IsValid())
			{
				continue;
			}

			const FString PropertyName = GetStringField(PropertyObject, TEXT("Name"));
			FProperty* Property = FindFProperty<FProperty>(Object->GetClass(), FName(*PropertyName));
			if (!Property || SkipNames.Contains(Property->GetFName()) || Property->HasAnyPropertyFlags(CPF_Transient | CPF_Deprecated))
			{
				continue;
			}

			const FString ValueText = GetStringField(PropertyObject, TEXT("Value"));
			Property->ImportText_InContainer(*ValueText, Object, Object, PPF_None);
			ResolveObjectPropertyAfterImport(Property, Object, ValueText);
			RecordMissingObject(Property, Object, Context, ValueText, OutMissingAssets);
		}
	}

	void ImportPropertiesIntoStruct(
		void* ValuePtr,
		const UStruct* Struct,
		UObject* Parent,
		const TArray<TSharedPtr<FJsonValue>>* Properties,
		const FString& Context,
		TArray<FString>& OutMissingAssets,
		const TSet<FName>& SkipNames = TSet<FName>())
	{
		if (!ValuePtr || !Struct || !Properties)
		{
			return;
		}

		for (const TSharedPtr<FJsonValue>& Value : *Properties)
		{
			const TSharedPtr<FJsonObject> PropertyObject = Value.IsValid() ? Value->AsObject() : nullptr;
			if (!PropertyObject.IsValid())
			{
				continue;
			}

			const FString PropertyName = GetStringField(PropertyObject, TEXT("Name"));
			FProperty* Property = FindFProperty<FProperty>(Struct, FName(*PropertyName));
			if (!Property || SkipNames.Contains(Property->GetFName()) || Property->HasAnyPropertyFlags(CPF_Transient | CPF_Deprecated))
			{
				continue;
			}

			const FString ValueText = GetStringField(PropertyObject, TEXT("Value"));
			Property->ImportText_InContainer(*ValueText, ValuePtr, Parent, PPF_None);
			ResolveObjectPropertyAfterImport(Property, ValuePtr, ValueText);
			RecordMissingObject(Property, ValuePtr, Context, ValueText, OutMissingAssets);
		}
	}

	// ---------------------------------------------------------------------------
	// Niagara type helpers
	// ---------------------------------------------------------------------------

	TSharedPtr<FJsonObject> ExportType(const FNiagaraTypeDefinition& Type)
	{
		TSharedPtr<FJsonObject> TypeObject = MakeShared<FJsonObject>();
		TypeObject->SetStringField(TEXT("Struct"), Type.GetStruct() ? Type.GetStruct()->GetPathName() : FString());
		TypeObject->SetStringField(TEXT("Class"), Type.GetClass() ? Type.GetClass()->GetPathName() : FString());
		TypeObject->SetStringField(TEXT("Enum"), Type.GetEnum() ? Type.GetEnum()->GetPathName() : FString());
		return TypeObject;
	}

	FNiagaraTypeDefinition ResolveType(const TSharedPtr<FJsonObject>& TypeObject, TArray<FString>& OutMissingAssets)
	{
		if (!TypeObject.IsValid())
		{
			return FNiagaraTypeDefinition();
		}

		const FString EnumPath = GetStringField(TypeObject, TEXT("Enum"));
		if (!EnumPath.IsEmpty())
		{
			if (UEnum* Enum = LoadObject<UEnum>(nullptr, *EnumPath))
			{
				return FNiagaraTypeDefinition(Enum);
			}
			OutMissingAssets.Add(EnumPath);
			return FNiagaraTypeDefinition();
		}

		const FString ClassPath = GetStringField(TypeObject, TEXT("Class"));
		if (!ClassPath.IsEmpty())
		{
			if (UClass* Class = LoadObject<UClass>(nullptr, *ClassPath))
			{
				return FNiagaraTypeDefinition(Class);
			}
			OutMissingAssets.Add(ClassPath);
			return FNiagaraTypeDefinition();
		}

		const FString StructPath = GetStringField(TypeObject, TEXT("Struct"));
		if (!StructPath.IsEmpty())
		{
			if (UScriptStruct* Struct = LoadObject<UScriptStruct>(nullptr, *StructPath))
			{
				return FNiagaraTypeDefinition(Struct, FNiagaraTypeDefinition::EAllowUnfriendlyStruct::Allow);
			}
			OutMissingAssets.Add(StructPath);
		}

		return FNiagaraTypeDefinition();
	}

	// ---------------------------------------------------------------------------
	// Graph helpers
	// ---------------------------------------------------------------------------

	UNiagaraGraph* GetGraphFromSource(UNiagaraScriptSourceBase* SourceBase)
	{
		UNiagaraScriptSource* Source = Cast<UNiagaraScriptSource>(SourceBase);
		return Source ? Source->NodeGraph.Get() : nullptr;
	}

	FString GetUsageName(ENiagaraScriptUsage Usage)
	{
		if (const UEnum* UsageEnum = StaticEnum<ENiagaraScriptUsage>())
		{
			return UsageEnum->GetNameStringByValue(static_cast<int64>(Usage));
		}
		return TEXT("Unknown");
	}

	FString MakeGraphKey(const UNiagaraScript* Script, int32 GraphIndex)
	{
		if (!Script)
		{
			return FString::Printf(TEXT("Unknown|%d"), GraphIndex);
		}

		return FString::Printf(
			TEXT("%s|%s|%s|%d"),
			*GetUsageName(Script->GetUsage()),
			*MakeGuidString(Script->GetUsageId()),
			*Script->GetName(),
			GraphIndex);
	}

	FString GetCompileStatusName(ENiagaraScriptCompileStatus Status)
	{
		if (const UEnum* StatusEnum = StaticEnum<ENiagaraScriptCompileStatus>())
		{
			return StatusEnum->GetNameStringByValue(static_cast<int64>(Status));
		}
		return TEXT("Unknown");
	}

	/**
	 * Collects every script that still has no compiled VM after a compile pass.  The rebuilt graph data lives on the
	 * scripts, so a script without a VM means its renderer bindings / event receivers never get cached and the effect
	 * silently loses emitters at runtime.
	 */
	void CollectUncompiledScripts(UNiagaraSystem* System, TArray<FString>& OutPending)
	{
		OutPending.Reset();
		if (!System)
		{
			return;
		}

		auto CheckScript = [&OutPending](const UNiagaraScript* Script, const TCHAR* Label)
			{
				if (!Script)
				{
					return;
				}

				const ENiagaraScriptCompileStatus Status = Script->GetLastCompileStatus();
				if (Status == ENiagaraScriptCompileStatus::NCS_Unknown || Status == ENiagaraScriptCompileStatus::NCS_Error)
				{
					OutPending.Add(FString::Printf(TEXT("%s:%s=%s"), Label, *Script->GetName(), *GetCompileStatusName(Status)));
				}
			};

		CheckScript(System->GetSystemSpawnScript(), TEXT("System/Spawn"));
		CheckScript(System->GetSystemUpdateScript(), TEXT("System/Update"));

		for (const FNiagaraEmitterHandle& Handle : System->GetEmitterHandles())
		{
			const FVersionedNiagaraEmitterData* EmitterData = Handle.GetEmitterData();
			if (!EmitterData || !Handle.GetIsEnabled())
			{
				continue;
			}

			const FString EmitterName = Handle.GetName().ToString();
			const FString LabelPrefix = EmitterName + TEXT("/");

			CheckScript(EmitterData->SpawnScriptProps.Script, *LabelPrefix);
			CheckScript(EmitterData->UpdateScriptProps.Script, *LabelPrefix);

			// A CPU emitter's GPU compute script is intentionally never compiled.
			if (EmitterData->SimTarget == ENiagaraSimTarget::GPUComputeSim)
			{
				CheckScript(EmitterData->GetGPUComputeScript(), *(LabelPrefix + TEXT("GPU")));
			}

			for (const FNiagaraEventScriptProperties& EventHandler : EmitterData->EventHandlerScriptProps)
			{
				CheckScript(EventHandler.Script, *(LabelPrefix + TEXT("Event")));
			}

			for (UNiagaraSimulationStageBase* SimulationStage : EmitterData->GetSimulationStages())
			{
				if (SimulationStage && SimulationStage->bEnabled)
				{
					CheckScript(SimulationStage->Script, *(LabelPrefix + TEXT("SimulationStage")));
				}
			}
		}
	}

	/** Text factory that allows every graph node, including output / emitter nodes which cannot be duplicated. */
	struct FCommonEFXGraphTextFactory : public FCustomizableTextObjectFactory
	{
		UEdGraph* DestinationGraph = nullptr;
		TSet<UEdGraphNode*> SpawnedNodes;

		explicit FCommonEFXGraphTextFactory(UEdGraph* InGraph)
			: FCustomizableTextObjectFactory(GWarn)
			, DestinationGraph(InGraph)
		{
		}

		virtual bool CanCreateClass(UClass* ObjectClass, bool& bOmitSubObjs) const override
		{
			bOmitSubObjs = true;
			return ObjectClass && ObjectClass->IsChildOf(UEdGraphNode::StaticClass());
		}

		virtual void ProcessConstructedObject(UObject* CreatedObject) override
		{
			if (UNiagaraNodeInput* InputNode = Cast<UNiagaraNodeInput>(CreatedObject))
			{
				FObjectProperty* DataInterfaceProperty = FindFProperty<FObjectProperty>(UNiagaraNodeInput::StaticClass(), TEXT("DataInterface"));
				if (InputNode->Input.IsDataInterface() && DataInterfaceProperty &&
					DataInterfaceProperty->GetPropertyValue_InContainer(InputNode) == nullptr)
				{
					// A dotted input name is exported as a short object path, which the text importer
					// cannot resolve back to the embedded DataInterface it has already created.
					TArray<UObject*> ChildObjects;
					GetObjectsWithOuter(InputNode, ChildObjects, false);
					for (UObject* ChildObject : ChildObjects)
					{
						UNiagaraDataInterface* DataInterface = Cast<UNiagaraDataInterface>(ChildObject);
						if (DataInterface && DataInterface->GetClass() == InputNode->Input.GetType().GetClass())
						{
							DataInterfaceProperty->SetPropertyValue_InContainer(InputNode, DataInterface);
							break;
						}
					}
				}
			}

			if (UEdGraphNode* Node = Cast<UEdGraphNode>(CreatedObject))
			{
				SpawnedNodes.Add(Node);
				if (DestinationGraph)
				{
					DestinationGraph->Nodes.Add(Node);
				}
			}
		}
	};

	TArray<TSharedPtr<FJsonValue>> ExportScriptVariables(UNiagaraGraph* Graph)
	{
		TArray<TSharedPtr<FJsonValue>> Result;
		if (!Graph)
		{
			return Result;
		}

		static const TSet<FName> SkipNames =
		{
			TEXT("Variable"),
			TEXT("DefaultValueVariant"),
		};

		for (const TPair<FNiagaraVariable, TObjectPtr<UNiagaraScriptVariable>>& Pair : Graph->GetAllMetaData())
		{
			const FNiagaraVariable& Variable = Pair.Key;
			const UNiagaraScriptVariable* ScriptVariable = Pair.Value.Get();
			if (!ScriptVariable || !Variable.GetType().IsValid())
			{
				continue;
			}

			TSharedPtr<FJsonObject> VariableObject = MakeShared<FJsonObject>();
			VariableObject->SetStringField(TEXT("Name"), Variable.GetName().ToString());
			VariableObject->SetObjectField(TEXT("Type"), ExportType(Variable.GetType()));

			TArray<TSharedPtr<FJsonValue>> Properties;
			ExportPropertiesFromObject(const_cast<UNiagaraScriptVariable*>(ScriptVariable), SkipNames, false, Properties);
			VariableObject->SetArrayField(TEXT("Properties"), Properties);

			const FNiagaraVariant& DefaultValue = ScriptVariable->GetDefaultValueVariant();
			if (DefaultValue.GetMode() == ENiagaraVariantMode::Bytes && DefaultValue.GetNumBytes() > 0)
			{
				TArray<uint8> Bytes;
				Bytes.Append(DefaultValue.GetBytes(), DefaultValue.GetNumBytes());
				VariableObject->SetStringField(TEXT("DefaultValueBase64"), FBase64::Encode(Bytes));
			}

			Result.Add(MakeShared<FJsonValueObject>(VariableObject));
		}

		return Result;
	}

	TSharedPtr<FJsonObject> ExportGraph(UNiagaraGraph* Graph, const FString& Key, int32& OutNodeCount)
	{
		TSharedPtr<FJsonObject> GraphObject = MakeShared<FJsonObject>();
		GraphObject->SetStringField(TEXT("Key"), Key);

		TArray<TSharedPtr<FJsonValue>> NodeValues;
		TSet<UObject*> NodesToExport;

		if (Graph)
		{
			for (const TObjectPtr<UEdGraphNode>& NodePtr : Graph->Nodes)
			{
				UEdGraphNode* Node = NodePtr.Get();
				if (!Node)
				{
					continue;
				}

				NodesToExport.Add(Node);

				TSharedPtr<FJsonObject> NodeObject = MakeShared<FJsonObject>();
				NodeObject->SetStringField(TEXT("Guid"), MakeGuidString(Node->NodeGuid));
				NodeObject->SetStringField(TEXT("Class"), Node->GetClass()->GetPathName());
				NodeObject->SetStringField(TEXT("Name"), Node->GetName());

				if (const UNiagaraNodeFunctionCall* FunctionCall = Cast<UNiagaraNodeFunctionCall>(Node))
				{
					if (FunctionCall->FunctionScript)
					{
						NodeObject->SetStringField(TEXT("FunctionScript"), FunctionCall->FunctionScript->GetPathName());
					}
				}

				NodeValues.Add(MakeShared<FJsonValueObject>(NodeObject));
			}
		}

		FString NodesText;
		if (NodesToExport.Num() > 0)
		{
			FEdGraphUtilities::ExportNodesToText(NodesToExport, NodesText);
		}

		GraphObject->SetStringField(TEXT("NodesText"), NodesText);
		GraphObject->SetArrayField(TEXT("Nodes"), NodeValues);
		GraphObject->SetArrayField(TEXT("ScriptVariables"), ExportScriptVariables(Graph));

		OutNodeCount += NodeValues.Num();
		return GraphObject;
	}

	void ImportScriptVariables(UNiagaraGraph* Graph, const TArray<TSharedPtr<FJsonValue>>* VariableValues, const FString& Context, TArray<FString>& OutMissingAssets)
	{
		if (!Graph || !VariableValues)
		{
			return;
		}

		static const TSet<FName> SkipNames =
		{
			TEXT("Variable"),
			TEXT("DefaultValueVariant"),
		};

		for (const TSharedPtr<FJsonValue>& Value : *VariableValues)
		{
			const TSharedPtr<FJsonObject> VariableObject = Value.IsValid() ? Value->AsObject() : nullptr;
			if (!VariableObject.IsValid())
			{
				continue;
			}

			const FString VariableName = GetStringField(VariableObject, TEXT("Name"));
			const FNiagaraTypeDefinition Type = ResolveType(GetObjectField(VariableObject, TEXT("Type")), OutMissingAssets);
			if (!Type.IsValid() || VariableName.IsEmpty())
			{
				UE_LOG(LogCommonEFXSnapshotV2, Warning, TEXT("%s: skipped graph variable '%s' because its type could not be resolved."), *Context, *VariableName);
				continue;
			}

			FNiagaraVariable Variable(Type, FName(*VariableName));
			Variable.AllocateData();

			TObjectPtr<UNiagaraScriptVariable>* ExistingVariable = Graph->GetAllMetaData().Find(Variable);
			UNiagaraScriptVariable* ScriptVariable = ExistingVariable ? ExistingVariable->Get() : nullptr;
			const bool bIsNew = ScriptVariable == nullptr;
			if (bIsNew)
			{
				ScriptVariable = NewObject<UNiagaraScriptVariable>(Graph, NAME_None, RF_Transactional);
				ScriptVariable->Variable = Variable;
			}

			const FString DefaultValueText = GetStringField(VariableObject, TEXT("DefaultValueBase64"));
			if (!DefaultValueText.IsEmpty())
			{
				TArray<uint8> DefaultValueBytes;
				if (FBase64::Decode(DefaultValueText, DefaultValueBytes))
				{
					if (DefaultValueBytes.Num() == Variable.GetSizeInBytes() && DefaultValueBytes.Num() > 0)
					{
						ScriptVariable->SetDefaultValueData(DefaultValueBytes.GetData());
					}
					else
					{
						UE_LOG(LogCommonEFXSnapshotV2, Warning,
							TEXT("%s: default value size mismatch for graph variable '%s' (recorded=%d expected=%d)."),
							*Context, *VariableName, DefaultValueBytes.Num(), Variable.GetSizeInBytes());
					}
				}
			}

			ImportPropertiesIntoObject(ScriptVariable, GetArrayField(VariableObject, TEXT("Properties")), Context, OutMissingAssets, SkipNames);

			if (bIsNew)
			{
				Graph->GetAllMetaData().Add(Variable, ScriptVariable);
			}
		}
	}

	int32 ImportGraph(UNiagaraGraph* Graph, const TSharedPtr<FJsonObject>& GraphObject, const FString& Context, TArray<FString>& OutMissingAssets)
	{
		if (!Graph || !GraphObject.IsValid())
		{
			return 0;
		}

		const FString NodesText = GetStringField(GraphObject, TEXT("NodesText"));
		const TArray<TSharedPtr<FJsonValue>>* RecordedNodes = GetArrayField(GraphObject, TEXT("Nodes"));
		if (NodesText.IsEmpty() && (!RecordedNodes || RecordedNodes->Num() == 0))
		{
			// Generic EFX snapshots only carry RapidIteration values and renderers. Wiping the factory
			// graph here leaves every script without an output node; Niagara Editor then crashes on open.
			UE_LOG(LogCommonEFXSnapshotV2, Display, TEXT("%s: snapshot graph is empty, keeping the factory graph."), *Context);
			return 0;
		}

		Graph->Modify();

		TArray<UEdGraphNode*> ExistingNodes;
		for (const TObjectPtr<UEdGraphNode>& Node : Graph->Nodes)
		{
			if (Node)
			{
				ExistingNodes.Add(Node.Get());
			}
		}
		for (UEdGraphNode* Node : ExistingNodes)
		{
			Graph->RemoveNode(Node);
		}

		// Clear the factory-created script variable metadata; the snapshot's variables are re-added below.
		Graph->GetAllMetaData().Empty();

		// Script assets referenced by function call nodes are loaded before the text import so the object
		// references inside the T3D can be resolved even when the original system is gone.
		TMap<FGuid, FString> FunctionScriptPaths;
		if (const TArray<TSharedPtr<FJsonValue>>* NodeValues = GetArrayField(GraphObject, TEXT("Nodes")))
		{
			for (const TSharedPtr<FJsonValue>& Value : *NodeValues)
			{
				const TSharedPtr<FJsonObject> NodeObject = Value.IsValid() ? Value->AsObject() : nullptr;
				if (!NodeObject.IsValid())
				{
					continue;
				}

				const FString FunctionScriptPath = GetStringField(NodeObject, TEXT("FunctionScript"));
				if (FunctionScriptPath.IsEmpty())
				{
					continue;
				}

				const FGuid NodeGuid = GetGuidField(NodeObject, TEXT("Guid"));
				FunctionScriptPaths.Add(NodeGuid, FunctionScriptPath);
				LoadObject<UNiagaraScript>(nullptr, *FunctionScriptPath);
			}
		}

		FCommonEFXGraphTextFactory Factory(Graph);
		if (!NodesText.IsEmpty())
		{
			Factory.ProcessBuffer(Graph, RF_Transactional, NodesText);
		}

		FEdGraphUtilities::PostProcessPastedNodes(Factory.SpawnedNodes);
		UEdGraphPin::ResolveAllPinReferences();

		for (const TObjectPtr<UEdGraphNode>& NodePtr : Graph->Nodes)
		{
			UEdGraphNode* Node = NodePtr.Get();
			if (!Node)
			{
				continue;
			}

			// Assignment nodes own an auto generated script. When the source system is gone the recorded
			// script path no longer loads, so regenerate the script and its pins from the saved targets.
			if (UNiagaraNodeAssignment* Assignment = Cast<UNiagaraNodeAssignment>(Node))
			{
				if (Assignment->FunctionScript == nullptr)
				{
					Assignment->RefreshFromExternalChanges();
				}
				continue;
			}

			if (UNiagaraNodeFunctionCall* FunctionCall = Cast<UNiagaraNodeFunctionCall>(Node))
			{
				if (FunctionCall->FunctionScript == nullptr)
				{
					if (const FString* FunctionScriptPath = FunctionScriptPaths.Find(Node->NodeGuid))
					{
						if (UNiagaraScript* Script = LoadObject<UNiagaraScript>(nullptr, **FunctionScriptPath))
						{
							FunctionCall->FunctionScript = Script;
						}
						else
						{
							OutMissingAssets.Add(*FunctionScriptPath);
						}
					}
				}
			}
		}

		ImportScriptVariables(Graph, GetArrayField(GraphObject, TEXT("ScriptVariables")), Context, OutMissingAssets);

		Graph->NotifyGraphChanged();
		return Factory.SpawnedNodes.Num();
	}

	// ---------------------------------------------------------------------------
	// System / emitter JSON helpers
	// ---------------------------------------------------------------------------

	void ExportUsageId(const TSharedPtr<FJsonObject>& UsageIds, const TCHAR* Key, const UNiagaraScript* Script)
	{
		UsageIds->SetStringField(Key, Script ? MakeGuidString(Script->GetUsageId()) : FString());
	}

	void ImportUsageId(const TSharedPtr<FJsonObject>& UsageIds, const TCHAR* Key, UNiagaraScript* Script)
	{
		if (!UsageIds.IsValid() || !Script)
		{
			return;
		}

		FGuid UsageId;
		if (FGuid::Parse(GetStringField(UsageIds, Key), UsageId))
		{
			Script->SetUsageId(UsageId);
		}
	}

	void ExportUsage(const TSharedPtr<FJsonObject>& Usages, const TCHAR* Key, const UNiagaraScript* Script)
	{
		Usages->SetStringField(Key, Script ? GetUsageName(Script->GetUsage()) : FString());
	}

	void ImportUsage(const TSharedPtr<FJsonObject>& Usages, const TCHAR* Key, UNiagaraScript* Script)
	{
		if (!Usages.IsValid() || !Script)
		{
			return;
		}

		const FString UsageName = GetStringField(Usages, Key);
		if (UsageName.IsEmpty())
		{
			return;
		}

		const UEnum* UsageEnum = StaticEnum<ENiagaraScriptUsage>();
		if (!UsageEnum)
		{
			return;
		}

		const int64 UsageValue = UsageEnum->GetValueByNameString(UsageName);
		if (UsageValue != INDEX_NONE)
		{
			Script->SetUsage(static_cast<ENiagaraScriptUsage>(UsageValue));
		}
	}

	TArray<TSharedPtr<FJsonValue>> ExportUserParameters(UNiagaraSystem* System)
	{
		TArray<TSharedPtr<FJsonValue>> Result;
		if (!System)
		{
			return Result;
		}

		FNiagaraUserRedirectionParameterStore& Store = System->GetExposedParameters();
		TArray<FNiagaraVariable> Parameters;
		Store.GetParameters(Parameters);

		for (const FNiagaraVariable& Variable : Parameters)
		{
			if (!IsUserParameterVariable(Variable) || !Variable.GetType().IsValid())
			{
				continue;
			}

			TSharedPtr<FJsonObject> ParameterObject = MakeShared<FJsonObject>();
			ParameterObject->SetStringField(TEXT("Name"), Variable.GetName().ToString());
			ParameterObject->SetObjectField(TEXT("Type"), ExportType(Variable.GetType()));

			if (Variable.IsDataInterface())
			{
				if (UNiagaraDataInterface* DataInterface = Store.GetDataInterface(Variable))
				{
					TSharedPtr<FJsonObject> InterfaceObject = MakeShared<FJsonObject>();
					InterfaceObject->SetStringField(TEXT("Class"), DataInterface->GetClass()->GetPathName());

					TArray<TSharedPtr<FJsonValue>> InterfaceProperties;
					ExportPropertiesFromObject(DataInterface, TSet<FName>(), true, InterfaceProperties);
					InterfaceObject->SetArrayField(TEXT("Properties"), InterfaceProperties);

					ParameterObject->SetObjectField(TEXT("DataInterface"), InterfaceObject);
				}
			}
			else if (Variable.IsUObject())
			{
				const int32 Offset = Store.IndexOf(Variable);
				const TArray<UObject*>& UObjects = Store.GetUObjects();
				if (UObjects.IsValidIndex(Offset) && UObjects[Offset])
				{
					ParameterObject->SetStringField(TEXT("Object"), UObjects[Offset]->GetPathName());
				}
			}
			else if (Variable.GetSizeInBytes() > 0)
			{
				TArray<uint8> Bytes;
				Bytes.SetNumZeroed(Variable.GetSizeInBytes());
				if (Store.CopyParameterData(Variable, Bytes.GetData()))
				{
					ParameterObject->SetStringField(TEXT("ValueBase64"), FBase64::Encode(Bytes));
				}
			}

			Result.Add(MakeShared<FJsonValueObject>(ParameterObject));
		}

		return Result;
	}

	void ImportUserParameters(UNiagaraSystem* System, const TArray<TSharedPtr<FJsonValue>>* ParameterValues, TArray<FString>& OutMissingAssets)
	{
		if (!System || !ParameterValues)
		{
			return;
		}

		FNiagaraUserRedirectionParameterStore& Store = System->GetExposedParameters();

		for (const TSharedPtr<FJsonValue>& Value : *ParameterValues)
		{
			const TSharedPtr<FJsonObject> ParameterObject = Value.IsValid() ? Value->AsObject() : nullptr;
			if (!ParameterObject.IsValid())
			{
				continue;
			}

			const FString ParameterName = GetStringField(ParameterObject, TEXT("Name"));
			const FNiagaraTypeDefinition Type = ResolveType(GetObjectField(ParameterObject, TEXT("Type")), OutMissingAssets);
			if (!Type.IsValid() || ParameterName.IsEmpty())
			{
				UE_LOG(LogCommonEFXSnapshotV2, Warning, TEXT("Skipped user parameter '%s' because its type could not be resolved."), *ParameterName);
				continue;
			}

			FNiagaraVariable Variable(Type, FName(*ParameterName));

			if (Type.IsDataInterface())
			{
				const TSharedPtr<FJsonObject> InterfaceObject = GetObjectField(ParameterObject, TEXT("DataInterface"));
				UClass* InterfaceClass = nullptr;
				if (InterfaceObject.IsValid())
				{
					const FString ClassPath = GetStringField(InterfaceObject, TEXT("Class"));
					InterfaceClass = LoadClass<UNiagaraDataInterface>(nullptr, *ClassPath);
					if (!InterfaceClass)
					{
						OutMissingAssets.Add(ClassPath);
					}
				}

				if (InterfaceClass)
				{
					UNiagaraDataInterface* DataInterface = NewObject<UNiagaraDataInterface>(System, InterfaceClass, NAME_None, RF_Transactional);
					ImportPropertiesIntoObject(DataInterface, GetArrayField(InterfaceObject, TEXT("Properties")), ParameterName, OutMissingAssets);

					int32 Offset = INDEX_NONE;
					Store.AddParameter(Variable, false, false, &Offset);
					Store.SetDataInterface(DataInterface, Variable);
				}
			}
			else if (Type.IsUObject())
			{
				const FString ObjectPath = GetStringField(ParameterObject, TEXT("Object"));
				UObject* Object = ObjectPath.IsEmpty() ? nullptr : LoadObject<UObject>(nullptr, *ObjectPath);
				if (!ObjectPath.IsEmpty() && !Object)
				{
					OutMissingAssets.Add(ObjectPath);
				}

				int32 Offset = INDEX_NONE;
				Store.AddParameter(Variable, false, false, &Offset);
				if (Object && Offset != INDEX_NONE)
				{
					Store.SetUObject(Object, Variable);
				}
			}
			else
			{
				const FString ValueText = GetStringField(ParameterObject, TEXT("ValueBase64"));
				if (ValueText.IsEmpty())
				{
					Store.AddParameter(Variable, true, false);
					continue;
				}

				TArray<uint8> Bytes;
				if (!FBase64::Decode(ValueText, Bytes))
				{
					continue;
				}

				if (Bytes.Num() == Variable.GetSizeInBytes() && Bytes.Num() > 0)
				{
					Store.SetParameterData(Bytes.GetData(), Variable, true);
				}
				else
				{
					UE_LOG(LogCommonEFXSnapshotV2, Warning,
						TEXT("User parameter '%s' default size mismatch (recorded=%d expected=%d)."),
						*ParameterName, Bytes.Num(), Variable.GetSizeInBytes());
				}
			}
		}
	}

	// ---------------------------------------------------------------------------
	// Script parameter (rapid iteration) helpers
	// ---------------------------------------------------------------------------

	/**
	 * Module input overrides are baked into UNiagaraScript::RapidIterationParameters, which is script state and
	 * therefore not part of the graph text. Snapshot it so the rebuilt scripts keep the exact input values.
	 */
	TSharedPtr<FJsonObject> ExportScriptParameters(UNiagaraScript* Script)
	{
		if (!Script)
		{
			return nullptr;
		}

		TSharedPtr<FJsonObject> ScriptObject = MakeShared<FJsonObject>();
		ScriptObject->SetStringField(TEXT("UsageId"), MakeGuidString(Script->GetUsageId()));
		ScriptObject->SetStringField(TEXT("Usage"), GetUsageName(Script->GetUsage()));
		ScriptObject->SetStringField(TEXT("Name"), Script->GetName());

		TArray<TSharedPtr<FJsonValue>> ParameterValues;
		TArray<FNiagaraVariable> Variables;
		Script->RapidIterationParameters.GetParameters(Variables);
		for (const FNiagaraVariable& Variable : Variables)
		{
			if (!Variable.GetType().IsValid())
			{
				continue;
			}

			TSharedPtr<FJsonObject> ParameterObject = MakeShared<FJsonObject>();
			ParameterObject->SetStringField(TEXT("Name"), Variable.GetName().ToString());
			ParameterObject->SetObjectField(TEXT("Type"), ExportType(Variable.GetType()));

			if (Variable.IsDataInterface())
			{
				if (UNiagaraDataInterface* DataInterface = Script->RapidIterationParameters.GetDataInterface(Variable))
				{
					TSharedPtr<FJsonObject> InterfaceObject = MakeShared<FJsonObject>();
					InterfaceObject->SetStringField(TEXT("Class"), DataInterface->GetClass()->GetPathName());

					TArray<TSharedPtr<FJsonValue>> InterfaceProperties;
					ExportPropertiesFromObject(DataInterface, TSet<FName>(), true, InterfaceProperties);
					InterfaceObject->SetArrayField(TEXT("Properties"), InterfaceProperties);

					ParameterObject->SetObjectField(TEXT("DataInterface"), InterfaceObject);
				}
			}
			else if (Variable.IsUObject())
			{
				if (UObject* Object = Script->RapidIterationParameters.GetUObject(Variable))
				{
					ParameterObject->SetStringField(TEXT("Object"), Object->GetPathName());
				}
			}
			else if (Variable.GetSizeInBytes() > 0)
			{
				TArray<uint8> Bytes;
				Bytes.SetNumZeroed(Variable.GetSizeInBytes());
				if (Script->RapidIterationParameters.CopyParameterData(Variable, Bytes.GetData()))
				{
					ParameterObject->SetStringField(TEXT("ValueBase64"), FBase64::Encode(Bytes));
				}
			}

			ParameterValues.Add(MakeShared<FJsonValueObject>(ParameterObject));
		}

		ScriptObject->SetArrayField(TEXT("Parameters"), ParameterValues);
		return ScriptObject;
	}

	void ImportScriptParameters(UNiagaraScript* Script, const TArray<TSharedPtr<FJsonValue>>* ParameterValues, const FString& Context, TArray<FString>& OutMissingAssets)
	{
		if (!Script || !ParameterValues)
		{
			return;
		}

		for (const TSharedPtr<FJsonValue>& Value : *ParameterValues)
		{
			const TSharedPtr<FJsonObject> ParameterObject = Value.IsValid() ? Value->AsObject() : nullptr;
			if (!ParameterObject.IsValid())
			{
				continue;
			}

			const FString ParameterName = GetStringField(ParameterObject, TEXT("Name"));
			const FNiagaraTypeDefinition Type = ResolveType(GetObjectField(ParameterObject, TEXT("Type")), OutMissingAssets);
			if (!Type.IsValid() || ParameterName.IsEmpty())
			{
				continue;
			}

			FNiagaraVariable Variable(Type, FName(*ParameterName));

			if (Type.IsDataInterface())
			{
				const TSharedPtr<FJsonObject> InterfaceObject = GetObjectField(ParameterObject, TEXT("DataInterface"));
				UClass* InterfaceClass = nullptr;
				if (InterfaceObject.IsValid())
				{
					const FString ClassPath = GetStringField(InterfaceObject, TEXT("Class"));
					InterfaceClass = LoadClass<UNiagaraDataInterface>(nullptr, *ClassPath);
					if (!InterfaceClass)
					{
						OutMissingAssets.Add(ClassPath);
					}
				}

				if (InterfaceClass)
				{
					UNiagaraDataInterface* DataInterface = NewObject<UNiagaraDataInterface>(Script, InterfaceClass, NAME_None, RF_Transactional);
					ImportPropertiesIntoObject(DataInterface, GetArrayField(InterfaceObject, TEXT("Properties")), FString::Printf(TEXT("%s/%s"), *Context, *ParameterName), OutMissingAssets);

					int32 Offset = INDEX_NONE;
					Script->RapidIterationParameters.AddParameter(Variable, false, false, &Offset);
					Script->RapidIterationParameters.SetDataInterface(DataInterface, Variable);
				}
			}
			else if (Type.IsUObject())
			{
				const FString ObjectPath = GetStringField(ParameterObject, TEXT("Object"));
				UObject* Object = ObjectPath.IsEmpty() ? nullptr : LoadObject<UObject>(nullptr, *ObjectPath);
				if (!ObjectPath.IsEmpty() && !Object)
				{
					OutMissingAssets.Add(ObjectPath);
				}

				int32 Offset = INDEX_NONE;
				Script->RapidIterationParameters.AddParameter(Variable, false, false, &Offset);
				if (Object)
				{
					Script->RapidIterationParameters.SetUObject(Object, Variable);
				}
			}
			else
			{
				int32 Offset = INDEX_NONE;
				Script->RapidIterationParameters.AddParameter(Variable, false, false, &Offset);

				TArray<uint8> Bytes;
				if (FBase64::Decode(GetStringField(ParameterObject, TEXT("ValueBase64")), Bytes)
					&& Bytes.Num() == Variable.GetSizeInBytes() && Bytes.Num() > 0)
				{
					Script->RapidIterationParameters.SetParameterData(Bytes.GetData(), Variable, true);
				}
			}
		}
	}

	/**
	 * Applies a recorded script parameter block to the script with the same usage name.  Occurrence disambiguates
	 * multiple scripts that share a usage (event handlers, simulation stages) and is tracked in export order.
	 */
	void ApplyScriptParameters(UNiagaraScript* Script, const TArray<TSharedPtr<FJsonValue>>* ScriptValues, const FString& Usage, int32 Occurrence, const FString& Context, TArray<FString>& OutMissingAssets)
	{
		if (!Script || !ScriptValues)
		{
			return;
		}

		int32 Seen = 0;
		for (const TSharedPtr<FJsonValue>& Value : *ScriptValues)
		{
			const TSharedPtr<FJsonObject> ScriptObject = Value.IsValid() ? Value->AsObject() : nullptr;
			if (!ScriptObject.IsValid() || GetStringField(ScriptObject, TEXT("Usage")) != Usage)
			{
				continue;
			}

			if (Seen++ != Occurrence)
			{
				continue;
			}

			ImportScriptParameters(Script, GetArrayField(ScriptObject, TEXT("Parameters")), Context, OutMissingAssets);
			return;
		}
	}

	// ---------------------------------------------------------------------------
	// Generic EFX snapshots have RapidIteration values but no graph. The factory
	// graph is kept so the asset can open; these helpers then write spawn / burst
	// / motion onto that graph so compile does not reset everything to defaults.
	// ---------------------------------------------------------------------------

	const TCHAR* const SpawnBurstModulePath = TEXT("/Niagara/Modules/Emitter/SpawnBurst_Instantaneous.SpawnBurst_Instantaneous");
	const TCHAR* const SphereLocationModulePath = TEXT("/Niagara/Modules/Spawn/Location/V2/SphereLocation.SphereLocation");
	const TCHAR* const BoxLocationModulePath = TEXT("/Niagara/Modules/Spawn/Location/BoxLocation.BoxLocation");
	const TCHAR* const CylinderLocationModulePath = TEXT("/Niagara/Modules/Spawn/Location/CylinderLocation.CylinderLocation");
	const TCHAR* const GravityForceModulePath = TEXT("/Niagara/Modules/Update/Forces/GravityForce.GravityForce");
	const TCHAR* const DragModulePath = TEXT("/Niagara/Modules/Update/Forces/Drag.Drag");

	UNiagaraScript* LoadNiagaraModuleScript(const FString& ScriptPath)
	{
		TArray<FString> Candidates;
		Candidates.Add(ScriptPath);
		if (ScriptPath.Contains(TEXT("/V2/")))
		{
			FString Candidate = ScriptPath;
			Candidate.ReplaceInline(TEXT("/V2/"), TEXT("/V3/"));
			Candidates.Add(Candidate);
			Candidate = ScriptPath;
			Candidate.ReplaceInline(TEXT("/V2/"), TEXT("/"));
			Candidates.Add(Candidate);
		}
		else
		{
			int32 Slash = INDEX_NONE;
			if (ScriptPath.FindLastChar(TEXT('/'), Slash))
			{
				const FString Directory = ScriptPath.Left(Slash);
				const FString Asset = ScriptPath.RightChop(Slash + 1);
				Candidates.Add(Directory + TEXT("/V2/") + Asset);
				Candidates.Add(Directory + TEXT("/V3/") + Asset);
			}
		}

		if (ScriptPath.EndsWith(TEXT("/Drag.Drag")))
		{
			Candidates.Add(TEXT("/Niagara/Modules/Update/Forces/DragForce.DragForce"));
		}

		for (const FString& Candidate : Candidates)
		{
			if (UNiagaraScript* Script = LoadObject<UNiagaraScript>(nullptr, *Candidate, nullptr, LOAD_NoWarn))
			{
				return Script;
			}
		}
		return nullptr;
	}

	UNiagaraNodeOutput* FindScriptOutputNode(UNiagaraScriptSource* Source, ENiagaraScriptUsage Usage)
	{
		if (!Source || !Source->NodeGraph)
		{
			return nullptr;
		}

		for (UEdGraphNode* Node : Source->NodeGraph->Nodes)
		{
			if (UNiagaraNodeOutput* Output = Cast<UNiagaraNodeOutput>(Node))
			{
				if (Output->GetUsage() == Usage)
				{
					return Output;
				}
			}
		}
		return nullptr;
	}

	bool IsConcreteNiagaraUsage(ENiagaraScriptUsage Usage)
	{
		switch (Usage)
		{
		case ENiagaraScriptUsage::ParticleSpawnScript:
		case ENiagaraScriptUsage::ParticleSpawnScriptInterpolated:
		case ENiagaraScriptUsage::ParticleUpdateScript:
		case ENiagaraScriptUsage::ParticleEventScript:
		case ENiagaraScriptUsage::ParticleSimulationStageScript:
		case ENiagaraScriptUsage::ParticleGPUComputeScript:
		case ENiagaraScriptUsage::EmitterSpawnScript:
		case ENiagaraScriptUsage::EmitterUpdateScript:
		case ENiagaraScriptUsage::SystemSpawnScript:
		case ENiagaraScriptUsage::SystemUpdateScript:
			return true;
		default:
			return false;
		}
	}

	FString RapidIterationTail(const FString& Name)
	{
		if (!Name.StartsWith(TEXT("Constants.")))
		{
			return Name;
		}

		int32 FirstDot = INDEX_NONE;
		Name.FindChar(TEXT('.'), FirstDot);
		if (FirstDot == INDEX_NONE)
		{
			return Name;
		}

		const int32 SecondDot = Name.Find(TEXT("."), ESearchCase::CaseSensitive, ESearchDir::FromStart, FirstDot + 1);
		if (SecondDot == INDEX_NONE)
		{
			return Name.Mid(FirstDot + 1);
		}
		return Name.Mid(SecondDot + 1);
	}

	bool ParseConstantModuleInput(const FString& Name, FString& OutModule, FString& OutInput)
	{
		const FString Tail = RapidIterationTail(Name);
		int32 LastDot = INDEX_NONE;
		if (!Tail.FindLastChar(TEXT('.'), LastDot))
		{
			return false;
		}

		OutModule = Tail.Left(LastDot);
		OutInput = Tail.Mid(LastDot + 1);
		return !OutModule.IsEmpty() && !OutInput.IsEmpty();
	}

	bool DecodeBase64Bytes(const FString& Base64, TArray<uint8>& OutBytes)
	{
		OutBytes.Reset();
		return FBase64::Decode(Base64, OutBytes) && OutBytes.Num() > 0;
	}

	bool DecodeFloatValue(const TArray<uint8>& Bytes, float& OutValue)
	{
		if (Bytes.Num() < static_cast<int32>(sizeof(float)))
		{
			return false;
		}
		FMemory::Memcpy(&OutValue, Bytes.GetData(), sizeof(float));
		return true;
	}

	struct FFactorySeedBinder
	{
		FVersionedNiagaraEmitterData* Data = nullptr;
		FString UniqueName;

		UNiagaraScript* ScriptFor(ENiagaraScriptUsage Usage) const
		{
			if (!Data)
			{
				return nullptr;
			}

			TArray<UNiagaraScript*> Scripts;
			Data->GetScripts(Scripts, false);
			for (UNiagaraScript* Script : Scripts)
			{
				if (Script && Script->GetUsage() == Usage)
				{
					return Script;
				}
			}
			return nullptr;
		}

		UNiagaraNodeFunctionCall* FindModule(const FString& ModuleName) const
		{
			UNiagaraScriptSource* Source = Data ? Cast<UNiagaraScriptSource>(Data->GraphSource) : nullptr;
			if (!Source || !Source->NodeGraph)
			{
				return nullptr;
			}

			FString Target = ModuleName;
			Target.ReplaceInline(TEXT(" "), TEXT(""));
			for (UEdGraphNode* Node : Source->NodeGraph->Nodes)
			{
				UNiagaraNodeFunctionCall* Call = Cast<UNiagaraNodeFunctionCall>(Node);
				if (!Call)
				{
					continue;
				}

				FString Name = Call->GetFunctionName();
				Name.ReplaceInline(TEXT(" "), TEXT(""));
				if (Name.Equals(Target, ESearchCase::IgnoreCase) ||
					Name.EndsWith(TEXT(".") + Target, ESearchCase::IgnoreCase))
				{
					return Call;
				}
			}
			return nullptr;
		}

		UEdGraphPin* FindLinkedMapInputPin(UEdGraphNode* Node) const
		{
			if (!Node)
			{
				return nullptr;
			}

			UEdGraphPin* Fallback = nullptr;
			for (UEdGraphPin* Pin : Node->Pins)
			{
				if (!Pin || Pin->Direction != EGPD_Input || Pin->LinkedTo.Num() != 1)
				{
					continue;
				}

				const FString Name = Pin->PinName.ToString();
				if (Name.Equals(TEXT("InputMap")) || Name.Equals(TEXT("Input")))
				{
					return Pin;
				}
				if (!Fallback)
				{
					Fallback = Pin;
				}
			}
			return Fallback;
		}

		void CollectOrderedModules(UNiagaraNodeOutput* Output, TArray<UNiagaraNodeFunctionCall*>& OutModules) const
		{
			OutModules.Reset();
			UEdGraphNode* Current = Output;
			while (Current)
			{
				UEdGraphPin* InputPin = FindLinkedMapInputPin(Current);
				if (!InputPin)
				{
					break;
				}

				UEdGraphNode* Previous = InputPin->LinkedTo[0] ? InputPin->LinkedTo[0]->GetOwningNode() : nullptr;
				if (UNiagaraNodeFunctionCall* Call = Cast<UNiagaraNodeFunctionCall>(Previous))
				{
					OutModules.Insert(Call, 0);
				}
				Current = Previous;
			}
		}

		bool ModuleMustPrecedeForceSolver(const FString& ModuleName) const
		{
			return ModuleName.Equals(TEXT("GravityForce"), ESearchCase::IgnoreCase) ||
				ModuleName.Equals(TEXT("Drag"), ESearchCase::IgnoreCase) ||
				ModuleName.Equals(TEXT("CurlNoiseForce"), ESearchCase::IgnoreCase) ||
				ModuleName.Equals(TEXT("LinearForce"), ESearchCase::IgnoreCase);
		}

		int32 InsertIndexBeforeForceSolver(UNiagaraNodeOutput* Output) const
		{
			TArray<UNiagaraNodeFunctionCall*> Ordered;
			CollectOrderedModules(Output, Ordered);
			for (int32 Index = 0; Index < Ordered.Num(); ++Index)
			{
				FString Name = Ordered[Index]->GetFunctionName();
				Name.ReplaceInline(TEXT(" "), TEXT(""));
				if (Name.Contains(TEXT("SolveForcesAndVelocity")))
				{
					return Index;
				}
			}
			return INDEX_NONE;
		}

		UNiagaraNodeFunctionCall* EnsureModule(ENiagaraScriptUsage Usage, const TCHAR* ModulePath, const FString& ModuleName)
		{
			if (UNiagaraNodeFunctionCall* Existing = FindModule(ModuleName))
			{
				return Existing;
			}

			UNiagaraScriptSource* Source = Data ? Cast<UNiagaraScriptSource>(Data->GraphSource) : nullptr;
			UNiagaraScript* ModuleScript = LoadNiagaraModuleScript(ModulePath);
			if (!Source || !ModuleScript)
			{
				UE_LOG(LogCommonEFXSnapshotV2, Warning, TEXT("Factory seed: could not load Niagara module %s"), ModulePath);
				return nullptr;
			}

			ENiagaraScriptUsage EffectiveUsage = Usage;
			const ENiagaraScriptUsage ScriptUsage = ModuleScript->GetUsage();
			if (IsConcreteNiagaraUsage(ScriptUsage))
			{
				EffectiveUsage = ScriptUsage;
			}

			UNiagaraNodeOutput* Output = FindScriptOutputNode(Source, EffectiveUsage);
			if (!Output)
			{
				Output = FindScriptOutputNode(Source, Usage);
			}
			if (!Output)
			{
				UE_LOG(LogCommonEFXSnapshotV2, Warning, TEXT("Factory seed: no output node for %s"), *ModuleName);
				return nullptr;
			}

			const int32 TargetIndex = ModuleMustPrecedeForceSolver(ModuleName)
				? InsertIndexBeforeForceSolver(Output)
				: INDEX_NONE;
			UNiagaraNodeFunctionCall* Call = FNiagaraStackGraphUtilities::AddScriptModuleToStack(ModuleScript, *Output, TargetIndex, ModuleName);
			if (Call)
			{
				Call->MarkNodeRequiresSynchronization(TEXT("CommonEFX factory seed"), true);
			}
			return Call;
		}

		template<typename ValueType>
		bool TrySetBinderValue(const FString& Module, const FString& Input, const ValueType& Value) const
		{
			FNiagaraStackFunctionInputBinder Binder;
			FText Error;
			if (!BindInput(Module, Input, Binder, Error, nullptr, FNiagaraTypeDefinition::Get<ValueType>()))
			{
				return false;
			}
			Binder.SetValue(Value);
			return true;
		}

		bool BindInput(const FString& Module, const FString& Input, FNiagaraStackFunctionInputBinder& Binder, FText& OutError, FString* OutResolvedInput = nullptr, TOptional<FNiagaraTypeDefinition> ExpectedType = {}) const
		{
			UNiagaraNodeFunctionCall* Call = FindModule(Module);
			if (!Call || !Data)
			{
				return false;
			}

			TArray<UNiagaraScript*> DependentScripts;
			Data->GetScripts(DependentScripts, false);

			UNiagaraScript* OwningScript = ScriptFor(FNiagaraStackGraphUtilities::GetOutputNodeUsage(*Call));
			if (!OwningScript)
			{
				for (UNiagaraScript* Script : DependentScripts)
				{
					if (Script)
					{
						OwningScript = Script;
						break;
					}
				}
			}
			if (!OwningScript)
			{
				return false;
			}

			auto Attempt = [&](const FString& Candidate)
			{
				return Binder.TryBind(
					OwningScript,
					DependentScripts,
					FCompileConstantResolver(),
					UniqueName,
					Call,
					FName(*Candidate),
					ExpectedType,
					true,
					OutError);
			};

			if (Attempt(Input))
			{
				if (OutResolvedInput)
				{
					*OutResolvedInput = Input;
				}
				return true;
			}

			FString Compact = Input;
			Compact.ReplaceInline(TEXT(" "), TEXT(""));
			if (!Compact.Equals(Input, ESearchCase::CaseSensitive) && Attempt(Compact))
			{
				if (OutResolvedInput)
				{
					*OutResolvedInput = Compact;
				}
				return true;
			}
			return false;
		}

		bool SetPinDefault(UNiagaraNodeFunctionCall* Call, const FString& Input, const FString& Value) const
		{
			if (!Call)
			{
				return false;
			}

			FString CompactInput = Input;
			CompactInput.ReplaceInline(TEXT(" "), TEXT(""));
			bool bFound = false;
			for (UEdGraphPin* Pin : Call->Pins)
			{
				if (!Pin || Pin->Direction != EGPD_Input)
				{
					continue;
				}

				const FString PinName = Pin->PinName.ToString();
				FString CompactPin = PinName;
				CompactPin.ReplaceInline(TEXT(" "), TEXT(""));
				if (PinName != Input &&
					!PinName.EndsWith(TEXT(".") + Input) &&
					!CompactPin.Equals(CompactInput, ESearchCase::IgnoreCase) &&
					!CompactPin.EndsWith(TEXT(".") + CompactInput, ESearchCase::IgnoreCase))
				{
					continue;
				}

				Pin->Modify();
				Pin->DefaultValue = Value;
				bFound = true;
			}

			if (bFound)
			{
				Call->MarkNodeRequiresSynchronization(TEXT("CommonEFX factory seed"), true);
			}
			return bFound;
		}

		bool SetFloat(const FString& Module, const FString& Input, float Value)
		{
			float WriteValue = Value;
			const bool bSpawnRateModule = Module.Equals(TEXT("SpawnRate"), ESearchCase::IgnoreCase);
			if (bSpawnRateModule && Input.Equals(TEXT("SpawnRate"), ESearchCase::IgnoreCase) && WriteValue <= 0.0f)
			{
				// look-params: Spawn Rate is particles/sec. 0 produces no particles.
				WriteValue = 10.0f;
			}
			if (bSpawnRateModule && Input.Equals(TEXT("Spawn Probability"), ESearchCase::IgnoreCase) && WriteValue <= 0.0f)
			{
				WriteValue = 1.0f;
			}

			TrySetBinderValue(Module, Input, WriteValue);
			TrySetBinderValue(Module, Input, FMath::RoundToInt(WriteValue));
			// RapidIteration-only writes are wiped by compile; pin defaults survive and show in the stack.
			return SetPinDefault(FindModule(Module), Input, FString::SanitizeFloat(WriteValue));
		}

		bool SetInt(const FString& Module, const FString& Input, int32 Value)
		{
			TrySetBinderValue(Module, Input, Value);
			return SetPinDefault(FindModule(Module), Input, FString::FromInt(Value));
		}

		bool SetVec3(const FString& Module, const FString& Input, const FVector3f& Value)
		{
			if (TrySetBinderValue(Module, Input, FNiagaraPosition(Value)) ||
				TrySetBinderValue(Module, Input, Value) ||
				TrySetBinderValue(Module, Input, FVector2f(Value.X, Value.Y)))
			{
				return true;
			}
			return SetPinDefault(FindModule(Module), Input,
				FString::Printf(TEXT("(X=%f,Y=%f,Z=%f)"), Value.X, Value.Y, Value.Z));
		}

		bool SetColor(const FString& Module, const FString& Input, const FLinearColor& Value)
		{
			if (TrySetBinderValue(Module, Input, Value))
			{
				return true;
			}
			return SetPinDefault(FindModule(Module), Input,
				FString::Printf(TEXT("(R=%f,G=%f,B=%f,A=%f)"), Value.R, Value.G, Value.B, Value.A));
		}

		static FString NormalizeEnumToken(FString Value)
		{
			FString Result;
			for (const TCHAR Character : Value)
			{
				if (FChar::IsAlnum(Character))
				{
					Result.AppendChar(FChar::ToLower(Character));
				}
			}
			return Result;
		}

		static int32 ResolveEnumIndex(UEnum* Enum, const FString& Value)
		{
			if (!Enum)
			{
				return INDEX_NONE;
			}

			const int64 Direct = Enum->GetValueByNameString(Value);
			if (Direct != INDEX_NONE)
			{
				return static_cast<int32>(Direct);
			}

			const FString Target = NormalizeEnumToken(Value);
			for (int32 Index = 0; Index < Enum->NumEnums(); ++Index)
			{
				FString Name = Enum->GetNameStringByIndex(Index);
				int32 Separator = INDEX_NONE;
				if (Name.FindLastChar(TEXT(':'), Separator))
				{
					Name = Name.RightChop(Separator + 1);
				}
				const FString Display = Enum->GetDisplayNameTextByIndex(Index).ToString();
				if (NormalizeEnumToken(Name) == Target || NormalizeEnumToken(Display) == Target)
				{
					return Index;
				}
			}
			return INDEX_NONE;
		}

		TArray<FString> EnumAliases(const FString& Input, const FString& Value) const
		{
			TArray<FString> Aliases;
			Aliases.Add(Value);
			if (Value.Equals(TEXT("Random"), ESearchCase::IgnoreCase))
			{
				Aliases.Add(TEXT("Random Range"));
				Aliases.Add(TEXT("RandomRange"));
			}
			else if (Value.Equals(TEXT("Random Range"), ESearchCase::IgnoreCase) || Value.Equals(TEXT("RandomRange"), ESearchCase::IgnoreCase))
			{
				Aliases.Add(TEXT("Random"));
			}
			if (Value.Equals(TEXT("Random Uniform"), ESearchCase::IgnoreCase) || Value.Equals(TEXT("RandomUniform"), ESearchCase::IgnoreCase))
			{
				Aliases.Add(TEXT("Uniform"));
			}
			else if (Value.Equals(TEXT("Uniform"), ESearchCase::IgnoreCase) && Input.Contains(TEXT("Size")))
			{
				Aliases.Add(TEXT("Random Uniform"));
			}
			if (Value.Equals(TEXT("Direct Set"), ESearchCase::IgnoreCase) || Value.Equals(TEXT("DirectSet"), ESearchCase::IgnoreCase))
			{
				Aliases.Add(TEXT("Direct Set"));
				Aliases.Add(TEXT("DirectSet"));
				Aliases.Add(TEXT("Direct"));
			}
			if (Value.Equals(TEXT("Simulation Position"), ESearchCase::IgnoreCase))
			{
				Aliases.Add(TEXT("SimulationPosition"));
			}
			return Aliases;
		}

		bool SetEnumOnce(const FString& Module, const FString& Input, const FString& Value)
		{
			UNiagaraNodeFunctionCall* Call = FindModule(Module);
			if (Call)
			{
				FString CompactInput = Input;
				CompactInput.ReplaceInline(TEXT(" "), TEXT(""));
				for (UEdGraphPin* Pin : Call->Pins)
				{
					if (!Pin || Pin->Direction != EGPD_Input || Pin->LinkedTo.Num() > 0)
					{
						continue;
					}

					const FString PinName = Pin->PinName.ToString();
					FString CompactPin = PinName;
					CompactPin.ReplaceInline(TEXT(" "), TEXT(""));
					if (PinName != Input &&
						!PinName.EndsWith(TEXT(".") + Input) &&
						!CompactPin.Equals(CompactInput, ESearchCase::IgnoreCase) &&
						!CompactPin.EndsWith(TEXT(".") + CompactInput, ESearchCase::IgnoreCase))
					{
						continue;
					}

					FString Stored = Value;
					if (Pin->PinType.PinCategory == UEdGraphSchema_K2::PC_Byte ||
						Pin->PinType.PinCategory == UEdGraphSchema_K2::PC_Enum)
					{
						if (UEnum* Enum = Cast<UEnum>(Pin->PinType.PinSubCategoryObject.Get()))
						{
							const int32 Index = ResolveEnumIndex(Enum, Value);
							if (Index == INDEX_NONE)
							{
								continue;
							}
							Stored = Enum->GetNameStringByIndex(Index);
							int32 Separator = INDEX_NONE;
							if (Stored.FindLastChar(TEXT(':'), Separator))
							{
								Stored = Stored.RightChop(Separator + 1);
							}
						}
					}

					Pin->Modify();
					Pin->DefaultValue = Stored;
					Call->MarkNodeRequiresSynchronization(TEXT("CommonEFX factory seed enum"), true);
					return true;
				}
			}

			FNiagaraStackFunctionInputBinder Binder;
			FText Error;
			if (BindInput(Module, Input, Binder, Error))
			{
				const FNiagaraTypeDefinition Type = Binder.GetInputType();
				if (Type.IsEnum())
				{
					const int32 Index = ResolveEnumIndex(Type.GetEnum(), Value);
					if (Index != INDEX_NONE)
					{
						Binder.SetValue<int32>(Index);
						return true;
					}
				}
			}
			return false;
		}

		bool SetEnum(const FString& Module, const FString& Input, const FString& Value)
		{
			for (const FString& Alias : EnumAliases(Input, Value))
			{
				if (SetEnumOnce(Module, Input, Alias))
				{
					return true;
				}
			}
			UE_LOG(LogCommonEFXSnapshotV2, Warning,
				TEXT("Factory seed: could not set enum %s.%s = %s"), *Module, *Input, *Value);
			return false;
		}
	};

	int32 OverlayExistingRapidIteration(UNiagaraScript* Script, const TArray<TSharedPtr<FJsonValue>>* ParameterValues)
	{
		if (!Script || !ParameterValues)
		{
			return 0;
		}

		TArray<FNiagaraVariable> Existing;
		Script->RapidIterationParameters.GetParameters(Existing);
		if (Existing.Num() == 0)
		{
			return 0;
		}

		int32 Applied = 0;
		for (const TSharedPtr<FJsonValue>& Value : *ParameterValues)
		{
			const TSharedPtr<FJsonObject> ParameterObject = Value.IsValid() ? Value->AsObject() : nullptr;
			if (!ParameterObject.IsValid())
			{
				continue;
			}

			const FString ParameterName = GetStringField(ParameterObject, TEXT("Name"));
			const FString Tail = RapidIterationTail(ParameterName);
			if (Tail.IsEmpty())
			{
				continue;
			}

			TArray<uint8> Bytes;
			if (!DecodeBase64Bytes(GetStringField(ParameterObject, TEXT("ValueBase64")), Bytes))
			{
				continue;
			}

			for (FNiagaraVariable Variable : Existing)
			{
				const FString ExistingName = Variable.GetName().ToString();
				if (ExistingName != ParameterName && !ExistingName.EndsWith(TEXT(".") + Tail) && ExistingName != Tail)
				{
					continue;
				}

				if (Bytes.Num() == Variable.GetSizeInBytes())
				{
					float OverlayFloat = 0.0f;
					if (Tail.EndsWith(TEXT("SpawnRate.SpawnRate")) && DecodeFloatValue(Bytes, OverlayFloat) && OverlayFloat <= 0.0f)
					{
						break;
					}
					Script->RapidIterationParameters.SetParameterData(Bytes.GetData(), Variable, true);
					++Applied;
					break;
				}

				float FloatValue = 0.0f;
				if (DecodeFloatValue(Bytes, FloatValue) && Variable.GetType().IsSameBaseDefinition(FNiagaraTypeDefinition::GetIntDef()))
				{
					const int32 IntValue = FMath::RoundToInt(FloatValue);
					Script->RapidIterationParameters.SetParameterData(reinterpret_cast<const uint8*>(&IntValue), Variable, true);
					++Applied;
					break;
				}
			}
		}

		return Applied;
	}

	int32 OverlayEmitterRapidIteration(FVersionedNiagaraEmitterData* EmitterData, const TArray<TSharedPtr<FJsonValue>>* ScriptValues)
	{
		if (!EmitterData || !ScriptValues)
		{
			return 0;
		}

		int32 Applied = 0;
		TArray<UNiagaraScript*> Scripts;
		EmitterData->GetScripts(Scripts, false);
		TMap<FString, int32> UsageOccurrences;
		for (UNiagaraScript* Script : Scripts)
		{
			if (!Script)
			{
				continue;
			}

			const FString Usage = GetUsageName(Script->GetUsage());
			int32& Occurrence = UsageOccurrences.FindOrAdd(Usage);
			int32 Seen = 0;
			for (const TSharedPtr<FJsonValue>& Value : *ScriptValues)
			{
				const TSharedPtr<FJsonObject> ScriptObject = Value.IsValid() ? Value->AsObject() : nullptr;
				if (!ScriptObject.IsValid() || GetStringField(ScriptObject, TEXT("Usage")) != Usage)
				{
					continue;
				}
				if (Seen++ != Occurrence)
				{
					continue;
				}

				Applied += OverlayExistingRapidIteration(Script, GetArrayField(ScriptObject, TEXT("Parameters")));
				break;
			}
			++Occurrence;
		}
		return Applied;
	}

	void ApplyJsonValueToBinder(FFactorySeedBinder& Binder, const FString& ModuleName, const FString& InputName, const TSharedPtr<FJsonValue>& JsonValue)
	{
		if (!JsonValue.IsValid() || JsonValue->IsNull())
		{
			return;
		}

		if (JsonValue->Type == EJson::String)
		{
			Binder.SetEnum(ModuleName, InputName, JsonValue->AsString());
			return;
		}

		if (JsonValue->Type == EJson::Number)
		{
			float FloatValue = static_cast<float>(JsonValue->AsNumber());
			if (InputName.Equals(TEXT("Spawn Count"), ESearchCase::IgnoreCase))
			{
				Binder.SetInt(ModuleName, InputName, FMath::RoundToInt(FloatValue));
				return;
			}
			Binder.SetFloat(ModuleName, InputName, FloatValue);
			return;
		}

		if (JsonValue->Type == EJson::Array)
		{
			const TArray<TSharedPtr<FJsonValue>>& Values = JsonValue->AsArray();
			TArray<float> Numbers;
			for (const TSharedPtr<FJsonValue>& Entry : Values)
			{
				if (Entry.IsValid() && Entry->Type == EJson::Number)
				{
					Numbers.Add(static_cast<float>(Entry->AsNumber()));
				}
			}
			if (Numbers.Num() >= 4)
			{
				FLinearColor Color(Numbers[0], Numbers[1], Numbers[2], Numbers[3]);
				if (InputName.Equals(TEXT("Color"), ESearchCase::IgnoreCase) && Color.A < 0.05f)
				{
					Color.A = 0.35f;
				}
				Binder.SetColor(ModuleName, InputName, Color);
				return;
			}
			if (Numbers.Num() >= 3)
			{
				Binder.SetVec3(ModuleName, InputName, FVector3f(Numbers[0], Numbers[1], Numbers[2]));
			}
		}
	}

	void ApplyJsonInputToBinder(FFactorySeedBinder& Binder, const FString& ModuleName, const FString& InputName, const TSharedPtr<FJsonObject>& ParameterObject)
	{
		if (!ParameterObject.IsValid())
		{
			return;
		}

		const FString EnumValue = GetStringField(ParameterObject, TEXT("Value"));
		const TSharedPtr<FJsonObject> TypeObject = GetObjectField(ParameterObject, TEXT("Type"));
		const bool bLooksEnum = TypeObject.IsValid() && !GetStringField(TypeObject, TEXT("Enum")).IsEmpty();
		if (!EnumValue.IsEmpty() && (bLooksEnum || InputName.Contains(TEXT("Mode"))))
		{
			Binder.SetEnum(ModuleName, InputName, EnumValue);
			return;
		}

		TArray<uint8> Bytes;
		if (!DecodeBase64Bytes(GetStringField(ParameterObject, TEXT("ValueBase64")), Bytes))
		{
			if (!EnumValue.IsEmpty())
			{
				Binder.SetEnum(ModuleName, InputName, EnumValue);
			}
			return;
		}

		if (Bytes.Num() == 16)
		{
			FLinearColor Color;
			FMemory::Memcpy(&Color, Bytes.GetData(), sizeof(FLinearColor));
			if (InputName.Equals(TEXT("Color"), ESearchCase::IgnoreCase) && Color.A < 0.05f)
			{
				Color.A = 0.35f;
			}
			Binder.SetColor(ModuleName, InputName, Color);
			return;
		}
		if (Bytes.Num() == 12)
		{
			FVector3f Vector;
			FMemory::Memcpy(&Vector, Bytes.GetData(), sizeof(FVector3f));
			Binder.SetVec3(ModuleName, InputName, Vector);
			return;
		}

		float FloatValue = 0.0f;
		if (!DecodeFloatValue(Bytes, FloatValue))
		{
			return;
		}

		if (InputName.Equals(TEXT("Spawn Count"), ESearchCase::IgnoreCase))
		{
			Binder.SetInt(ModuleName, InputName, FMath::RoundToInt(FloatValue));
			return;
		}
		if (ModuleName.Equals(TEXT("SpawnRate"), ESearchCase::IgnoreCase) &&
			InputName.Equals(TEXT("SpawnRate"), ESearchCase::IgnoreCase) &&
			FloatValue <= 0.0f)
		{
			FloatValue = 10.0f;
		}
		Binder.SetFloat(ModuleName, InputName, FloatValue);
	}

	const TCHAR* ModulePathForName(const FString& ModuleName)
	{
		if (ModuleName.StartsWith(TEXT("SpawnBurst")))
		{
			return SpawnBurstModulePath;
		}
		if (ModuleName.Equals(TEXT("SphereLocation"), ESearchCase::IgnoreCase))
		{
			return SphereLocationModulePath;
		}
		if (ModuleName.Equals(TEXT("BoxLocation"), ESearchCase::IgnoreCase))
		{
			return BoxLocationModulePath;
		}
		if (ModuleName.Equals(TEXT("CylinderLocation"), ESearchCase::IgnoreCase))
		{
			return CylinderLocationModulePath;
		}
		if (ModuleName.Equals(TEXT("GravityForce"), ESearchCase::IgnoreCase))
		{
			return GravityForceModulePath;
		}
		if (ModuleName.Equals(TEXT("Drag"), ESearchCase::IgnoreCase))
		{
			return DragModulePath;
		}
		return nullptr;
	}

	ENiagaraScriptUsage ModuleUsageForName(const FString& ModuleName)
	{
		if (ModuleName.StartsWith(TEXT("SpawnBurst")))
		{
			return ENiagaraScriptUsage::EmitterUpdateScript;
		}
		if (ModuleName.Equals(TEXT("GravityForce"), ESearchCase::IgnoreCase) || ModuleName.Equals(TEXT("Drag"), ESearchCase::IgnoreCase))
		{
			return ENiagaraScriptUsage::ParticleUpdateScript;
		}
		return ENiagaraScriptUsage::ParticleSpawnScript;
	}

	void ApplyModulesObject(FFactorySeedBinder& Binder, const TSharedPtr<FJsonObject>& ModulesObject, TSet<FString>& EnsuredModules)
	{
		if (!ModulesObject.IsValid())
		{
			return;
		}

		for (const TPair<FString, TSharedPtr<FJsonValue>>& ModulePair : ModulesObject->Values)
		{
			const TSharedPtr<FJsonObject> Inputs = ModulePair.Value.IsValid() ? ModulePair.Value->AsObject() : nullptr;
			if (!Inputs.IsValid())
			{
				continue;
			}

			const FString& ModuleName = ModulePair.Key;
			if (!EnsuredModules.Contains(ModuleName))
			{
				if (const TCHAR* Path = ModulePathForName(ModuleName))
				{
					Binder.EnsureModule(ModuleUsageForName(ModuleName), Path, ModuleName);
				}
				EnsuredModules.Add(ModuleName);
			}

			for (const TPair<FString, TSharedPtr<FJsonValue>>& InputPair : Inputs->Values)
			{
				ApplyJsonValueToBinder(Binder, ModuleName, InputPair.Key, InputPair.Value);
			}
		}
	}

	FString NonEmptyMode(const TSharedPtr<FJsonObject>& Object, const TCHAR* FieldName, const FString& Fallback)
	{
		const FString Value = GetStringField(Object, FieldName);
		if (Value.IsEmpty() || Value.Equals(TEXT("Unset"), ESearchCase::IgnoreCase))
		{
			return Fallback;
		}
		return Value;
	}

	void EnsureInitializeParticleAndSpawnRate(FFactorySeedBinder& Binder, const TSharedPtr<FJsonObject>& EmitterObject)
	{
		const TSharedPtr<FJsonObject> Modules = GetObjectField(EmitterObject, TEXT("Modules"));
		const TSharedPtr<FJsonObject> Init = GetObjectField(Modules, TEXT("InitializeParticle"));
		const TSharedPtr<FJsonObject> Spawn = GetObjectField(Modules, TEXT("SpawnRate"));

		const FString LifetimeMode = NonEmptyMode(Init, TEXT("Lifetime Mode"), TEXT("Random"));
		const FString SpriteSizeMode = NonEmptyMode(Init, TEXT("Sprite Size Mode"), TEXT("Random Uniform"));
		const FString ColorMode = NonEmptyMode(Init, TEXT("Color Mode"), TEXT("Direct Set"));
		const FString RotationMode = NonEmptyMode(Init, TEXT("Sprite Rotation Mode"), TEXT("Random"));
		const FString PositionMode = NonEmptyMode(Init, TEXT("Position Mode"), TEXT("Simulation Position"));

		float SpawnProbability = 1.0f;
		double ParsedProbability = 1.0;
		if (Spawn.IsValid() && Spawn->TryGetNumberField(TEXT("Spawn Probability"), ParsedProbability) && ParsedProbability > 0.0)
		{
			SpawnProbability = static_cast<float>(FMath::Min(1.0, ParsedProbability));
		}

		Binder.SetEnum(TEXT("InitializeParticle"), TEXT("Lifetime Mode"), LifetimeMode);
		Binder.SetEnum(TEXT("InitializeParticle"), TEXT("Sprite Size Mode"), SpriteSizeMode);
		Binder.SetEnum(TEXT("InitializeParticle"), TEXT("Color Mode"), ColorMode);
		Binder.SetEnum(TEXT("InitializeParticle"), TEXT("Sprite Rotation Mode"), RotationMode);
		Binder.SetEnum(TEXT("InitializeParticle"), TEXT("Position Mode"), PositionMode);
		Binder.SetFloat(TEXT("SpawnRate"), TEXT("Spawn Probability"), SpawnProbability);

		UE_LOG(LogCommonEFXSnapshotV2, Display,
			TEXT("Initialize Particle modes: Lifetime=%s SpriteSize=%s Color=%s Rotation=%s Position=%s | Spawn Probability=%f"),
			*LifetimeMode, *SpriteSizeMode, *ColorMode, *RotationMode, *PositionMode, SpawnProbability);
	}

	FString ResolveHandleUniqueName(UNiagaraSystem* System, UNiagaraEmitter* Emitter, const FString& Fallback)
	{
		if (System && Emitter)
		{
			for (const FNiagaraEmitterHandle& Handle : System->GetEmitterHandles())
			{
				if (Handle.GetInstance().Emitter != Emitter)
				{
					continue;
				}

				const FString InstanceName = Handle.GetUniqueInstanceName();
				if (!InstanceName.IsEmpty())
				{
					return InstanceName;
				}
				if (UNiagaraEmitter* Instance = Handle.GetInstance().Emitter)
				{
					const FString EmitterUnique = Instance->GetUniqueEmitterName();
					return EmitterUnique.IsEmpty() ? Handle.GetName().ToString() : EmitterUnique;
				}
				return Handle.GetName().ToString();
			}
		}
		return Fallback;
	}

	int32 ApplyFactorySeedOverrides(FVersionedNiagaraEmitterData* EmitterData, const FString& UniqueName, const TSharedPtr<FJsonObject>& EmitterObject, TArray<FString>& OutMissingAssets)
	{
		if (!EmitterData || !EmitterObject.IsValid())
		{
			return 0;
		}
		(void)OutMissingAssets;

		FFactorySeedBinder Binder;
		Binder.Data = EmitterData;
		Binder.UniqueName = UniqueName;

		TSet<FString> EnsuredModules;
		int32 Applied = 0;
		const TArray<TSharedPtr<FJsonValue>>* ScriptValues = GetArrayField(EmitterObject, TEXT("Scripts"));
		if (ScriptValues)
		{
			for (const TSharedPtr<FJsonValue>& ScriptValue : *ScriptValues)
			{
				const TSharedPtr<FJsonObject> ScriptObject = ScriptValue.IsValid() ? ScriptValue->AsObject() : nullptr;
				const TArray<TSharedPtr<FJsonValue>>* ParameterValues = GetArrayField(ScriptObject, TEXT("Parameters"));
				if (!ParameterValues)
				{
					continue;
				}

				for (const TSharedPtr<FJsonValue>& ParameterValue : *ParameterValues)
				{
					const TSharedPtr<FJsonObject> ParameterObject = ParameterValue.IsValid() ? ParameterValue->AsObject() : nullptr;
					if (!ParameterObject.IsValid())
					{
						continue;
					}

					FString ModuleName;
					FString InputName;
					if (!ParseConstantModuleInput(GetStringField(ParameterObject, TEXT("Name")), ModuleName, InputName))
					{
						continue;
					}

					if (!EnsuredModules.Contains(ModuleName))
					{
						if (const TCHAR* Path = ModulePathForName(ModuleName))
						{
							Binder.EnsureModule(ModuleUsageForName(ModuleName), Path, ModuleName);
						}
						EnsuredModules.Add(ModuleName);
					}

					ApplyJsonInputToBinder(Binder, ModuleName, InputName, ParameterObject);
					++Applied;
				}
			}
		}

		ApplyModulesObject(Binder, GetObjectField(EmitterObject, TEXT("Modules")), EnsuredModules);
		EnsureInitializeParticleAndSpawnRate(Binder, EmitterObject);

		Applied += OverlayEmitterRapidIteration(EmitterData, ScriptValues);
		UE_LOG(LogCommonEFXSnapshotV2, Display,
			TEXT("Factory seed overrides applied for %s (%d inputs, unique=%s)"),
			*UniqueName, Applied, *UniqueName);
		return Applied;
	}

	// ---------------------------------------------------------------------------
	// Emitter export
	// ---------------------------------------------------------------------------

	void ExportPixelEmitter(const FNiagaraEmitterHandle& Handle, int32 Index, TArray<TSharedPtr<FJsonValue>>& OutEmitters, int32& OutRendererCount, int32& OutEventCount, int32& OutStageCount, int32& OutNodeCount)
	{
		FVersionedNiagaraEmitterData* EmitterData = Handle.GetEmitterData();
		if (!EmitterData)
		{
			return;
		}

		TSharedPtr<FJsonObject> EmitterObject = MakeShared<FJsonObject>();
		EmitterObject->SetNumberField(TEXT("Index"), Index);
		EmitterObject->SetStringField(TEXT("Name"), Handle.GetName().ToString());
		EmitterObject->SetStringField(TEXT("HandleId"), MakeGuidString(Handle.GetId()));
		EmitterObject->SetStringField(TEXT("VersionGuid"), MakeGuidString(Handle.GetInstance().Version));
		EmitterObject->SetNumberField(TEXT("MajorVersion"), EmitterData->Version.MajorVersion);
		EmitterObject->SetNumberField(TEXT("MinorVersion"), EmitterData->Version.MinorVersion);
		EmitterObject->SetBoolField(TEXT("Enabled"), Handle.GetIsEnabled());

		static const TSet<FName> EmitterSkipNames =
		{
			TEXT("Version"),
			TEXT("EventHandlerScriptProps"),
			TEXT("UpdateScriptProps"),
			TEXT("SpawnScriptProps"),
			TEXT("EmitterSpawnScriptProps"),
			TEXT("EmitterUpdateScriptProps"),
			TEXT("GraphSource"),
			TEXT("ScratchPads"),
			TEXT("ParentScratchPads"),
			TEXT("VersionedParent"),
			TEXT("VersionedParentAtLastMerge"),
			TEXT("RendererBindings"),
			TEXT("RendererBindingsExternalObjects"),
			TEXT("ResolvedDIBindings"),
			TEXT("GPUComputeScript"),
			TEXT("EditorData"),
			TEXT("EditorParameters"),
			TEXT("SimStageExecutionLoopEditorData"),
		};

		TArray<TSharedPtr<FJsonValue>> EmitterProperties;
		ExportPropertiesFromStruct(FVersionedNiagaraEmitterData::StaticStruct(), EmitterData, nullptr, EmitterSkipNames, true, EmitterProperties);
		EmitterObject->SetArrayField(TEXT("Properties"), EmitterProperties);

		TSharedPtr<FJsonObject> UsageIds = MakeShared<FJsonObject>();
		ExportUsageId(UsageIds, TEXT("EmitterSpawnScript"), EmitterData->EmitterSpawnScriptProps.Script);
		ExportUsageId(UsageIds, TEXT("EmitterUpdateScript"), EmitterData->EmitterUpdateScriptProps.Script);
		ExportUsageId(UsageIds, TEXT("ParticleSpawnScript"), EmitterData->SpawnScriptProps.Script);
		ExportUsageId(UsageIds, TEXT("ParticleUpdateScript"), EmitterData->UpdateScriptProps.Script);
		ExportUsageId(UsageIds, TEXT("ParticleGPUComputeScript"), EmitterData->GetGPUComputeScript());
		EmitterObject->SetObjectField(TEXT("UsageIds"), UsageIds);

		TSharedPtr<FJsonObject> Usages = MakeShared<FJsonObject>();
		ExportUsage(Usages, TEXT("EmitterSpawnScript"), EmitterData->EmitterSpawnScriptProps.Script);
		ExportUsage(Usages, TEXT("EmitterUpdateScript"), EmitterData->EmitterUpdateScriptProps.Script);
		ExportUsage(Usages, TEXT("ParticleSpawnScript"), EmitterData->SpawnScriptProps.Script);
		ExportUsage(Usages, TEXT("ParticleUpdateScript"), EmitterData->UpdateScriptProps.Script);
		ExportUsage(Usages, TEXT("ParticleGPUComputeScript"), EmitterData->GetGPUComputeScript());
		EmitterObject->SetObjectField(TEXT("Usages"), Usages);

		// Recorded in the same order as ImportScripts applies them.  This has to be an explicit list because
		// ForEachScript skips the emitter spawn/update and simulation stage scripts, and those carry the emitter
		// state / spawn rate module overrides that drive the effect.
		TArray<TSharedPtr<FJsonValue>> ScriptValues;
		auto ExportScript = [&ScriptValues](UNiagaraScript* Script)
			{
				if (TSharedPtr<FJsonObject> ScriptObject = ExportScriptParameters(Script))
				{
					ScriptValues.Add(MakeShared<FJsonValueObject>(ScriptObject));
				}
			};
		ExportScript(EmitterData->SpawnScriptProps.Script);
		ExportScript(EmitterData->UpdateScriptProps.Script);
		ExportScript(EmitterData->EmitterSpawnScriptProps.Script);
		ExportScript(EmitterData->EmitterUpdateScriptProps.Script);
		ExportScript(EmitterData->GetGPUComputeScript());
		for (const FNiagaraEventScriptProperties& EventHandler : EmitterData->EventHandlerScriptProps)
		{
			ExportScript(EventHandler.Script);
		}
		for (UNiagaraSimulationStageBase* SimulationStage : EmitterData->GetSimulationStages())
		{
			if (SimulationStage)
			{
				ExportScript(SimulationStage->Script);
			}
		}
		EmitterObject->SetArrayField(TEXT("Scripts"), ScriptValues);

		TArray<TSharedPtr<FJsonValue>> EventHandlers;
		for (const FNiagaraEventScriptProperties& EventHandler : EmitterData->EventHandlerScriptProps)
		{
			TSharedPtr<FJsonObject> HandlerObject = MakeShared<FJsonObject>();

			TArray<TSharedPtr<FJsonValue>> HandlerProperties;
			ExportPropertiesFromStruct(FNiagaraEventScriptProperties::StaticStruct(), &EventHandler, nullptr, TSet<FName>({ TEXT("Script") }), false, HandlerProperties);
			HandlerObject->SetArrayField(TEXT("Properties"), HandlerProperties);
			HandlerObject->SetStringField(TEXT("ScriptUsageId"), EventHandler.Script ? MakeGuidString(EventHandler.Script->GetUsageId()) : FString());
			HandlerObject->SetStringField(TEXT("ScriptName"), EventHandler.Script ? EventHandler.Script->GetName() : FString());

			EventHandlers.Add(MakeShared<FJsonValueObject>(HandlerObject));
			++OutEventCount;
		}
		EmitterObject->SetArrayField(TEXT("EventHandlers"), EventHandlers);

		TArray<TSharedPtr<FJsonValue>> SimulationStages;
		for (UNiagaraSimulationStageBase* SimulationStage : EmitterData->GetSimulationStages())
		{
			if (!SimulationStage)
			{
				continue;
			}

			TSharedPtr<FJsonObject> StageObject = MakeShared<FJsonObject>();
			StageObject->SetStringField(TEXT("Class"), SimulationStage->GetClass()->GetPathName());
			StageObject->SetStringField(TEXT("Name"), SimulationStage->GetName());
			StageObject->SetStringField(TEXT("ScriptUsageId"), SimulationStage->Script ? MakeGuidString(SimulationStage->Script->GetUsageId()) : FString());
			StageObject->SetStringField(TEXT("ScriptName"), SimulationStage->Script ? SimulationStage->Script->GetName() : FString());

			TArray<TSharedPtr<FJsonValue>> StageProperties;
			static const TSet<FName> StageSkipNames = { TEXT("Script"), TEXT("OuterEmitterVersion"), TEXT("MergeId") };
			ExportPropertiesFromObject(SimulationStage, StageSkipNames, false, StageProperties);
			StageObject->SetArrayField(TEXT("Properties"), StageProperties);

			SimulationStages.Add(MakeShared<FJsonValueObject>(StageObject));
			++OutStageCount;
		}
		EmitterObject->SetArrayField(TEXT("SimulationStages"), SimulationStages);

		TArray<TSharedPtr<FJsonValue>> Renderers;
		for (UNiagaraRendererProperties* Renderer : EmitterData->GetRenderers())
		{
			if (!Renderer)
			{
				continue;
			}

			TSharedPtr<FJsonObject> RendererObject = MakeShared<FJsonObject>();
			RendererObject->SetStringField(TEXT("Class"), Renderer->GetClass()->GetPathName());
			RendererObject->SetStringField(TEXT("Name"), Renderer->GetName());

			static const TSet<FName> RendererSkipNames = { TEXT("OuterEmitterVersion"), TEXT("MergeId") };
			TArray<TSharedPtr<FJsonValue>> RendererProperties;
			ExportPropertiesFromObject(Renderer, RendererSkipNames, false, RendererProperties);
			RendererObject->SetArrayField(TEXT("Properties"), RendererProperties);

			Renderers.Add(MakeShared<FJsonValueObject>(RendererObject));
			++OutRendererCount;
		}
		EmitterObject->SetArrayField(TEXT("Renderers"), Renderers);

		UNiagaraGraph* Graph = GetGraphFromSource(EmitterData->GraphSource);
		const FString GraphKey = MakeGraphKey(EmitterData->EmitterUpdateScriptProps.Script, Index);
		EmitterObject->SetObjectField(TEXT("Graph"), ExportGraph(Graph, GraphKey, OutNodeCount));

		OutEmitters.Add(MakeShared<FJsonValueObject>(EmitterObject));
	}

	// ---------------------------------------------------------------------------
	// Emitter import
	// ---------------------------------------------------------------------------

	struct FEmitterImportContext
	{
		UNiagaraEmitter* Emitter = nullptr;
		FVersionedNiagaraEmitterData* EmitterData = nullptr;
		FGuid VersionGuid;
		FString Name;
		TSharedPtr<FJsonObject> EmitterObject;
		bool bSeedFactoryGraph = false;
	};

	bool TrySetEmitterHandleId(FNiagaraEmitterHandle& Handle, const FGuid& HandleId)
	{
		FStructProperty* IdProperty = FindFProperty<FStructProperty>(FNiagaraEmitterHandle::StaticStruct(), TEXT("Id"));
		if (!IdProperty)
		{
			return false;
		}

		*IdProperty->ContainerPtrToValuePtr<FGuid>(&Handle) = HandleId;

		if (FNameProperty* IdNameProperty = FindFProperty<FNameProperty>(FNiagaraEmitterHandle::StaticStruct(), TEXT("IdName")))
		{
			*IdNameProperty->ContainerPtrToValuePtr<FName>(&Handle) = FName(*HandleId.ToString());
		}

		return true;
	}

	void SetEmitterHandleEnabled(FNiagaraEmitterHandle& Handle, bool bEnabled)
	{
		if (FBoolProperty* EnabledProperty = FindFProperty<FBoolProperty>(FNiagaraEmitterHandle::StaticStruct(), TEXT("bIsEnabled")))
		{
			EnabledProperty->SetPropertyValue_InContainer(&Handle, bEnabled);
		}
	}

	void ImportRenderers(UNiagaraEmitter* Emitter, FVersionedNiagaraEmitterData* EmitterData, const TArray<TSharedPtr<FJsonValue>>* RendererValues, const FString& Context, TArray<FString>& OutMissingAssets, int32& OutCount)
	{
		if (!Emitter || !EmitterData || !RendererValues)
		{
			return;
		}

		for (const TSharedPtr<FJsonValue>& Value : *RendererValues)
		{
			const TSharedPtr<FJsonObject> RendererObject = Value.IsValid() ? Value->AsObject() : nullptr;
			if (!RendererObject.IsValid())
			{
				continue;
			}

			const FString ClassPath = GetStringField(RendererObject, TEXT("Class"));
			UClass* RendererClass = LoadClass<UNiagaraRendererProperties>(nullptr, *ClassPath);
			if (!RendererClass)
			{
				OutMissingAssets.Add(ClassPath);
				continue;
			}

			UNiagaraRendererProperties* Renderer = NewObject<UNiagaraRendererProperties>(Emitter, RendererClass, NAME_None, RF_Transactional);
			if (!Renderer)
			{
				continue;
			}

			ImportPropertiesIntoObject(Renderer, GetArrayField(RendererObject, TEXT("Properties")), Context, OutMissingAssets);

			Emitter->AddRenderer(Renderer, EmitterData->Version.VersionGuid);
			++OutCount;
		}
	}

	void ImportEventHandlers(UNiagaraEmitter* Emitter, FVersionedNiagaraEmitterData* EmitterData, const TArray<TSharedPtr<FJsonValue>>* HandlerValues, const TMap<FGuid, FGuid>& HandleIdMap, const FString& Context, TArray<FString>& OutMissingAssets, int32& OutCount)
	{
		if (!Emitter || !EmitterData || !HandlerValues)
		{
			return;
		}

		static const TSet<FName> SkipNames = { TEXT("Script") };

		for (const TSharedPtr<FJsonValue>& Value : *HandlerValues)
		{
			const TSharedPtr<FJsonObject> HandlerObject = Value.IsValid() ? Value->AsObject() : nullptr;
			if (!HandlerObject.IsValid())
			{
				continue;
			}

			FNiagaraEventScriptProperties EventHandler;
			ImportPropertiesIntoStruct(&EventHandler, FNiagaraEventScriptProperties::StaticStruct(), Emitter, GetArrayField(HandlerObject, TEXT("Properties")), Context, OutMissingAssets, SkipNames);

			if (EventHandler.SourceEmitterID.IsValid())
			{
				if (const FGuid* NewHandleId = HandleIdMap.Find(EventHandler.SourceEmitterID))
				{
					EventHandler.SourceEmitterID = *NewHandleId;
				}
				else
				{
					UE_LOG(LogCommonEFXSnapshotV2, Warning, TEXT("%s: event handler source emitter %s could not be remapped."), *Context, *EventHandler.SourceEmitterID.ToString());
				}
			}

			const FString ScriptName = GetStringField(HandlerObject, TEXT("ScriptName"));
			UNiagaraScript* Script = NewObject<UNiagaraScript>(
				Emitter,
				MakeUniqueObjectName(Emitter, UNiagaraScript::StaticClass(), FName(*(ScriptName.IsEmpty() ? FString(TEXT("EventScript")) : ScriptName))),
				RF_Transactional);
			Script->SetUsage(ENiagaraScriptUsage::ParticleEventScript);
			Script->SetLatestSource(EmitterData->GraphSource);

			FGuid ScriptUsageId;
			if (FGuid::Parse(GetStringField(HandlerObject, TEXT("ScriptUsageId")), ScriptUsageId))
			{
				Script->SetUsageId(ScriptUsageId);
			}

			EventHandler.Script = Script;
			Emitter->AddEventHandler(EventHandler, EmitterData->Version.VersionGuid);
			++OutCount;
		}
	}

	void ImportSimulationStages(UNiagaraEmitter* Emitter, FVersionedNiagaraEmitterData* EmitterData, const TArray<TSharedPtr<FJsonValue>>* StageValues, const FString& Context, TArray<FString>& OutMissingAssets, int32& OutCount)
	{
		if (!Emitter || !EmitterData || !StageValues)
		{
			return;
		}

		static const TSet<FName> SkipNames = { TEXT("Script"), TEXT("OuterEmitterVersion"), TEXT("MergeId") };

		for (const TSharedPtr<FJsonValue>& Value : *StageValues)
		{
			const TSharedPtr<FJsonObject> StageObject = Value.IsValid() ? Value->AsObject() : nullptr;
			if (!StageObject.IsValid())
			{
				continue;
			}

			const FString ClassPath = GetStringField(StageObject, TEXT("Class"));
			UClass* StageClass = LoadClass<UNiagaraSimulationStageBase>(nullptr, *ClassPath);
			if (!StageClass)
			{
				OutMissingAssets.Add(ClassPath);
				continue;
			}

			UNiagaraSimulationStageBase* SimulationStage = NewObject<UNiagaraSimulationStageBase>(Emitter, StageClass, NAME_None, RF_Transactional);
			if (!SimulationStage)
			{
				continue;
			}

			const FString ScriptName = GetStringField(StageObject, TEXT("ScriptName"));
			SimulationStage->Script = NewObject<UNiagaraScript>(
				SimulationStage,
				MakeUniqueObjectName(SimulationStage, UNiagaraScript::StaticClass(), FName(*(ScriptName.IsEmpty() ? FString(TEXT("SimulationStage")) : ScriptName))),
				RF_Transactional);
			SimulationStage->Script->SetUsage(ENiagaraScriptUsage::ParticleSimulationStageScript);
			SimulationStage->Script->SetLatestSource(EmitterData->GraphSource);

			FGuid ScriptUsageId;
			if (FGuid::Parse(GetStringField(StageObject, TEXT("ScriptUsageId")), ScriptUsageId))
			{
				SimulationStage->Script->SetUsageId(ScriptUsageId);
			}

			ImportPropertiesIntoObject(SimulationStage, GetArrayField(StageObject, TEXT("Properties")), Context, OutMissingAssets, SkipNames);

			Emitter->AddSimulationStage(SimulationStage, EmitterData->Version.VersionGuid);
			++OutCount;
		}
	}

	bool CreateEmitter(UNiagaraSystem* System, const TSharedPtr<FJsonObject>& EmitterObject, int32 EmitterIndex, FEmitterImportContext& OutContext, FNiagaraEmitterHandle& OutHandle, TArray<FString>& OutMissingAssets, int32& OutRendererCount, int32& OutNodeCount)
	{
		if (!System || !EmitterObject.IsValid())
		{
			return false;
		}

		FString EmitterName = GetStringField(EmitterObject, TEXT("Name"));
		if (EmitterName.IsEmpty())
		{
			EmitterName = FString::Printf(TEXT("Emitter%d"), EmitterIndex);
		}

		// Keep the recorded version guid even when it is invalid: the source emitters can use the default (zero)
		// version, and versioning is disabled on these inline emitters, so GetEmitterData always resolves to the
		// latest data regardless of the guid.
		const FGuid EmitterVersionGuid = GetGuidField(EmitterObject, TEXT("VersionGuid"));

		UNiagaraEmitter* Emitter = NewObject<UNiagaraEmitter>(System, FName(*EmitterName), RF_Transactional);
		if (!Emitter)
		{
			return false;
		}

		Emitter->bIsInheritable = false;

		const TSharedPtr<FJsonObject> GraphObject = GetObjectField(EmitterObject, TEXT("Graph"));
		const FString NodesText = GetStringField(GraphObject, TEXT("NodesText"));
		const bool bSeedFactoryGraph = NodesText.IsEmpty();
		UNiagaraEmitterFactoryNew::InitializeEmitter(Emitter, bSeedFactoryGraph);

		FVersionedNiagaraEmitterData* EmitterData = Emitter->GetLatestEmitterData();
		if (!EmitterData)
		{
			return false;
		}

		// Generic EFX snapshots send an empty VersionGuid. Overwriting the factory guid with
		// 0 makes runtime lookups miss the emitter data: the stack still shows, but nothing spawns.
		if (EmitterVersionGuid.IsValid())
		{
			EmitterData->Version.VersionGuid = EmitterVersionGuid;
		}
		if (EmitterObject->HasField(TEXT("MajorVersion")))
		{
			EmitterData->Version.MajorVersion = GetIntField(EmitterObject, TEXT("MajorVersion"));
		}
		if (EmitterObject->HasField(TEXT("MinorVersion")))
		{
			EmitterData->Version.MinorVersion = GetIntField(EmitterObject, TEXT("MinorVersion"));
		}

		Emitter->SetUniqueEmitterName(EmitterName);

		const TSharedPtr<FJsonObject> UsageIds = GetObjectField(EmitterObject, TEXT("UsageIds"));
		ImportUsageId(UsageIds, TEXT("EmitterSpawnScript"), EmitterData->EmitterSpawnScriptProps.Script);
		ImportUsageId(UsageIds, TEXT("EmitterUpdateScript"), EmitterData->EmitterUpdateScriptProps.Script);
		ImportUsageId(UsageIds, TEXT("ParticleSpawnScript"), EmitterData->SpawnScriptProps.Script);
		ImportUsageId(UsageIds, TEXT("ParticleUpdateScript"), EmitterData->UpdateScriptProps.Script);
		ImportUsageId(UsageIds, TEXT("ParticleGPUComputeScript"), EmitterData->GetGPUComputeScript());

		const TSharedPtr<FJsonObject> Usages = GetObjectField(EmitterObject, TEXT("Usages"));
		ImportUsage(Usages, TEXT("EmitterSpawnScript"), EmitterData->EmitterSpawnScriptProps.Script);
		ImportUsage(Usages, TEXT("EmitterUpdateScript"), EmitterData->EmitterUpdateScriptProps.Script);
		ImportUsage(Usages, TEXT("ParticleSpawnScript"), EmitterData->SpawnScriptProps.Script);
		ImportUsage(Usages, TEXT("ParticleUpdateScript"), EmitterData->UpdateScriptProps.Script);
		ImportUsage(Usages, TEXT("ParticleGPUComputeScript"), EmitterData->GetGPUComputeScript());

		const FString Context = FString::Printf(TEXT("Emitter %s"), *EmitterName);
		if (bSeedFactoryGraph)
		{
			// Keep factory allocation / sim target. A partial FixedCount restore with a zero
			// PreAllocationCount produces a valid-looking emitter that never allocates particles.
			UE_LOG(LogCommonEFXSnapshotV2, Display, TEXT("%s: keeping factory emitter properties because the snapshot has no graph."), *Context);
		}
		else
		{
			ImportPropertiesIntoStruct(EmitterData, FVersionedNiagaraEmitterData::StaticStruct(), Emitter, GetArrayField(EmitterObject, TEXT("Properties")), Context, OutMissingAssets);
		}

		OutNodeCount += ImportGraph(GetGraphFromSource(EmitterData->GraphSource), GraphObject, Context, OutMissingAssets);

		const TArray<TSharedPtr<FJsonValue>>* RendererValues = GetArrayField(EmitterObject, TEXT("Renderers"));
		if (bSeedFactoryGraph)
		{
			// Factory-new emitters already have a Sprite renderer wired to the default graph. Replacing it
			// with a partial renderer from JSON (no material, empty mesh array) crashes Niagara Editor on open.
			UE_LOG(LogCommonEFXSnapshotV2, Display, TEXT("%s: keeping factory renderers because the snapshot has no graph."), *Context);
		}
		else
		{
			ImportRenderers(Emitter, EmitterData, RendererValues, Context, OutMissingAssets, OutRendererCount);
		}

		// Programmatically created emitters never run PostLoad, which is where FVersionedNiagaraEmitterData
		// initializes non-reflected runtime state (RuntimeEstimation / StatDatabase). PostEditChange runs that
		// initialization; without it, runtime estimation asserts on a null critical section and crashes.
		Emitter->PostEditChange();

		const FGuid HandleVersion = EmitterData->Version.VersionGuid;
		OutHandle = FNiagaraEmitterHandle(*Emitter, HandleVersion);

		const FGuid RecordedHandleId = GetGuidField(EmitterObject, TEXT("HandleId"));
		if (RecordedHandleId.IsValid())
		{
			if (!TrySetEmitterHandleId(OutHandle, RecordedHandleId))
			{
				UE_LOG(LogCommonEFXSnapshotV2, Warning, TEXT("%s: could not restore the emitter handle id; references will be remapped."), *Context);
			}
		}

		SetEmitterHandleEnabled(OutHandle, GetBoolField(EmitterObject, TEXT("Enabled")));

		OutContext.Emitter = Emitter;
		OutContext.EmitterData = EmitterData;
		OutContext.VersionGuid = HandleVersion;
		OutContext.Name = EmitterName;
		OutContext.EmitterObject = EmitterObject;
		OutContext.bSeedFactoryGraph = bSeedFactoryGraph;
		return true;
	}

	void RemapEmitterNodeReferences(UNiagaraGraph* Graph, UNiagaraSystem* System, const TMap<FGuid, FGuid>& HandleIdMap)
	{
		if (!Graph || !System)
		{
			return;
		}

		for (const TObjectPtr<UEdGraphNode>& NodePtr : Graph->Nodes)
		{
			UEdGraphNode* Node = NodePtr.Get();
			if (!Node)
			{
				continue;
			}

			FStructProperty* HandleIdProperty = FindFProperty<FStructProperty>(Node->GetClass(), TEXT("EmitterHandleId"));
			if (!HandleIdProperty)
			{
				continue;
			}

			FGuid* HandleId = HandleIdProperty->ContainerPtrToValuePtr<FGuid>(Node);
			if (const FGuid* NewHandleId = HandleIdMap.Find(*HandleId))
			{
				*HandleId = *NewHandleId;
			}

			if (FObjectPropertyBase* OwnerProperty = FindFProperty<FObjectPropertyBase>(Node->GetClass(), TEXT("OwnerSystem")))
			{
				OwnerProperty->SetObjectPropertyValue_InContainer(Node, System);
			}
		}
	}

	void LayoutSystemOverviewGraph(UNiagaraSystem* System)
	{
		if (!System)
		{
			return;
		}

		UNiagaraSystemEditorData* EditorData = Cast<UNiagaraSystemEditorData>(System->GetEditorData());
		if (!EditorData)
		{
			return;
		}

		// The overview graph is populated when a system is created (with no emitters) and the editor only adds the
		// missing emitter nodes when an emitter is toggled.  Synchronize here so the imported asset shows every
		// emitter node immediately after import.
		EditorData->SynchronizeOverviewGraphWithSystem(*System);

		UEdGraph* OverviewGraph = EditorData->GetSystemOverviewGraph();
		if (!OverviewGraph)
		{
			return;
		}

		TMap<FGuid, int32> HandleOrder;
		const TArray<FNiagaraEmitterHandle>& Handles = System->GetEmitterHandles();
		for (int32 HandleIndex = 0; HandleIndex < Handles.Num(); ++HandleIndex)
		{
			HandleOrder.Add(Handles[HandleIndex].GetId(), HandleIndex);
		}

		// Deterministic layout: system node on the left, then one column per emitter in handle order.
		constexpr int32 ColumnSpacing = 250;
		int32 EmitterNodeCount = 0;
		for (UEdGraphNode* Node : OverviewGraph->Nodes)
		{
			UNiagaraOverviewNode* OverviewNode = Cast<UNiagaraOverviewNode>(Node);
			if (!OverviewNode)
			{
				continue;
			}

			const FGuid EmitterHandleId = OverviewNode->GetEmitterHandleGuid();
			if (!EmitterHandleId.IsValid())
			{
				Node->NodePosX = -ColumnSpacing;
				Node->NodePosY = 0;
				continue;
			}

			if (const int32* HandleIndex = HandleOrder.Find(EmitterHandleId))
			{
				Node->NodePosX = (*HandleIndex) * ColumnSpacing;
				Node->NodePosY = 0;
				++EmitterNodeCount;
			}
		}

		OverviewGraph->NotifyGraphChanged();

		UE_LOG(LogCommonEFXSnapshotV2, Display,
			TEXT("System overview graph repaired: %d emitter node(s) for %d emitter handle(s)."),
			EmitterNodeCount, Handles.Num());
	}

	void LogMissingAssets(const TArray<FString>& MissingAssets)
	{
		if (MissingAssets.Num() == 0)
		{
			return;
		}

		UE_LOG(LogCommonEFXSnapshotV2, Warning, TEXT("%d external asset reference(s) could not be resolved:"), MissingAssets.Num());
		for (const FString& MissingAsset : MissingAssets)
		{
			UE_LOG(LogCommonEFXSnapshotV2, Warning, TEXT("  Missing: %s"), *MissingAsset);
		}
	}

	void ResolveDestination(const FString& SourceSystemPath, FString& OutPackagePath, FString& OutAssetName)
	{
		const FString SourcePackageName = SourceSystemPath.IsEmpty() ? FString() : FPackageName::ObjectPathToPackageName(SourceSystemPath);

		if (!SourcePackageName.IsEmpty() && FPackageName::IsValidLongPackageName(SourcePackageName) && SourcePackageName.StartsWith(TEXT("/Game/")))
		{
			OutPackagePath = FPackageName::GetLongPackagePath(SourcePackageName);
			OutAssetName = FPackageName::GetShortName(SourcePackageName);
		}
		else
		{
			OutPackagePath = TEXT("/Game/CommonEFX");
			OutAssetName = TEXT("NiagaraSystem");
		}

		if (OutAssetName.IsEmpty())
		{
			OutAssetName = TEXT("NiagaraSystem");
		}

		OutAssetName += TEXT("_Rebuilt");
	}
}

bool FCommonEFXSnapshotV2::Export(UNiagaraSystem* System, const FString& FileName, FString& OutError)
{
	if (!System)
	{
		OutError = TEXT("未找到要导出的 Niagara System。");
		return false;
	}

	TSharedRef<FJsonObject> RootObject = MakeShared<FJsonObject>();
	RootObject->SetNumberField(TEXT("Version"), Version);
	RootObject->SetStringField(TEXT("SourceSystem"), System->GetPathName());
	RootObject->SetStringField(TEXT("SourceSystemClass"), System->GetClass()->GetPathName());
	RootObject->SetStringField(TEXT("EngineVersion"), FEngineVersion::Current().ToString());
	RootObject->SetStringField(TEXT("ExportedAt"), FDateTime::UtcNow().ToIso8601());

	TSharedPtr<FJsonObject> SystemObject = MakeShared<FJsonObject>();

	static const TSet<FName> SystemSkipNames =
	{
		TEXT("EmitterHandles"),
		TEXT("SystemSpawnScript"),
		TEXT("SystemUpdateScript"),
		TEXT("ExposedParameters"),
		TEXT("EffectType"),
		TEXT("ParameterCollectionOverrides"),
		TEXT("EditorData"),
		TEXT("EditorParameters"),
		TEXT("SystemCompiledData"),
	};

	TArray<TSharedPtr<FJsonValue>> SystemProperties;
	ExportPropertiesFromObject(System, SystemSkipNames, true, SystemProperties);
	SystemObject->SetArrayField(TEXT("Properties"), SystemProperties);

	SystemObject->SetStringField(TEXT("EffectType"), System->GetEffectType() ? System->GetEffectType()->GetPathName() : FString());

	if (const FArrayProperty* CollectionOverrides = FindFProperty<FArrayProperty>(UNiagaraSystem::StaticClass(), TEXT("ParameterCollectionOverrides")))
	{
		FScriptArrayHelper Helper(CollectionOverrides, CollectionOverrides->ContainerPtrToValuePtr<void>(System));
		if (Helper.Num() > 0)
		{
			UE_LOG(LogCommonEFXSnapshotV2, Warning, TEXT("System uses %d parameter collection override(s); v2 does not restore them."), Helper.Num());
		}
	}

	TSharedPtr<FJsonObject> SystemUsageIds = MakeShared<FJsonObject>();
	ExportUsageId(SystemUsageIds, TEXT("SystemSpawnScript"), System->GetSystemSpawnScript());
	ExportUsageId(SystemUsageIds, TEXT("SystemUpdateScript"), System->GetSystemUpdateScript());
	SystemObject->SetObjectField(TEXT("UsageIds"), SystemUsageIds);

	TArray<TSharedPtr<FJsonValue>> SystemScriptValues;
	if (TSharedPtr<FJsonObject> SpawnScriptObject = ExportScriptParameters(System->GetSystemSpawnScript()))
	{
		SystemScriptValues.Add(MakeShared<FJsonValueObject>(SpawnScriptObject));
	}
	if (TSharedPtr<FJsonObject> UpdateScriptObject = ExportScriptParameters(System->GetSystemUpdateScript()))
	{
		SystemScriptValues.Add(MakeShared<FJsonValueObject>(UpdateScriptObject));
	}
	SystemObject->SetArrayField(TEXT("Scripts"), SystemScriptValues);

	SystemObject->SetArrayField(TEXT("UserParameters"), ExportUserParameters(System));

	UNiagaraGraph* SystemGraph = System->GetSystemSpawnScript() ? GetGraphFromSource(System->GetSystemSpawnScript()->GetLatestSource()) : nullptr;
	int32 SystemNodeCount = 0;
	SystemObject->SetObjectField(TEXT("Graph"), ExportGraph(SystemGraph, MakeGraphKey(System->GetSystemSpawnScript(), 0), SystemNodeCount));

	RootObject->SetObjectField(TEXT("System"), SystemObject);

	TArray<TSharedPtr<FJsonValue>> Emitters;
	int32 RendererCount = 0;
	int32 EventHandlerCount = 0;
	int32 SimulationStageCount = 0;
	int32 NodeCount = SystemNodeCount;

	const TArray<FNiagaraEmitterHandle>& Handles = System->GetEmitterHandles();
	for (int32 Index = 0; Index < Handles.Num(); ++Index)
	{
		ExportPixelEmitter(Handles[Index], Index, Emitters, RendererCount, EventHandlerCount, SimulationStageCount, NodeCount);
	}
	RootObject->SetArrayField(TEXT("Emitters"), Emitters);

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

	UE_LOG(LogCommonEFXSnapshotV2, Display,
		TEXT("Exported Niagara snapshot v2: %s | emitters=%d renderers=%d eventHandlers=%d simulationStages=%d graphNodes=%d"),
		*FileName, Emitters.Num(), RendererCount, EventHandlerCount, SimulationStageCount, NodeCount);

	return true;
}

UNiagaraSystem* FCommonEFXSnapshotV2::Import(const TSharedPtr<FJsonObject>& RootObject, FString& OutError, const FString& DestinationPathOverride)
{
	if (!RootObject.IsValid())
	{
		OutError = TEXT("参数文件格式无效，无法解析 JSON。");
		return nullptr;
	}

	const FString SourceSystemPath = GetStringField(RootObject, TEXT("SourceSystem"));
	FString DestinationPath;
	FString DestinationName;
	ResolveDestination(SourceSystemPath, DestinationPath, DestinationName);
	if (!DestinationPathOverride.IsEmpty())
	{
		DestinationPath = DestinationPathOverride;
	}

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	IAssetTools& AssetTools = AssetToolsModule.Get();

	FString UniquePackageName;
	FString UniqueAssetName;
	AssetTools.CreateUniqueAssetName(
		FString::Printf(TEXT("%s/%s"), *DestinationPath, *DestinationName),
		TEXT(""),
		UniquePackageName,
		UniqueAssetName);

	// The factory class itself is not exported from NiagaraEditor, so resolve its class by path instead of
	// instantiating it directly (which would reference a non-exported static class symbol at link time).
	UClass* FactoryClass = LoadClass<UFactory>(nullptr, TEXT("/Script/NiagaraEditor.NiagaraSystemFactoryNew"));
	UFactory* Factory = FactoryClass ? NewObject<UFactory>(GetTransientPackage(), FactoryClass, NAME_None, RF_Transient) : nullptr;
	if (!Factory)
	{
		OutError = TEXT("无法创建 Niagara System 工厂，离线重建失败。");
		return nullptr;
	}

	UObject* CreatedObject = AssetTools.CreateAsset(
		UniqueAssetName,
		FPackageName::GetLongPackagePath(UniquePackageName),
		UNiagaraSystem::StaticClass(),
		Factory,
		TEXT("CommonEFX"));

	UNiagaraSystem* NewSystem = Cast<UNiagaraSystem>(CreatedObject);
	if (!NewSystem)
	{
		OutError = TEXT("创建新的 Niagara System 资产失败。");
		return nullptr;
	}

	// The factory may have queued a compile for the (still empty) system.  It must not run while the emitters are
	// being imported: two concurrent compilations share the same UNiagaraScript objects and abort each other's
	// tasks, which leaves most scripts without a compiled VM.  Only the final reconcile compile should run.
	NewSystem->KillAllActiveCompilations();

	UNiagaraScript* SystemSpawnScript = NewSystem->GetSystemSpawnScript();
	UNiagaraScript* SystemUpdateScript = NewSystem->GetSystemUpdateScript();

	const TSharedPtr<FJsonObject> SystemObject = GetObjectField(RootObject, TEXT("System"));
	if (SystemObject.IsValid())
	{
		const TSharedPtr<FJsonObject> UsageIds = GetObjectField(SystemObject, TEXT("UsageIds"));
		ImportUsageId(UsageIds, TEXT("SystemSpawnScript"), SystemSpawnScript);
		ImportUsageId(UsageIds, TEXT("SystemUpdateScript"), SystemUpdateScript);
	}

	TArray<FString> MissingAssets;

	if (SystemObject.IsValid())
	{
		ImportPropertiesIntoObject(NewSystem, GetArrayField(SystemObject, TEXT("Properties")), TEXT("System"), MissingAssets);

		const FString EffectTypePath = GetStringField(SystemObject, TEXT("EffectType"));
		if (EffectTypePath.IsEmpty())
		{
			NewSystem->SetEffectType(nullptr);
		}
		else if (UNiagaraEffectType* EffectType = LoadObject<UNiagaraEffectType>(nullptr, *EffectTypePath))
		{
			NewSystem->SetEffectType(EffectType);
		}
		else
		{
			MissingAssets.Add(EffectTypePath);
			NewSystem->SetEffectType(nullptr);
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* EmitterValues = GetArrayField(RootObject, TEXT("Emitters"));
	const int32 EmitterCount = EmitterValues ? EmitterValues->Num() : 0;

	TArray<FEmitterImportContext> EmitterContexts;
	EmitterContexts.Reserve(EmitterCount);

	TMap<FGuid, FGuid> HandleIdMap;
	int32 RendererCount = 0;
	int32 ImportedNodeCount = 0;

	for (int32 EmitterIndex = 0; EmitterIndex < EmitterCount; ++EmitterIndex)
	{
		const TSharedPtr<FJsonObject> EmitterObject = (*EmitterValues)[EmitterIndex].IsValid() ? (*EmitterValues)[EmitterIndex]->AsObject() : nullptr;
		if (!EmitterObject.IsValid())
		{
			continue;
		}

		FEmitterImportContext Context;
		FNiagaraEmitterHandle Handle;
		if (!CreateEmitter(NewSystem, EmitterObject, EmitterIndex, Context, Handle, MissingAssets, RendererCount, ImportedNodeCount))
		{
			continue;
		}

		const FGuid RecordedHandleId = GetGuidField(EmitterObject, TEXT("HandleId"));
		NewSystem->AddEmitterHandleDirect(Handle);
		const FGuid NewHandleId = NewSystem->GetEmitterHandles().Last().GetId();
		if (RecordedHandleId.IsValid() && NewHandleId.IsValid())
		{
			HandleIdMap.Add(RecordedHandleId, NewHandleId);
		}

		EmitterContexts.Add(Context);
	}

	int32 EventHandlerCount = 0;
	int32 SimulationStageCount = 0;
	for (FEmitterImportContext& Context : EmitterContexts)
	{
		const FString Label = FString::Printf(TEXT("Emitter %s"), *Context.Name);
		ImportEventHandlers(Context.Emitter, Context.EmitterData, GetArrayField(Context.EmitterObject, TEXT("EventHandlers")), HandleIdMap, Label, MissingAssets, EventHandlerCount);
		ImportSimulationStages(Context.Emitter, Context.EmitterData, GetArrayField(Context.EmitterObject, TEXT("SimulationStages")), Label, MissingAssets, SimulationStageCount);
	}

	// Module input overrides live on the scripts, so restore them once every script (including event handler and
	// simulation stage scripts) exists.  The enumeration order has to match the exporter exactly.
	for (FEmitterImportContext& Context : EmitterContexts)
	{
		if (!Context.EmitterData)
		{
			continue;
		}

		if (Context.bSeedFactoryGraph)
		{
			const FString UniqueName = ResolveHandleUniqueName(NewSystem, Context.Emitter, Context.Name);
			ApplyFactorySeedOverrides(Context.EmitterData, UniqueName, Context.EmitterObject, MissingAssets);
			continue;
		}

		const TArray<TSharedPtr<FJsonValue>>* ScriptValues = GetArrayField(Context.EmitterObject, TEXT("Scripts"));
		const FString Label = FString::Printf(TEXT("Emitter %s"), *Context.Name);

		TMap<FString, int32> UsageOccurrences;
		auto ApplyScript = [&](UNiagaraScript* Script)
			{
				if (!Script)
				{
					return;
				}

				const FString Usage = GetUsageName(Script->GetUsage());
				int32& Occurrence = UsageOccurrences.FindOrAdd(Usage);
				ApplyScriptParameters(Script, ScriptValues, Usage, Occurrence,
					FString::Printf(TEXT("%s/%s"), *Label, *Script->GetName()), MissingAssets);
				++Occurrence;
			};

		FVersionedNiagaraEmitterData* EmitterData = Context.EmitterData;
		ApplyScript(EmitterData->SpawnScriptProps.Script);
		ApplyScript(EmitterData->UpdateScriptProps.Script);
		ApplyScript(EmitterData->EmitterSpawnScriptProps.Script);
		ApplyScript(EmitterData->EmitterUpdateScriptProps.Script);
		ApplyScript(EmitterData->GetGPUComputeScript());
		for (const FNiagaraEventScriptProperties& EventHandler : EmitterData->EventHandlerScriptProps)
		{
			ApplyScript(EventHandler.Script);
		}
		for (UNiagaraSimulationStageBase* SimulationStage : EmitterData->GetSimulationStages())
		{
			if (SimulationStage)
			{
				ApplyScript(SimulationStage->Script);
			}
		}
	}

	if (SystemObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* SystemScripts = GetArrayField(SystemObject, TEXT("Scripts"));
		ApplyScriptParameters(SystemSpawnScript, SystemScripts, GetUsageName(ENiagaraScriptUsage::SystemSpawnScript), 0, TEXT("System/SpawnScript"), MissingAssets);
		ApplyScriptParameters(SystemUpdateScript, SystemScripts, GetUsageName(ENiagaraScriptUsage::SystemUpdateScript), 0, TEXT("System/UpdateScript"), MissingAssets);
	}

	UNiagaraGraph* SystemGraph = SystemSpawnScript ? GetGraphFromSource(SystemSpawnScript->GetLatestSource()) : nullptr;
	if (SystemObject.IsValid())
	{
		ImportedNodeCount += ImportGraph(SystemGraph, GetObjectField(SystemObject, TEXT("Graph")), TEXT("System"), MissingAssets);
		RemapEmitterNodeReferences(SystemGraph, NewSystem, HandleIdMap);
		ImportUserParameters(NewSystem, GetArrayField(SystemObject, TEXT("UserParameters")), MissingAssets);
	}

	// The handles were added before the emitter scripts had their rapid iteration values, so refresh again now
	// that they are restored.  This is what pushes the emitter state / spawn rate overrides into the system scripts.
	for (const FNiagaraEmitterHandle& Handle : NewSystem->GetEmitterHandles())
	{
		NewSystem->RefreshSystemParametersFromEmitter(Handle);
	}

	// Force a full recompile: the restored graphs and scripts must all be rebuilt, not just the ones the engine
	// happened to consider dirty.  Only one compilation may be in flight at a time (see KillAllActiveCompilations
	// above), otherwise the scripts end up without a compiled VM.
	if (NewSystem->HasActiveCompilations())
	{
		NewSystem->KillAllActiveCompilations();
	}

	TArray<FString> PendingScripts;
	for (int32 CompileAttempt = 0; CompileAttempt < 3; ++CompileAttempt)
	{
		NewSystem->RequestCompile(true);
		NewSystem->WaitForCompilationComplete(false, false);

		CollectUncompiledScripts(NewSystem, PendingScripts);
		if (PendingScripts.Num() == 0)
		{
			break;
		}

		UE_LOG(LogCommonEFXSnapshotV2, Warning,
			TEXT("Compile attempt %d/%d left %d script(s) without a compiled VM: %s"),
			CompileAttempt + 1, 3, PendingScripts.Num(), *FString::Join(PendingScripts, TEXT(", ")));
	}

	// Refresh everything the engine caches from the compiled scripts: renderer attribute bindings, material parameter
	// masks and the event receiver/generator lists.  Without this the rebuilt asset is saved with stale cached state
	// and looks like it is missing emitters.
	NewSystem->CacheFromCompiledData();
	for (const FNiagaraEmitterHandle& Handle : NewSystem->GetEmitterHandles())
	{
		if (UNiagaraEmitter* Emitter = Handle.GetInstance().Emitter)
		{
			Emitter->OnPostCompile(Handle.GetInstance().Version);
		}
	}

	// Compile rebuilds RapidIteration from the graph. Factory-seeded emitters therefore need the
	// JSON values written onto the compiled parameter store, not only onto the pre-compile copy.
	// Initialize Particle static switches (Sprite Size Mode, Lifetime Mode) only expose size/life
	// pins after the first compile, so re-apply modules and pin defaults here.
	for (FEmitterImportContext& Context : EmitterContexts)
	{
		if (Context.bSeedFactoryGraph && Context.EmitterData)
		{
			const FString UniqueName = ResolveHandleUniqueName(NewSystem, Context.Emitter, Context.Name);
			ApplyFactorySeedOverrides(Context.EmitterData, UniqueName, Context.EmitterObject, MissingAssets);
		}
	}

	// The editor pushes emitter parameters into the system scripts after the compile; do the same so the system
	// scripts end up with the same overrides (including the ones the compiled code does not bake).
	for (const FNiagaraEmitterHandle& Handle : NewSystem->GetEmitterHandles())
	{
		NewSystem->RefreshSystemParametersFromEmitter(Handle);
	}

	LayoutSystemOverviewGraph(NewSystem);
	NewSystem->MarkPackageDirty();

	TArray<UPackage*> PackagesToSave;
	if (UPackage* SystemPackage = NewSystem->GetOutermost())
	{
		PackagesToSave.Add(SystemPackage);
	}

	if (PackagesToSave.Num() > 0 && !FApp::IsUnattended())
	{
		const FEditorFileUtils::EPromptReturnCode SaveResult =
			FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, false, false);
		if (SaveResult != FEditorFileUtils::PR_Success)
		{
			UE_LOG(LogCommonEFXSnapshotV2, Warning, TEXT("The rebuilt asset could not be saved: %s"), *NewSystem->GetPathName());
		}
	}

	LogMissingAssets(MissingAssets);

	UE_LOG(LogCommonEFXSnapshotV2, Display,
		TEXT("Rebuilt Niagara system from v2 snapshot: %s | emitters=%d renderers=%d eventHandlers=%d simulationStages=%d graphNodes=%d missingAssets=%d"),
		*NewSystem->GetPathName(), EmitterContexts.Num(), RendererCount, EventHandlerCount, SimulationStageCount, ImportedNodeCount, MissingAssets.Num());

	return NewSystem;
}
