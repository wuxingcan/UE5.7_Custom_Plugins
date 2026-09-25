// Copyright UMIUSHI Inc. All Rights Reserved.

#define HC4UE_UE5		(ENGINE_MAJOR_VERSION >= 5)
#define HC4UE_UE5_1		(ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1)
#define HC4UE_UE5_2		(ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 2)
#define HC4UE_UE5_3		(ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3)
#define HC4UE_UE5_4		(ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 4)
#define HC4UE_UE5_5		(ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 5)
#define HC4UE_UE5_6		(ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 6)
#define HC4UE_UE5_7		(ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 7)

#include "HealthCheckerEditorSubsystem.h"
#include "HealthCheckerSettings.h"
#include "HealthCheckerReport.h"
#include "HealthCheckerLocalization.h"
#include "Engine/EngineTypes.h"
#include "EngineUtils.h"
#include "Editor.h"
#include "EditorLevelUtils.h"
#include "LevelEditorViewport.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Misc/ScopedSlowTask.h"
#include "Containers/Ticker.h"
#include "ProfilingDebugging/ScopedTimers.h"
#include "MaterialEditingLibrary.h"
#include "ContentStreaming.h"
#include "ShaderCompiler.h"
#include "DistanceFieldAtlas.h"
#if HC4UE_UE5
#include "AssetCompilingManager.h"
#endif
#include "ComponentRecreateRenderStateContext.h"
#include "Misc/UObjectToken.h"
#include "MessageLogModule.h"
#include "IMessageLogListing.h"
#include "Logging/MessageLog.h"
#include "Logging/TokenizedMessage.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Interfaces/IPluginManager.h"
#include "Containers/LazyPrintf.h"
#include "ISettingsModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/FileHelper.h"

#include "Landscape.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/MaterialBillboardComponent.h"
#include "Components/BrushComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/LineBatchComponent.h"
#include "Components/AudioComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/RectLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

// Plugins Niagara
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraLightRendererProperties.h"
#include "NiagaraMeshRendererProperties.h"
#include "NiagaraDataInterfaceSkeletalMesh.h"
#include "NiagaraScript.h"
#include "NiagaraScriptSource.h"
#include "NiagaraGraph.h"
#include "NiagaraNodeInput.h"
#include "NiagaraNodeFunctionCall.h"
#if HC4UE_UE5_6
#include "NiagaraValidationRules.h"
#else
#include "NiagaraEditorSettings.h"
#endif

#include "Engine/Texture2D.h"
#include "Engine/Texture2DArray.h"
#include "Engine/TextureCube.h"
#include "Engine/VolumeTexture.h"
#include "Engine/TextureRenderTarget2D.h"

#include "Engine/SkeletalMesh.h"
#include "Rendering/SkeletalMeshModel.h"
#include "Rendering/SkeletalMeshLODModel.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Rendering/SkeletalMeshLODRenderData.h"
#include "Rendering/SkinWeightVertexBuffer.h"

#include "Editor/GroupActor.h"
#include "EditorUtilityActor.h"
#include "Engine/LevelStreamingAlwaysLoaded.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/SkyLight.h"
#include "Engine/ReflectionCapture.h"
#include "Engine/ExponentialHeightFog.h"
#include "Engine/Scene.h"
#if HC4UE_UE5_4
#include "LevelInstance/LevelInstanceActor.h"
#endif
#if HC4UE_UE5_1
#include "Engine/SkinnedAssetCommon.h"
#endif
#include "Interfaces/Interface_PostProcessVolume.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/Volume.h"
#include "PhysicsEngine/BodySetup.h"
#include "Interfaces/Interface_CollisionDataProvider.h"
#if HC4UE_UE5_5 // Nanite SK
#include "Rendering/NaniteResources.h"
#endif

#include "NavigationSystemTypes.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "NavigationData.h"
#if RECAST_INTERNAL_DEBUG_DATA
#include "NavMesh/RecastInternalDebugData.h"
#include "NavMesh/NavMeshRenderingComponent.h"
#include "NavModifierComponent.h"
#endif

#if HC4UE_UE5_1 // WorldPartition
#include "WorldPartition/WorldPartition.h"
#include "WorldPartition/WorldPartitionMiniMap.h"
#include "WorldPartition/DataLayer/WorldDataLayers.h"
#include "WorldPartition/WorldPartitionEditorLoaderAdapter.h"
#include "WorldPartition/LoaderAdapter/LoaderAdapterShape.h"
#include "WorldPartition/HLOD/HLODActor.h"
#if HC4UE_UE5_4 // WorldPartitionUtils
#include "WorldPartition/WorldPartitionUtils.h"
#include "WorldPartition/WorldPartitionRuntimeCellInterface.h"
#include "WorldPartition/WorldPartitionRuntimeCell.h"
#endif
#endif

#define HC4UE_DEBUG (0)

#if HC4UE_DEBUG
PRAGMA_DISABLE_OPTIMIZATION
#endif

DEFINE_LOG_CATEGORY(LogHealthChecker);

#define LOCTEXT_NAMESPACE "HealthChecker"

#define HC4UE_CRLF TEXT("\r\n")

#define HC4UE_LOCTEXT(Key, DefaultString)		HC4UE::GetLocalizedText(TEXT(Key), TEXT(DefaultString))
#define HC4UE_LOCTEXT_FORMAT(Fmt, ...)			HC4UE::TextFormat(Fmt, ##__VA_ARGS__)

#define HC4UE_GET_LOCTEXT(Key)					HC4UE::GetLocalizedText(TEXT(Key))
#define HC4UE_GET_LOCTEXT_FORMAT(Fmt, ...)		HC4UE::GetLocalizedText(*FString::Printf(TEXT(Fmt), ##__VA_ARGS__))
#define HC4UE_GET_LOCTEXT_VAR(Var)				HC4UE::GetLocalizedText(Var)

namespace HC4UE
{

static TAutoConsoleVariable<int32> CVarNiagaraDebug(TEXT("hc4ue.NiagaraDebug"), 0, TEXT("Niagara parameter debugging"), ECVF_Cheat);
static TAutoConsoleVariable<int32> CVarNiagaraMapCheckDebug1(TEXT("hc4ue.NiagaraMapCheckDebug1"), 0, TEXT("Niagara MapCheck debugging1"), ECVF_Cheat);
static TAutoConsoleVariable<int32> CVarNiagaraMapCheckDebug2(TEXT("hc4ue.NiagaraMapCheckDebug2"), 0, TEXT("Niagara MapCheck debugging2"), ECVF_Cheat);

#if HC4UE_UE5 && (_MSC_VER >= 1930)
// VS2022以降
static constexpr int32 NumScoreSettings = (int32)EScore::D + 1;
#else
// VS2019は定数じゃないとラムダキャプチャーに失敗する
#define NumScoreSettings 4
#endif

using ELightMobility = EComponentMobility::Type;

static IAssetRegistry* GAssetRegistry = nullptr;

static FString NoneString = TEXT("None");

FString GetHealthCheckerPluginDirectory()
{
	TSharedPtr<IPlugin> HealthCheckerPlugin = IPluginManager::Get().FindPlugin(UHealthCheckerSettings::GetHealthCheckerString());
	if(HealthCheckerPlugin.IsValid())
	{
		return HealthCheckerPlugin->GetBaseDir();
	}
	return FString();
}

const UHealthCheckerSettings* GetHealthCheckerSettings()
{
	return GetDefault<UHealthCheckerSettings>();
}

void ShowHealthCheckerSettings()
{
	if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->ShowViewer("Project", "Plugins", "Health Checker");
	}
}

FString RemoveClassPrefix(const FString& ObjectPath)
{
	const int32 StartQuotationIndex = ObjectPath.Find(TEXT("'"), ESearchCase::CaseSensitive, ESearchDir::FromStart);
	const int32 LastQuotationIndex = ObjectPath.Find(TEXT("'"), ESearchCase::CaseSensitive, ESearchDir::FromEnd);
	if(StartQuotationIndex >= 0 && LastQuotationIndex >= 0 && LastQuotationIndex > StartQuotationIndex)
	{
		return ObjectPath.Mid(StartQuotationIndex + 1, LastQuotationIndex - StartQuotationIndex - 1);
	}
	return ObjectPath;
}

template<typename T>
T SafeDivide(const T& A, const T& B)
{
	return (B != (T)0) ? (A / B) : (T)0;
}

template<typename T>
T SafeDivideToPercentage(const T& A, const T& B)
{
	return SafeDivide<T>(A * 100, B);
}

template<typename T, int32 N>
using TFixedArray = TArray<T, TFixedAllocator<N>>;

template<typename T, int32 N>
void InitializeFixedArray(TFixedArray<T, N>& Array, const T& DefaultValue)
{
	Array.Reset();
	for(int32 i = 0; i < N; ++i)
	{
		Array.Emplace(DefaultValue);
	}
}

#if HC4UE_UE5_1

#define HC4UE_GET_SCRIPT_CLASS(ModuleName, ClassName) FTopLevelAssetPath(TEXT("/Script/"#ModuleName), TEXT(#ClassName))

static TMap<FTopLevelAssetPath, TSet<FTopLevelAssetPath>> DerivedClassPathCache;

struct FClassInfoCache
{
	FTopLevelAssetPath ClassPath;
	bool bIsBlueprintClass;
};
static TMap<FTopLevelAssetPath, FClassInfoCache> ClassInfoCache;

void ClearClassInfoCache()
{
	DerivedClassPathCache.Reset();
	ClassInfoCache.Reset();
}

const TSet<FTopLevelAssetPath>& GetDerivedClassPath(const FTopLevelAssetPath& BaseClassPath)
{
	auto GetDerivedClassPathImpl = [](const FTopLevelAssetPath& BaseClassPath)->TSet<FTopLevelAssetPath>
	{
		TSet<FTopLevelAssetPath> DerivedClassPath;
		GAssetRegistry->GetDerivedClassNames({ BaseClassPath }, {}, DerivedClassPath);
		return DerivedClassPath;
	};

	if(const TSet<FTopLevelAssetPath>* FoundDerivedClassPath = DerivedClassPathCache.Find(BaseClassPath))
	{
		return *FoundDerivedClassPath;
	}
	return DerivedClassPathCache.Emplace(BaseClassPath, GetDerivedClassPathImpl(BaseClassPath));
}

const FClassInfoCache& GetClassInfo(const UObject* TargetObject)
{
	auto GetClassInfoImpl = [](const FTopLevelAssetPath& TargetObjectClassPath)->FClassInfoCache
	{
		FAssetData ClassData;
		if(GAssetRegistry->TryGetAssetByObjectPath(FSoftObjectPath(TargetObjectClassPath), ClassData) == UE::AssetRegistry::EExists::Exists)
		{
			static FTopLevelAssetPath BlueprintGeneratedClassPath(TEXT("/Script/Engine"), TEXT("BlueprintGeneratedClass"));
			if(GetDerivedClassPath(BlueprintGeneratedClassPath).Contains(ClassData.AssetClassPath))
			{
				FString TagValue;
				if(ClassData.GetTagValue(TEXT("NativeParentClass"), TagValue))
				{
					return { FTopLevelAssetPath(*RemoveClassPrefix(TagValue)), true };
				}
			}
		}

		return { TargetObjectClassPath, false };
	};

	FTopLevelAssetPath TargetObjectClassPath = TargetObject->GetClass()->GetClassPathName();
	if(const FClassInfoCache* FoundClassInfoCache = ClassInfoCache.Find(TargetObjectClassPath))
	{
		return *FoundClassInfoCache;
	}
	return ClassInfoCache.Emplace(TargetObjectClassPath, GetClassInfoImpl(TargetObjectClassPath));
}

bool IsBlueprintClass(const UObject* TargetObject)
{
	return GetClassInfo(TargetObject).bIsBlueprintClass;
}

bool IsChildOf(const UObject* TargetObject, const FTopLevelAssetPath& BaseClassPath)
{
	const FTopLevelAssetPath& TargetClassPath = GetClassInfo(TargetObject).ClassPath;
	return GetDerivedClassPath(BaseClassPath).Contains(TargetClassPath);
}

template<typename T>
bool IsChildOf(const UObject* TargetObject)
{
	return IsChildOf(TargetObject, T::StaticClass()->GetClassPathName());
}

bool IsSameClass(const UObject* TargetObject, const FTopLevelAssetPath& ClassPath)
{
	return TargetObject->GetClass()->GetClassPathName() == ClassPath;
}

template<typename T>
bool IsSameClass(const UObject* TargetObject)
{
	return IsSameClass(TargetObject, T::StaticClass()->GetClassPathName());
}

#else

#define HC4UE_GET_SCRIPT_CLASS(ModuleName, ClassName) FString(TEXT("/Script/"#ModuleName"."#ClassName))

static TMap<FName, TSet<FName>> DerivedClassPathCache;

struct FClassInfoCache
{
	FName ClassPath;
	bool bIsBlueprintClass;
};
static TMap<FName, FClassInfoCache> ClassInfoCache;

void ClearClassInfoCache()
{
	DerivedClassPathCache.Reset();
	ClassInfoCache.Reset();
}

const TSet<FName>& GetDerivedClassPath(const FString& BaseClassPath)
{
	auto GetDerivedClassPathImpl = [](const FString& BaseClassPath)->TSet<FName>
	{
		FName BaseClassName = *FPaths::GetExtension(BaseClassPath);
		TSet<FName> DerivedClassName;
		GAssetRegistry->GetDerivedClassNames({ BaseClassName }, {}, DerivedClassName);

		TSet<FName> DerivedClassPath;
		if(DerivedClassName.Num() > 0)
		{
			for(const FName& ClassName : DerivedClassName)
			{
				// UE4のDerivedClassNameには名前しか入っていないので名前からクラスを引っ張る
				if(UClass* Class = FindObjectFast<UClass>(nullptr, ClassName, false, true, RF_NoFlags))
				{
					DerivedClassPath.Emplace(*Class->GetPathName());
				}
				else
				{
					// メモリにクラス情報がないということはこのプロジェクトでは使用されていない
				}
			}
		}
		return DerivedClassPath;
	};

	if(const TSet<FName>* FoundDerivedClassPath = DerivedClassPathCache.Find(*BaseClassPath))
	{
		return *FoundDerivedClassPath;
	}
	return DerivedClassPathCache.Emplace(*BaseClassPath, GetDerivedClassPathImpl(BaseClassPath));
}

const FClassInfoCache& GetClassInfo(const UObject* TargetObject)
{
	auto GetClassInfoImpl = [](const FName& TargetObjectClassPath)->FClassInfoCache
	{
		FAssetData ClassData = GAssetRegistry->GetAssetByObjectPath(TargetObjectClassPath);
		if(ClassData.IsValid())
		{
			static const FName BlueprintClassName(TEXT("Blueprint"));
			if(ClassData.AssetClass == BlueprintClassName)
			{
				FString TagValue;
				if(ClassData.GetTagValue(TEXT("NativeParentClass"), TagValue))
				{
					return { FName(*RemoveClassPrefix(TagValue)), true };
				}
			}
		}

		return { TargetObjectClassPath, false };
	};

	FName TargetObjectClassPath = *TargetObject->GetClass()->GetPathName();
	if(const FClassInfoCache* FoundClassInfoCache = ClassInfoCache.Find(TargetObjectClassPath))
	{
		return *FoundClassInfoCache;
	}
	return ClassInfoCache.Emplace(TargetObjectClassPath, GetClassInfoImpl(TargetObjectClassPath));
}

bool IsBlueprintClass(const UObject* TargetObject)
{
	return GetClassInfo(TargetObject).bIsBlueprintClass;
}

bool IsChildOf(const UObject* TargetObject, const FString& BaseClassPath)
{
	FName TargetObjectClassPath = *TargetObject->GetClass()->GetPathName();
	return GetDerivedClassPath(BaseClassPath).Contains(TargetObjectClassPath);
}

template<typename T>
bool IsChildOf(const UObject* TargetObject)
{
	return IsChildOf(TargetObject, T::StaticClass()->GetPathName());
}

bool IsSameClass(const UObject* TargetObject, const FString& ClassPath)
{
	return TargetObject->GetClass()->GetPathName() == ClassPath;
}

template<typename T>
bool IsSameClass(const UObject* TargetObject)
{
	return IsSameClass(TargetObject, T::StaticClass()->GetPathName());
}

#endif

void SetLevelsVisibility(ULevel* Level, bool bShouldBeVisible)
{
	UEditorLevelUtils::SetLevelsVisibility({Level}, {bShouldBeVisible}, false, ELevelVisibilityDirtyMode::DontModify);
}

template<typename TRangeType>
FString StringJoin(const TRangeType& Array, const TCHAR* Separator, int32 MaxCount = 0)
{
	// from FString::Join()
	FString Result;
	bool bFirst = true;
	int32 Count = 0;
	for (const auto& Element : Array)
	{
		if(MaxCount > 0 && ++Count > MaxCount)
		{
			break;
		}

		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Result += Separator;
		}

		Result += Element;
	}
	return Result;
}

//enum class ETextureSize
//{
//	SizeOver8192,
//	Size4096,
//	Size2048,
//	Size1024,
//	Size512,
//	Size256,
//	Size128,
//	Size64,
//	SizeBelow64,
//	MAX
//};

const FString& GetTextureSizeName(ETextureSize TextureSize)
{
	static FString TextureSizeNames[] =
	{
		TEXT("8K"),
		TEXT("4K"),
		TEXT("2K"),
		TEXT("1K"),
		TEXT("512x512"),
		TEXT("256x256"),
		TEXT("128x128"),
		TEXT("64x64"),
		TEXT("Small"),
	};
	static_assert(UE_ARRAY_COUNT(TextureSizeNames) == (int32)ETextureSize::MAX, "TextureSizeNames count is not mismatch ETextureSize::MAX");
	return TextureSizeNames[(int32)TextureSize];
}

ETextureSize GetTextureSize(int32 SizeX, int32 SizeY)
{
	if(SizeX*SizeY >= 8192*8192)
	{
		return ETextureSize::SizeOver8192;
	}
	else
	if(SizeX*SizeY >= 4096*4096)
	{
		return ETextureSize::Size4096;
	}
	else
	if(SizeX*SizeY >= 2048*2048)
	{
		return ETextureSize::Size2048;
	}
	else
	if(SizeX*SizeY >= 1024*1024)
	{
		return ETextureSize::Size1024;
	}
	else
	if(SizeX*SizeY >= 512*512)
	{
		return ETextureSize::Size512;
	}
	else
	if(SizeX*SizeY >= 256*256)
	{
		return ETextureSize::Size256;
	}
	else
	if(SizeX*SizeY >= 128*128)
	{
		return ETextureSize::Size128;
	}
	else
	if(SizeX*SizeY >= 64*64)
	{
		return ETextureSize::Size64;
	}
	else
	{
		return ETextureSize::SizeBelow64;
	}
}

enum class ELevelCategory : uint8
{
	Persistent,
	AlwaysLoaded,
	Streaming,
	MAX
};

const FString& GetLevelCategoryName(ELevelCategory LevelCategory)
{
	static FString LevelCategoryNames[] =
	{
		TEXT("Persistent"),
		TEXT("AlwaysLoaded"),
		TEXT("Streaming"),
	};
	static_assert(UE_ARRAY_COUNT(LevelCategoryNames) == (int32)ELevelCategory::MAX, "LevelCategoryNames count is not mismatch ELevelCategory::MAX");
	return LevelCategoryNames[(int32)LevelCategory];
}

enum class EActorCategory : uint8
{
	SkeletalMesh,
	StaticMesh,
	Particle,
	Audio,
	Rendering,
	Volume,
	Geometry,
	Gameplay,
	Other,
	MAX
};

const FString& GetActorCategoryName(EActorCategory ActorCategory)
{
	static FString ActorCategoryNames[] =
	{
		TEXT("SkeletalMesh"),
		TEXT("StaticMesh"),
		TEXT("Particle"),
		TEXT("Audio"),
		TEXT("Rendering"),
		TEXT("Volume"),
		TEXT("Geometry"),
		TEXT("Gameplay"),
		TEXT("Other"),
	};
	static_assert(UE_ARRAY_COUNT(ActorCategoryNames) == (int32)EActorCategory::MAX, "ActorCategoryNames count is not mismatch EActorCategory::MAX");
	return ActorCategoryNames[(int32)ActorCategory];
}

bool IsValidCategory(EActorCategory ActorCategory)
{
	uint32 ReportActorCategories = GetHealthCheckerSettings()->ReportActorCategories;
	if(ReportActorCategories & (1u << (uint32)ActorCategory))
	{
		return true;
	}

	return false;
}

template<typename T>
void InitializeCategoryMap(TMap<EActorCategory, T>& CategoryMap, const T& DefaultValue)
{
	CategoryMap.Reset();
	for(int32 i = 0; i < (int32)EActorCategory::MAX; ++i)
	{
		CategoryMap.Emplace((EActorCategory)i, DefaultValue);
	}
}

int32 GetTotalCount(const TMap<EActorCategory, int32>& CategoryMap)
{
	int32 TotalCount = 0;
	for(auto It : CategoryMap)
	{
		if(!IsValidCategory(It.Key))
		{
			continue;
		}
		TotalCount += It.Value;
	}
	return TotalCount;
}

enum class EMobilityAndOverlapType : uint8
{
	NoCollision,
	Static,
	StaticAndOverlap,
	Movable,
	MovableAndOverlap,
	MAX
};

const FString& GetMobilityAndOverlapTypeName(EMobilityAndOverlapType MobilityAndOverlapType)
{
	static FString MobilityAndOverlapTypeNames[] =
	{
		TEXT("NoCollision"),
		TEXT("Static"),
		TEXT("Static + Overlap"),
		TEXT("Movable"),
		TEXT("Movable + Overlap"),
	};
	static_assert(UE_ARRAY_COUNT(MobilityAndOverlapTypeNames) == (int32)EMobilityAndOverlapType::MAX, "MobilityAndOverlapTypeNames count is not mismatch EMobilityAndOverlapType::MAX");
	return MobilityAndOverlapTypeNames[(int32)MobilityAndOverlapType];
}

enum class ELightType : uint8
{
	DirectionalLight,
	PointLight,
	SpotLight,
	RectLight,
	UnknownLight,
	MAX
};

const FString& GetLightTypeName(ELightType LightType)
{
	static FString LightTypeNames[] =
	{
		TEXT("DirectionalLight"),
		TEXT("PointLight"),
		TEXT("SpotLight"),
		TEXT("RectLight"),
		TEXT("UnknownLight"),
	};
	static_assert(UE_ARRAY_COUNT(LightTypeNames) == (int32)ELightType::MAX, "LightTypeNames count is not mismatch ELightType::MAX");
	return LightTypeNames[(int32)LightType];
}

struct FLightInfo
{
	FName LightName;

	ELightType LightType = ELightType::MAX;
	ELightMobility LightMobility = ELightMobility::Static;
	bool bLightCastShadows = false;
	bool bLightCastDynamicShadows = false;
};

enum class EAutoManageAttachment : uint8
{
	Manual,
	Auto,
	MAX
};

enum class EAudioPlayMode : uint8
{
	Single,
	Multiple,
	MAX
};

enum class EMaterialBlendMode : uint8
{
	Opaque,
	Masked,
	Translucent,
	Unknown,
	MAX
};

const FString& GetMaterialBlendModeName(EMaterialBlendMode MaterialBlendMode)
{
	static FString MaterialBlendModeNames[] =
	{
		TEXT("Opaque"),
		TEXT("Masked"),
		TEXT("Translucent"),
		TEXT("Unknown"),
	};
	static_assert(UE_ARRAY_COUNT(MaterialBlendModeNames) == (int32)EMaterialBlendMode::MAX, "MaterialBlendModeNames count is not mismatch EMaterialBlendMode::MAX");
	return MaterialBlendModeNames[(int32)MaterialBlendMode];
}

bool IsMaterialOpaqueBlendMode(const UMaterialInterface* Material)
{
#if HC4UE_UE5_2
	return IsOpaqueBlendMode(*Material);
#else
	return Material->GetBlendMode() == BLEND_Opaque;
#endif
}

bool IsMaterialTranslucentOnlyBlendMode(const UMaterialInterface* Material)
{
#if HC4UE_UE5_2
	return IsTranslucentOnlyBlendMode(*Material);
#else
	return Material->GetBlendMode() == BLEND_Translucent;
#endif
}

const TCHAR* GetWorldTypeString(EWorldType::Type WorldType)
{
	switch(WorldType)
	{
	default: ensure(false); // fall through
	case EWorldType::None: return TEXT("None");
	case EWorldType::Game: return TEXT("Game");
	case EWorldType::Editor: return TEXT("Editor");
	case EWorldType::PIE: return TEXT("PIE");
	case EWorldType::EditorPreview: return TEXT("EditorPreview");
	case EWorldType::GamePreview: return TEXT("GamePreview");
	case EWorldType::GameRPC: return TEXT("GameRPC");
	case EWorldType::Inactive: return TEXT("Inactive");
	}
}

ULineBatchComponent* GetPersistentLineBatcher(const UWorld* World)
{
#if HC4UE_UE5_6 // GetLineBatcher()
	return World->GetLineBatcher(UWorld::ELineBatcherType::WorldPersistent);
#else
	return World->PersistentLineBatcher;
#endif
}

ERHIFeatureLevel::Type GetFeatureLevel(const UWorld* World)
{
#if HC4UE_UE5_3
	return World->GetFeatureLevel();
#else
	return World->Scene->GetFeatureLevel();
#endif
}

FBoxSphereBounds GetLocalBounds(const USceneComponent* SceneComponent)
{
#if HC4UE_UE5
	return SceneComponent->GetLocalBounds();
#else
	return SceneComponent->CalcLocalBounds();
#endif
}

bool IsNaniteMesh(const UStaticMesh* StaticMesh)
{
	if(!StaticMesh)
	{
		return false;
	}

#if HC4UE_UE5 // Nanite
	if(StaticMesh->HasValidNaniteData()
#if HC4UE_UE5_3 // NaniteEnabled
	&& StaticMesh->IsNaniteEnabled()
#endif
	)
	{
		return true;
	}
#endif

	return false;
}

bool IsNaniteMesh(const UStaticMeshComponent* StaticMeshComponent)
{
	if(!StaticMeshComponent)
	{
		return false;
	}

#if HC4UE_UE5 // Nanite
#if HC4UE_UE5_6
	if(StaticMeshComponent->IsForceDisableNanite())
	{
		return false;
	}
#endif
#if HC4UE_UE5_1
	if(!StaticMeshComponent->HasValidNaniteData())
	{
		return false;
	}
#endif

	return IsNaniteMesh(StaticMeshComponent->GetStaticMesh());
#else
	return false;
#endif
}

bool IsSameMaterialsInMaterialSlots(const UStaticMesh* StaticMesh)
{
	TArray<UMaterialInterface*> Materials;
	for(const FStaticMaterial& Material : StaticMesh->GetStaticMaterials())
	{
		Materials.AddUnique(Material.MaterialInterface);
	}
	return Materials.Num() != StaticMesh->GetStaticMaterials().Num();
}

#if HC4UE_UE5_1
bool IsSameMaterialsInMaterialSlots(const USkinnedAsset* SkeletalMesh)
#else
bool IsSameMaterialsInMaterialSlots(const USkeletalMesh* SkeletalMesh)
#endif
{
	TArray<UMaterialInterface*> Materials;
	for(const FSkeletalMaterial& Material : SkeletalMesh->GetMaterials())
	{
		Materials.AddUnique(Material.MaterialInterface);
	}
	return Materials.Num() != SkeletalMesh->GetMaterials().Num();
}

bool GetMeshVertices(const UStaticMesh* StaticMesh, bool bIsNaniteMesh, int32& OutNumVertices, int32& OutNumTriangles)
{
	if(!StaticMesh)
	{
		return false;
	}

#if HC4UE_UE5 // Nanite
	if(bIsNaniteMesh)
	{
		OutNumVertices = StaticMesh->GetNumNaniteVertices();
		OutNumTriangles = StaticMesh->GetNumNaniteTriangles();
	}
	else
	{
		OutNumVertices = StaticMesh->GetNumVertices(0);
		OutNumTriangles = StaticMesh->GetNumTriangles(0);
	}

	return true;
#else
	if(StaticMesh->GetRenderData() && StaticMesh->GetRenderData()->LODResources.IsValidIndex(0))
	{
		const FStaticMeshLODResources& LODModel = StaticMesh->GetRenderData()->LODResources[0];
		OutNumVertices = LODModel.GetNumVertices();
		OutNumTriangles = LODModel.GetNumTriangles();
		return true;
	}

	return false;
#endif
}

bool IsNaniteMesh(const USkeletalMesh* SkeletalMesh)
{
	if(!SkeletalMesh)
	{
		return false;
	}

#if HC4UE_UE5_5 // Nanite SK
	if(SkeletalMesh->IsNaniteEnabled() && SkeletalMesh->GetResourceForRendering())
	{
		if(const Nanite::FResources* NaniteResources = SkeletalMesh->GetResourceForRendering()->NaniteResourcesPtr.Get())
		{
			return NaniteResources ? NaniteResources->PageStreamingStates.Num() > 0 : false;
		}
	}
#endif

	return false;
}

bool IsNaniteMesh(const USkinnedMeshComponent* SkinnedMeshComponent)
{
	if(!SkinnedMeshComponent)
	{
		return false;
	}

#if HC4UE_UE5_5 // Nanite SK
	if(!SkinnedMeshComponent->HasValidNaniteData())
	{
		return false;
	}

	return IsNaniteMesh(Cast<USkeletalMesh>(SkinnedMeshComponent->GetSkinnedAsset()));
#else
	return false;
#endif
}

bool GetMeshVertices(const USkeletalMesh* SkeletalMesh, bool bIsNaniteMesh, int32& OutNumVertices, int32& OutNumTriangles)
{
	if(!SkeletalMesh)
	{
		return false;
	}

	bool bResult = false;

#if HC4UE_UE5_5 // Nanite SK
	if(bIsNaniteMesh)
	{
		OutNumVertices = SkeletalMesh->GetNumNaniteVertices();
		OutNumTriangles = SkeletalMesh->GetNumNaniteTriangles();
		bResult = true;
	}
	else
#endif
	{
		if(const FSkeletalMeshRenderData* RenderData = SkeletalMesh->GetResourceForRendering())
		{
			if(RenderData->LODRenderData.IsValidIndex(0))
			{
				const FSkeletalMeshLODRenderData& LODRenderData = RenderData->LODRenderData[0];
				for(const FSkelMeshRenderSection& RenderSection : LODRenderData.RenderSections)
				{
					OutNumVertices += RenderSection.NumVertices;
					OutNumTriangles += RenderSection.NumTriangles;
					bResult = true;
				}
			}
		}
	}

	return bResult;
}

void GeMeshesFromAsset(const UObject* ParticleAsset, TArray<UStaticMesh*>& OutStaticMeshes, TArray<USkeletalMesh*>& OutSkeletalMeshes)
{
	TArray<FName> Dependencies;
	if(GAssetRegistry->GetDependencies(ParticleAsset->GetPackage()->GetFName(), Dependencies, UE::AssetRegistry::EDependencyCategory::Package, UE::AssetRegistry::EDependencyQuery::Hard))
	{
		TArray<FAssetData> DependencyAssetData;
		for(const FName& PackageName : Dependencies)
		{
			GAssetRegistry->GetAssetsByPackageName(PackageName, DependencyAssetData);
		}

		auto IsEqualAssetClassName = [](const FAssetData& AssetData, const TCHAR* TargetClassName)
		{
#if HC4UE_UE5_1
			return AssetData.AssetClassPath.GetAssetName() == TargetClassName;
#else
			return AssetData.AssetClass == TargetClassName;
#endif
		};

		for(const FAssetData& AssetData : DependencyAssetData)
		{
			if(IsEqualAssetClassName(AssetData, TEXT("StaticMesh")))
			{
				if(UStaticMesh* StaticMesh = Cast<UStaticMesh>(AssetData.GetAsset()))
				{
					OutStaticMeshes.AddUnique(StaticMesh);
				}
			}
			else
			if(IsEqualAssetClassName(AssetData, TEXT("SkeletalMesh")))
			{
				if(USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(AssetData.GetAsset()))
				{
					OutSkeletalMeshes.AddUnique(SkeletalMesh);
				}
			}
		}
	}
}

bool GetLowestLodBoneCount(const USkeletalMesh* SkeletalMesh, int32& LowestLodBoneCount)
{
	if(const FSkeletalMeshRenderData* RenderData = SkeletalMesh->GetResourceForRendering())
	{
		int32 NumLOD = RenderData->LODRenderData.Num();
		if(NumLOD > 0)
		{
			TSet<int32> UsedBoneSet;
			const FSkeletalMeshLODRenderData& LODRenderData = RenderData->LODRenderData[NumLOD - 1];
			for(const FSkelMeshRenderSection& RenderSection : LODRenderData.RenderSections)
			{
				for(int32 BoneIndex : RenderSection.BoneMap)
				{
					UsedBoneSet.Add(BoneIndex);
				}
			}
			LowestLodBoneCount = UsedBoneSet.Num();
			return true;
		}
	}

	return false;
}

enum class ENiagaraSystemFlag : uint8
{
	A_NoValidation,
	B_MissingEffectType,
	C_NotFixedBounds,
	D_LongWarmupTime,
	E_MultipleLightRenderers,
	MAX
};

enum class ENiagaraEmitterFlag : uint8
{
	A_LifeCycleIsSelf,
	B_NeedsSpriteCutout,
	C_NeedsEmitterSourceMode,
	D_ManyRenderer,
	E_SkeletalMeshSampling,
	F_MeshRendererWithDistanceFieldMesh,
	G_MeshRendererWithCollisionMesh,
	H_MeshRendererWithMultiUVMesh,
	I_LargeVolumeTexture,
	J_StatefulEmitter,
	K_CloseToStatelessEmitter,
	MAX
};

const FString& GetNiagaraSystemFlagName(ENiagaraSystemFlag SystemFlag)
{
	static FString SystemFlagNames[] =
	{
		"(A) No Validation",
		"(B) Missing EffectType",
		"(C) Not FixedBounds",
		"(D) Long WarmupTime",
		"(E) Multiple Light Renderers",
	};
	static_assert(UE_ARRAY_COUNT(SystemFlagNames) == (int32)ENiagaraSystemFlag::MAX, "SystemFlagNames count is not mismatch ENiagaraSystemFlag::MAX");
	return SystemFlagNames[(int32)SystemFlag];
}

const FString& GetNiagaraEmitterFlagName(ENiagaraEmitterFlag EmitterFlag)
{
	static FString EmitterFlagNames[] =
	{
		"(A) LifeCycle is Self",
		"(B) Needs SpriteCutout",
		"(C) Needs Emitter SourceMode",
		"(D) Many Renderer",
		"(E) SkeletalMesh Sampling",
		"(F) MeshRenderer (DistanceField)",
		"(G) MeshRenderer (Collision)",
		"(H) MeshRenderer (Multi UV)",
		"(I) Large VolumeTexture",
		"(J) Stateful Emitter",
		"(K) Close to Stateless Emitter",
	};
	static_assert(UE_ARRAY_COUNT(EmitterFlagNames) == (int32)ENiagaraEmitterFlag::MAX, "EmitterFlagNames count is not mismatch ENiagaraEmitterFlag::MAX");
	return EmitterFlagNames[(int32)EmitterFlag];
}

struct FNiagaraEmitterInfo
{
	FNiagaraEmitterInfo(){}

	FNiagaraEmitterInfo(const UNiagaraSystem* InSystem, const UNiagaraEmitter* InEmitter)
	: System(InSystem), SystemName(InSystem->GetFName()), Emitter(InEmitter), EmitterName(InEmitter->GetFName())
	{}

	TWeakObjectPtr<const UNiagaraSystem> System;
	FName SystemName;
	TWeakObjectPtr<const UNiagaraEmitter> Emitter;
	FName EmitterName;
	TSet<ENiagaraEmitterFlag> EmitterFlags;

	FString GetEmitterName() const
	{
		return SystemName.ToString() + TEXT(".") + EmitterName.ToString();
	}
};

struct FNiagaraInfo
{
	FNiagaraInfo(){}

	FNiagaraInfo(const UNiagaraSystem* InSystem)
	: System(InSystem), SystemName(InSystem->GetFName())
	{}

	TWeakObjectPtr<const UNiagaraSystem> System;
	FName SystemName;
	TSet<ENiagaraSystemFlag> SystemFlags;
	TArray<FNiagaraEmitterInfo> EmitterInfos;
	TMap<TWeakObjectPtr<const UNiagaraSystem>, TArray<int32>> MissingEmitterIndex;
	TMap<TWeakObjectPtr<const UNiagaraRendererProperties>, TArray<int32>> MissingMaterialIndex;

	FString GetEmitterName(const FName& EmitterName) const
	{
		return SystemName.ToString() + TEXT(".") + EmitterName.ToString();
	}
};

// from NiagaraValidation::HasValidationRules()
bool HasNiagaraValidationRules(UNiagaraSystem* NiagaraSystem)
{
#if HC4UE_UE5_6
	return NiagaraValidation::HasValidationRules(NiagaraSystem);
#elif HC4UE_UE5_2
	auto HasAnyRules = [](const UNiagaraValidationRuleSet* ValidationRuleSet)
	{
		if(ValidationRuleSet)
		{
			return ValidationRuleSet->ValidationRules.ContainsByPredicate(
				[](const UNiagaraValidationRule* Rule)
				{
					return (Rule/* && Rule->IsEnabled()*/) ? true : false;
				}
			);
		}
		return false;
	};

	if(NiagaraSystem)
	{
		if(const UNiagaraEditorSettings* EditorSettings = GetDefault<UNiagaraEditorSettings>())
		{
			for(const TSoftObjectPtr<UNiagaraValidationRuleSet>& ValidationRuleSetPtr : EditorSettings->DefaultValidationRuleSets)
			{
				if(const UNiagaraValidationRuleSet* ValidationRuleSet = ValidationRuleSetPtr.LoadSynchronous())
				{
					return HasAnyRules(ValidationRuleSet);
				}
			}
		}

		if(UNiagaraEffectType* EffectType = NiagaraSystem->GetEffectType())
		{
			for(const UNiagaraValidationRule* Rule : EffectType->ValidationRules)
			{
				if(Rule/* && Rule->IsEnabled()*/)
				{
					return true;
				}
			}

			for(const UNiagaraValidationRuleSet* ValidationRuleSet : EffectType->ValidationRuleSets)
			{
				if(ValidationRuleSet)
				{
					return HasAnyRules(ValidationRuleSet);
				}
			}
		}
	}
	return false;
#else
	return false;
#endif
}

void GetNiagaraGraphRecursive(const UNiagaraScript* NiagaraScript, TSet<const UNiagaraGraph*>& OutNiagaraGraphs)
{
	if(const UNiagaraScriptSource* NiagaraScriptSource = Cast<UNiagaraScriptSource>(NiagaraScript->GetLatestSource()))
	{
		if(NiagaraScriptSource->NodeGraph)
		{
			OutNiagaraGraphs.Emplace(NiagaraScriptSource->NodeGraph);

			for(const UEdGraphNode* Node : NiagaraScriptSource->NodeGraph->Nodes)
			{
				if(const UNiagaraNodeFunctionCall* FunctionCallNode = Cast<UNiagaraNodeFunctionCall>(Node))
				{
					if(const UNiagaraScript* NiagaraModuleScript = FunctionCallNode->FunctionScript)
					{
						GetNiagaraGraphRecursive(NiagaraModuleScript, OutNiagaraGraphs);
					}
				}
			}
		}
	}
}

void GetParameterVariablesFromScript(const UNiagaraScript* NiagaraScript, TArray<FNiagaraVariable>& OutVariables)
{
	const FNiagaraVMExecutableData& VMExecutableData = NiagaraScript->GetVMExecutableData();

	for(const FNiagaraVariable& Variable : VMExecutableData.Parameters.Parameters)
	{
		OutVariables.Emplace(Variable);
	}

#if HC4UE_UE5_2
	for(const FNiagaraVariable& Variable : VMExecutableData.BakedRapidIterationParameters)
	{
		OutVariables.Emplace(Variable);
	}
#endif

	//for(const FNiagaraVariable& Variable : VMExecutableData.StaticVariablesWritten)
	//{
	//	OutVariables.Emplace(Variable);
	//}

	TArray<FNiagaraVariable> RapidIterParams;
	NiagaraScript->RapidIterationParameters.GetParameters(RapidIterParams);
	OutVariables.Append(MoveTemp(RapidIterParams));
#if HC4UE_UE5_1
	NiagaraScript->RapidIterationParametersCookedEditorCache.GetParameters(RapidIterParams);
	OutVariables.Append(MoveTemp(RapidIterParams));
#endif

	//TSet<const UNiagaraGraph*> NiagaraGraphs;
	//GetNiagaraGraphRecursive(NiagaraScript, NiagaraGraphs);
	//for(const UNiagaraGraph* NiagaraGraph : NiagaraGraphs)
	//{
	//	for(auto It : NiagaraGraph->GetAllMetaData())
	//	{
	//		OutVariables.Emplace(It.Value->Variable);
	//	}
	//}
}

FNiagaraInfo GetNiagaraInfo(UNiagaraSystem* System)
{
	if(!System)
	{
		return FNiagaraInfo();
	}

	FNiagaraInfo NiagaraInfo(System);
	TSet<ENiagaraSystemFlag>& SystemFlags = NiagaraInfo.SystemFlags;

	if(CVarNiagaraDebug.GetValueOnGameThread() > 0)
	{
		for(int32 i = 0; i < (int32)ENiagaraSystemFlag::MAX; ++i)
		{
			SystemFlags.Emplace((ENiagaraSystemFlag)i);
		}
	}

	if(!HasNiagaraValidationRules(System))
	{
		SystemFlags.Emplace(ENiagaraSystemFlag::A_NoValidation);
	}

	if(!System->GetEffectType())
	{
		SystemFlags.Emplace(ENiagaraSystemFlag::B_MissingEffectType);
	}

	if(!System->bFixedBounds)
	{
		SystemFlags.Emplace(ENiagaraSystemFlag::C_NotFixedBounds);
	}

	if(System->GetWarmupTime() > GetHealthCheckerSettings()->WarningNiagaraWarmupTime)
	{
		SystemFlags.Emplace(ENiagaraSystemFlag::D_LongWarmupTime);
	}

	auto GetMaxSpawnCount = [](const UNiagaraScript* NiagaraScript)
	{
		TArray<FNiagaraVariable> NiagaraVariables;
		GetParameterVariablesFromScript(NiagaraScript, NiagaraVariables);
		int32 MaxSpawnCount = 0;
		for(const FNiagaraVariable& Variable : NiagaraVariables)
		{
			if(Variable.GetType() == FNiagaraTypeDefinition::GetIntDef() &&
			   Variable.GetName().ToString().EndsWith(TEXT(".Spawn Count")))
			{
				if(const int32* ValuePtr = (const int32*)Variable.GetData())
				{
					MaxSpawnCount = FMath::Max<int32>(MaxSpawnCount, *ValuePtr);
				}
			}
		}
		return MaxSpawnCount;
	};

	int32 MaxSpawnCount = 0;
	if(const UNiagaraScript* SystemSpawnScript = System->GetSystemSpawnScript())
	{
		MaxSpawnCount = FMath::Max(MaxSpawnCount, GetMaxSpawnCount(SystemSpawnScript));
	}
	if(const UNiagaraScript* SystemUpdateScript = System->GetSystemUpdateScript())
	{
		MaxSpawnCount = FMath::Max(MaxSpawnCount, GetMaxSpawnCount(SystemUpdateScript));
	}

	auto IsEmitterUsingSelfLifeCycle = [](const TArray<UEdGraphPin*>& GraphSourcePins)
	{
		auto IsLifeCycleModePin = [](const UEdGraphPin* Pin)
		{
			if(Pin->PinName == TEXT("Life Cycle Mode"))
			{
				if(UEnum* Enum = Cast<UEnum>(Pin->PinType.PinSubCategoryObject.Get()))
				{
					if(Enum->GetName() == TEXT("ENiagaraEmitterLifeCycleMode"))
					{
						return true;
					}
				}
			}
			return false;
		};

		for(const UEdGraphPin* Pin : GraphSourcePins)
		{
			if(IsLifeCycleModePin(Pin) && Pin->bNotConnectable)
			{
				if(Pin->DefaultValue == TEXT("NewEnumerator1")) // NewEnumerator0 == System, NewEnumerator1 == Self
				{
					return true;
				}
			}
		}
		return false;
	};

	int32 NumLightRenderer = 0;
	for(int32 EmitterIndex = 0; EmitterIndex < System->GetEmitterHandles().Num(); ++EmitterIndex)
	{
		const FNiagaraEmitterHandle& EmitterHandle = System->GetEmitterHandles()[EmitterIndex];
		if(!EmitterHandle.GetIsEnabled())
		{
			continue;
		}

#if HC4UE_UE5_1
		const FVersionedNiagaraEmitter& VersionedEmitter = EmitterHandle.GetInstance();
		const UNiagaraEmitter* Emitter = VersionedEmitter.Emitter;
#else
		const UNiagaraEmitter* Emitter = EmitterHandle.GetInstance();
#endif
		if(!Emitter || (CVarNiagaraMapCheckDebug1.GetValueOnGameThread() > 0))
		{
			NiagaraInfo.MissingEmitterIndex.FindOrAdd(System).Emplace(EmitterIndex);
			continue;
		}

		FNiagaraEmitterInfo EmitterInfo(System, Emitter);
		TSet<ENiagaraEmitterFlag>& EmitterFlags = EmitterInfo.EmitterFlags;

		if(CVarNiagaraDebug.GetValueOnGameThread() > 0)
		{
			for(int32 i = 0; i < (int32)ENiagaraEmitterFlag::MAX; ++i)
			{
				EmitterFlags.Emplace((ENiagaraEmitterFlag)i);
			}
		}

#if HC4UE_UE5_1
		if(const FVersionedNiagaraEmitterData* EmitterData = VersionedEmitter.GetEmitterData())
#else
		if(const UNiagaraEmitter* EmitterData = Emitter)
#endif
		{
			if(EmitterData->GraphSource)
			{
				if(const UNiagaraScriptSource* NiagaraScriptSource = Cast<UNiagaraScriptSource>(EmitterData->GraphSource))
				{
					if(NiagaraScriptSource->NodeGraph)
					{
						for(const UEdGraphNode* Node : NiagaraScriptSource->NodeGraph->Nodes)
						{
							if(IsEmitterUsingSelfLifeCycle(Node->Pins))
							{
								EmitterFlags.Emplace(ENiagaraEmitterFlag::A_LifeCycleIsSelf);
							}
						}
					}
				}
			}

			auto IsStatelessEmitter = [&]()
			{
#if HC4UE_UE5_4
				if(EmitterHandle.GetEmitterMode() == ENiagaraEmitterMode::Stateless)
				{
					return true;
				}
#endif
				return false;
			};

			auto IsEmitterConvertibleToStateless = [&]()
			{
				if(EmitterFlags.Contains(ENiagaraEmitterFlag::A_LifeCycleIsSelf))
				{
					return false;
				}

#if HC4UE_UE5_6
				if(EmitterData->InterpolatedSpawnMode != ENiagaraInterpolatedSpawnMode::NoInterpolation)
				{
					return false;
				}
#else
				if(EmitterData->bInterpolatedSpawning)
				{
					return false;
				}
#endif

				if(EmitterData->RequiresPersistentIDs())
				{
					return false;
				}
 
				if(EmitterData->GetEventHandlers().Num() > 0)
				{
					return false;
				}
 
				return true;
			};

#if HC4UE_UE5_4
			if(!IsStatelessEmitter())
			{
				if(IsEmitterConvertibleToStateless())
				{
					EmitterFlags.Emplace(ENiagaraEmitterFlag::K_CloseToStatelessEmitter);
				}
				EmitterFlags.Emplace(ENiagaraEmitterFlag::J_StatefulEmitter);
			}
#endif

			if(EmitterData->GetRenderers().Num() > GetHealthCheckerSettings()->WarningNiagaraRendererCount)
			{
				EmitterFlags.Emplace(ENiagaraEmitterFlag::D_ManyRenderer);
			}

			for(int32 NiagaraRendererIndex = 0; NiagaraRendererIndex < EmitterData->GetRenderers().Num(); ++NiagaraRendererIndex)
			{
				const UNiagaraRendererProperties* NiagaraRenderer = EmitterData->GetRenderers()[NiagaraRendererIndex];
				if(NiagaraRenderer->IsA<UNiagaraLightRendererProperties>())
				{
					++NumLightRenderer;
				}

				if(const UNiagaraSpriteRendererProperties* SpriteRenderer = Cast<UNiagaraSpriteRendererProperties>(NiagaraRenderer))
				{
					if(SpriteRenderer->Material && IsMaterialTranslucentOnlyBlendMode(SpriteRenderer->Material))
					{
						if(!SpriteRenderer->bUseMaterialCutoutTexture && SpriteRenderer->CutoutTexture == nullptr)
						{
							EmitterFlags.Emplace(ENiagaraEmitterFlag::B_NeedsSpriteCutout);
						}
					}

					if(SpriteRenderer->SourceMode == ENiagaraRendererSourceDataMode::Particles)
					{
						if(MaxSpawnCount == 1)
						{
							EmitterFlags.Emplace(ENiagaraEmitterFlag::C_NeedsEmitterSourceMode);
						}
					}
				}

				if(const UNiagaraMeshRendererProperties* MeshRenderer = Cast<UNiagaraMeshRendererProperties>(NiagaraRenderer))
				{
					for(const FNiagaraMeshRendererMeshProperties& MeshProperties : MeshRenderer->Meshes)
					{
						if(MeshProperties.Mesh)
						{
							if(const FStaticMeshRenderData* RenderData = MeshProperties.Mesh->GetRenderData())
							{
								if(RenderData && RenderData->LODResources.Num() > 0)
								{
									const FStaticMeshLODResources& LOD = RenderData->LODResources[0];
									if(LOD.DistanceFieldData)
									{
										EmitterFlags.Emplace(ENiagaraEmitterFlag::F_MeshRendererWithDistanceFieldMesh);
									}
								}
							}

							if(const UBodySetup* BodySetup = MeshProperties.Mesh->GetBodySetup())
							{
								if(BodySetup->AggGeom.GetElementCount() > 0)
								{
									EmitterFlags.Emplace(ENiagaraEmitterFlag::G_MeshRendererWithCollisionMesh);
								}
							}

							if(MeshProperties.Mesh->GetNumUVChannels(0) > 1)
							{
								EmitterFlags.Emplace(ENiagaraEmitterFlag::H_MeshRendererWithMultiUVMesh);
							}
						}
					}
				}

				TArray<UMaterialInterface*> NiagaraMaterials;
				NiagaraRenderer->GetUsedMaterials(nullptr, NiagaraMaterials);

				TSet<const UObject*> NiagaraTextures;
				for(int32 MaterialIndex = 0; MaterialIndex < NiagaraMaterials.Num(); ++MaterialIndex)
				{
					const UMaterialInterface* NiagaraMaterial = NiagaraMaterials[MaterialIndex];
					if(!NiagaraMaterial || (CVarNiagaraMapCheckDebug2.GetValueOnGameThread() > 0))
					{
						NiagaraInfo.MissingMaterialIndex.FindOrAdd(NiagaraRenderer).Emplace(MaterialIndex);
						continue;
					}

					auto Textures = NiagaraMaterial->GetReferencedTextures();
					for(const UObject* Texture : Textures)
					{
						NiagaraTextures.Add(Texture);
					}
				}

				for(const UObject* Texture : NiagaraTextures)
				{
					if(const UVolumeTexture* VolumeTexture = Cast<UVolumeTexture>(Texture))
					{
						const int32& WarningNiagaraVolumeTextureSize = GetHealthCheckerSettings()->WarningNiagaraVolumeTextureSize;
						if(VolumeTexture->GetSizeX() >= WarningNiagaraVolumeTextureSize || VolumeTexture->GetSizeY() >= WarningNiagaraVolumeTextureSize || VolumeTexture->GetSizeZ() >= WarningNiagaraVolumeTextureSize)
						{
							EmitterFlags.Emplace(ENiagaraEmitterFlag::I_LargeVolumeTexture);
							break;
						}
					}
				}
			}

			EmitterData->ForEachScript(
				[&EmitterFlags, &MaxSpawnCount, &GetMaxSpawnCount](UNiagaraScript* NiagaraScript)
				{
					//MaxSpawnCount = FMath::Max(MaxSpawnCount, GetMaxSpawnCount(NiagaraScript));

					for(const FNiagaraScriptDataInterfaceInfo& DataInterfaceInfo : NiagaraScript->GetCachedDefaultDataInterfaces())
					{
						if(DataInterfaceInfo.DataInterface && DataInterfaceInfo.DataInterface->IsA<UNiagaraDataInterfaceSkeletalMesh>())
						{
							EmitterFlags.Emplace(ENiagaraEmitterFlag::E_SkeletalMeshSampling);
							break;
						}
					}
				}
			);
		}

		NiagaraInfo.EmitterInfos.Emplace(MoveTemp(EmitterInfo));
	}

	if(NumLightRenderer > 1)
	{
		SystemFlags.Emplace(ENiagaraSystemFlag::E_MultipleLightRenderers);
	}

	return MoveTemp(NiagaraInfo);

// todo: NiagaraのPIEモード残り

//Require Current Frame DataがONのまま
//System->bRequireCurrentFrameData
//移動しないSystemならOFF推奨
//
//Interpolated Spawningが常時ON
//Emitter->bInterpolatedSpawning
//高速移動しないEmitterではOFF可
//
//Solve Forces and Velocity使用中だが位置変化なし
//Moduleスキャンで検出
//無駄な更新
//
// SpawnCountもPIEモードであればEmitterInstanceから確実に拾える
}

using FPolygonVertices = TFixedArray<FVector, 3>;

struct FNavMeshPolygon
{
	FPolygonVertices PolygonVertices;
	FHitResult EdgeHitResult;

	FNavMeshPolygon(const FVector& InV0, const FVector& InV1, const FVector& InV2)
	: PolygonVertices({ InV0, InV1, InV2 })
	, EdgeHitResult(ForceInit)
	{}

	const FPolygonVertices& GetVertices() const
	{
		return PolygonVertices;
	}

	const FVector& V0() const
	{
		return PolygonVertices[0];
	}

	const FVector& V1() const
	{
		return PolygonVertices[1];
	}

	const FVector& V2() const
	{
		return PolygonVertices[2];
	}

	FVector GetCenter() const
	{
#if HC4UE_UE5
		return (PolygonVertices[0] + PolygonVertices[1] + PolygonVertices[2]) / ((FVector::FReal)3.0);
#else
		return (PolygonVertices[0] + PolygonVertices[1] + PolygonVertices[2]) / 3.f;
#endif
	}
};

bool CheckErrorBrushPolygons(const UBrushComponent* BrushComponent)
{
	if(!BrushComponent)
	{
		return false;
	}

	static const TFixedArray<FVector, 8> CheckSigns =
	{
		FVector(-1,  1, -1),
		FVector( 1,  1, -1),
		FVector( 1,  1,  1),
		FVector(-1,  1,  1),
		FVector(-1, -1, -1),
		FVector( 1, -1, -1),
		FVector( 1, -1,  1),
		FVector(-1, -1,  1),
	};

	const FVector& Origin = BrushComponent->Bounds.Origin;
	const FVector& BoxExtent = BrushComponent->Bounds.BoxExtent;
	FVector ClosestPoint;
	for(const FVector& CheckSign : CheckSigns)
	{
		if(BrushComponent->GetDistanceToCollision(Origin + BoxExtent * CheckSign + CheckSign, ClosestPoint) == 0.f)
		{
			return true;
		}
	}
	return false;
}

struct FComponentInfo
{
	FName ComponentName;
	FName MeshName;

	TWeakObjectPtr<const UActorComponent> Component;
	TWeakObjectPtr<const UObject> Mesh;
	TWeakObjectPtr<const UObject> Material;

	bool bIsRootComponent = false;

	bool bHasStaticMeshComponent = false;
	bool bHasSkeletalMeshComponent = false;
	bool bHasParticleComponent = false;
	bool bHasAudioComponent = false;
	bool bHasAudioGroupComponent = false;
	bool bHasLandscapeComponent = false;
	bool bHasWaterComponent = false;
	bool bHasUIComponent = false;
	bool bHasLightComponent = false;
	bool bHasDynamicMeshComponent = false;
	bool bHasGeometryComponent = false;
	bool bHasCustomVertexComponent = false;

	bool bInstancing = false;
	bool bIsNaniteMesh = false;
	bool bIsFoliage = false;

	bool bSimulatePhysics = false;
	bool bIsCollisionEnabled = false;
	bool bHasComplexCollision = false;
	bool bHasSimpleCollision = false;
	bool bGenerateOverlapEvents = false;
	bool bHasNavMesh = false;

	bool bCastShadows = false;
	bool bCastDynamicShadows = false;
	bool bUseAttachParentBound = false;
	EAutoManageAttachment AutoManageAttachment = EAutoManageAttachment::MAX;
	EAudioPlayMode AudioPlayMode = EAudioPlayMode::MAX;

	bool bErrorBrushPolygons = false;

	bool bMissingMeshes = false;
	bool bMissingMaterials = false;
	bool bSameMaterialsInMaterialSlots = false;
	bool bMismatchNumOverrideMaterial = false;
	bool bNoLodsMesh = false;

	TMap<TWeakObjectPtr<const UPrimitiveComponent>, TArray<int32>> MissingMaterialIndex;

	EComponentMobility::Type ComponentMobility = EComponentMobility::Static;
	EMaterialBlendMode MaterialBlendMode = EMaterialBlendMode::MAX;
	EVisibilityBasedAnimTickOption VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	int32 NumVertices = 0;
	int32 NumTriangles = 0;

	struct FParticleMeshInfo
	{
		int32 NumVertices = 0;
		int32 NumTriangles = 0;
		bool bIsNaniteMesh = false;
		bool bSameMaterialsInMaterialSlots = false;
		TWeakObjectPtr<const UObject> Mesh;
	};
	TMap<FName, FParticleMeshInfo> ParticleMeshInfos;

	FNiagaraInfo NiagaraInfo;

	int32 SkeletonBoneCount = 0;
	int32 BoneCount = 0;
	int32 LowestLodBoneCount = 0;
	float BoneReductionRate = 0;

	FSphere BoundsSphereRadius = 0;
	FSphere ParentBoundsSphereRadius = 0;
};

struct FActorInfo
{
	FString ActorLabelName;
	FString ActorFullName;
	FName ActorName;
	FName LevelName;
	FName LevelPathName;

	FString GetActorName() const{ return !ActorLabelName.IsEmpty() ? ActorLabelName : *ActorName.ToString(); }

	TWeakObjectPtr<const AActor> Actor;

	bool bIsBlueprintActor = false;
	bool bIsPawnActor = false;
	bool bIsStaticMeshActor = false;
	bool bIsLandscapeActor = false;
	bool bIsAudioActor = false;
	bool bIsRenderingActor = false;
	bool bIsVolumeActor = false;
	bool bIsGeometryActor = false;
	bool bIsGameplayActor = false;
	bool bIsMovable = false;
	bool bTickEnabled = false;

	TMap<TWeakObjectPtr<const AActor>, TArray<int32>> MissingComponentIndex;

	int32 ComponentCount = 0;
	int32 SceneComponentCount = 0;
	int32 PrimitiveComponentCount = 0;
	int32 MeshComponentCount = 0;
	int32 AudioComponentCount = 0;
	int32 BrushComponentCount = 0;

	int32 MeshCount = 0;
	int32 StaticMeshCount = 0;
	int32 SkinningMeshCount = 0;
	int32 MaterialCount = 0;

	TWeakObjectPtr<const UStaticMeshComponent> StaticMeshActorComponent;
	FName StaticMeshActorMeshName;

	TArray<FComponentInfo> ComponentInfos;
	TArray<FLightInfo> LightInfos;

#define HC4UE_HAS_ANY_COMPONENT(ComponentName) for(const FComponentInfo& ComponentInfo : ComponentInfos){ if(ComponentInfo.ComponentName){ return true; } } return false;

	bool HasAnyStaticMeshComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasStaticMeshComponent);
	}
	bool HasAnySkeletalMeshComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasSkeletalMeshComponent);
	}
	bool HasAnyParticleComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasParticleComponent);
	}
	bool HasAnyAudioComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasAudioComponent);
	}
	bool HasAnyLandscapeComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasLandscapeComponent);
	}
	bool HasAnyWaterComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasWaterComponent);
	}
	bool HasAnyUIComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasUIComponent);
	}
	bool HasAnyLightComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasLightComponent);
	}
	bool HasAnyDynamicMeshComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasDynamicMeshComponent);
	}
	bool HasAnyGeometryComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasGeometryComponent);
	}
	bool HasAnyCustomVertexComponent() const
	{
		HC4UE_HAS_ANY_COMPONENT(bHasCustomVertexComponent);
	}

#undef HC4UE_HAS_ANY_COMPONENT
};

FString GetComponentName(const FActorInfo& ActorInfo, const FComponentInfo& ComponentInfo)
{
	return FString::Printf(TEXT("'%s.%s.%s'"), *ActorInfo.LevelName.ToString(), *ActorInfo.GetActorName(), *ComponentInfo.ComponentName.ToString());
}

FString GetActorName(const FActorInfo& ActorInfo)
{
	return FString::Printf(TEXT("'%s.%s'"), *ActorInfo.LevelName.ToString(), *ActorInfo.GetActorName());
}

FString GetLevelName(const FActorInfo& ActorInfo)
{
	return FString::Printf(TEXT("'%s'"), *ActorInfo.LevelName.ToString());
}

FString GetActorLabelSafe(const AActor* Actor)
{
	if(Actor)
	{
		FString AcorLabel = Actor->GetActorLabel();
		return !AcorLabel.IsEmpty() ? MoveTemp(AcorLabel) : Actor->GetName();
	}
	return NoneString;
}

FString GetComponentName(const UActorComponent* Component)
{
	return FString::Printf(TEXT("'%s.%s.%s'"), *FPaths::GetBaseFilename(GetNameSafe(Component->GetOutermost())), *GetActorLabelSafe(Component->GetOwner()), *GetNameSafe(Component));
}

FString GetActorName(const UActorComponent* Component)
{
	return FString::Printf(TEXT("'%s.%s'"), *FPaths::GetBaseFilename(GetNameSafe(Component->GetOutermost())), *GetActorLabelSafe(Component->GetOwner()));
}

FString GetActorName(const AActor* Actor)
{
	return FString::Printf(TEXT("'%s.%s'"), *FPaths::GetBaseFilename(GetNameSafe(Actor->GetOutermost())), *GetActorLabelSafe(Actor));
}

FString GetObjectName(const UObject* Object, int32 OuterCount = 0)
{
	if(Object)
	{
		if(OuterCount == 0)
		{
			return Object->GetName();
		}

		FString Name = Object->GetName();
		const UObject* OuterObject = Object->GetOuter();
		while(OuterObject && OuterCount-- > 0)
		{
			Name.InsertAt(0, TEXT("."));
			Name.InsertAt(0, OuterObject->GetName());
			OuterObject = OuterObject->GetOuter();
		}
		return MoveTemp(Name);
	}
	return TEXT("");
};

struct FScore
{
	EScore Score = EScore::MAX;
	float ScoreWeight = 1.f;
	bool bAllowHealthCheck = true;
};

FScore GetScore(const int32& Value, const FIntScoreSettings& IntScoreSettings)
{
	FScore Score = { EScore::F, IntScoreSettings.ScoreWeight, IntScoreSettings.bAllowHealthCheck };
	for(int32 i = 0; i < NumScoreSettings; ++i)
	{
		if(Value <= IntScoreSettings[(EScore)i])
		{
			Score.Score = (EScore)i;
			break;
		}
	}
	return Score;
}

FScore GetScore(const float& Value, const FFloatScoreSettings& FloatScoreSettings)
{
	FScore Score = { EScore::F, FloatScoreSettings.ScoreWeight, FloatScoreSettings.bAllowHealthCheck };
	for(int32 i = 0; i < NumScoreSettings; ++i)
	{
		if(Value <= FloatScoreSettings[(EScore)i])
		{
			Score.Score = (EScore)i;
			break;
		}
	}
	return Score;
}

EScore GetBeforeScore(const EScore& Score)
{
	if(Score == EScore::A)
	{
		return EScore::A;
	}
	return (EScore)((int32)Score - 1);
}

struct FHealthCheckerMessageLog
{
	static const FName& GetHealthCheckerLogName()
	{
		static const FName Name = TEXT("LogHealthChecker");
		return Name;
	}

	void Initialize()
	{
		if(FMessageLogModule* MessageLogModule = FModuleManager::Get().GetModulePtr<FMessageLogModule>("MessageLog"))
		{
			if(!MessageLogModule->IsRegisteredLogListing(GetHealthCheckerLogName()))
			{
				MessageLogModule->RegisterLogListing(GetHealthCheckerLogName(), UHealthCheckerSettings::GetHealthCheckerDisplayText());
			}
			MessageLogModule->GetLogListing(GetHealthCheckerLogName())->ClearMessages();
		}

		Settings = GetHealthCheckerSettings();

		FString PluginDir = GetHealthCheckerPluginDirectory();
		if(!PluginDir.IsEmpty())
		{
			FFileHelper::LoadFileToString(DocumentBaseURL, *FPaths::Combine(PluginDir, TEXT("Resources/DocumentURL.txt")), FFileHelper::EHashOptions::EnableVerify|FFileHelper::EHashOptions::ErrorMissingHash);
			FText DocumentAIHintText = FText::Format(HC4UE_LOCTEXT("Document_AI_Hint", "UE{0}に関する質問"), FText::FromString(FEngineVersion::Current().ToString(EVersionComponent::Minor)));
			DocumentAIHint = Settings->bAddEngineVersionToSearchHints ? DocumentAIHintText.ToString() : TEXT("");
		}
	}

	void Open() const
	{
		if(bHasMessage)
		{
			if(FMessageLogModule* MessageLogModule = FModuleManager::Get().GetModulePtr<FMessageLogModule>("MessageLog"))
			{
				MessageLogModule->OpenMessageLog(GetHealthCheckerLogName());
			}
		}
	}

	static FText GetComponentName(const UActorComponent* Component)
	{
		AActor* Actor = Component->GetOwner();
		FString ActorName = GetActorLabelSafe(Actor);
		if(Actor)
		{
			while(Actor->IsChildActor())
			{
				const UActorComponent* ParentComponent = Actor->GetParentComponent();
				Actor = ParentComponent->GetOwner();
				ActorName = GetActorLabelSafe(Actor) + TEXT(".") + ActorName;
			}
#if HC4UE_UE5_4
			if(Actor->IsInLevelInstance())
			{
				if(ULevel* Level = Actor->GetLevel())
				{
					if(AActor* EditorPathOwner = Cast<AActor>(Level->GetEditorPathOwner()))
					{
						ActorName = GetActorLabelSafe(EditorPathOwner) + TEXT(".") + ActorName;
					}
				}
			}
#endif
		}
		return FText::FromString(FString::Printf(TEXT("%s.%s"), *ActorName, *GetNameSafe(Component)));
	};

	static void OnMessageTokenActivated(const TSharedRef<IMessageToken>& Token)
	{
		if(Token->GetType() == EMessageToken::Object)
		{
			const TSharedRef<FUObjectToken> UObjectToken = StaticCastSharedRef<FUObjectToken>(Token);
			if(UObjectToken->GetObject().IsValid())
			{
				if(UActorComponent* Component = Cast<UActorComponent>(UObjectToken->GetObject().Get()))
				{
					if(GEditor)
					{
						GEditor->SelectNone(false, true);
						AActor* Actor = Component->GetOwner();
						while(Actor->IsChildActor())
						{
							Component = Actor->GetParentComponent();
							Actor = Component->GetOwner();
						}
#if HC4UE_UE5_4
						if(Actor->IsInLevelInstance())
						{
							if(ULevel* Level = Actor->GetLevel())
							{
								if(AActor* EditorPathOwner = Cast<AActor>(Level->GetEditorPathOwner()))
								{
									Actor = EditorPathOwner;
								}
							}
						}
#endif
						GEditor->SelectActor(Actor, true, false);
						GEditor->SelectComponent(Component, true, false);
						GEditor->NoteSelectionChange();
						if(UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component))
						{
							GEditor->MoveViewportCamerasToActor({ Actor }, { PrimitiveComponent }, false);
						}
						else
						{
							GEditor->MoveViewportCamerasToActor(*Actor, false);
						}
						return;
					}
				}
			}
		}
		FUnrealEdMisc::Get().OnMessageTokenActivated(Token);
	}

	TSharedRef<FTokenizedMessage> PerformanceWarning()
	{
		bHasMessage = true;
		return FMessageLog(GetHealthCheckerLogName()).SuppressLoggingToOutputLog(true/*FMessageLogのログ機能は使用しない*/).PerformanceWarning();
	}

	void PerformanceWarning(const FText& Comment, const FText& Details, const AActor* Actor)
	{
		UE_CLOG(Settings->bPostToLog, LogHealthChecker, Warning, TEXT("%s: %s"), *Comment.ToString(), *GetFullNameSafe(Actor));
		if(Settings->bPostToMapCheck)
		{
			PerformanceWarning()
				->AddToken(FTextToken::Create(Comment))
				->AddToken(FTextToken::Create(FText::FromString(TEXT(" Actor:"))))
				->AddToken(FUObjectToken::Create(Actor))
				->AddToken(FDocumentationToken::Create(GetDocumentURL(Details.ToString())));
		}
	}

	void PerformanceWarning(const FText& Comment, const FText& Details, const UActorComponent* Component)
	{
		UE_CLOG(Settings->bPostToLog, LogHealthChecker, Warning, TEXT("%s: %s"), *Comment.ToString(), *GetFullNameSafe(Component));
		if(Settings->bPostToMapCheck)
		{
			PerformanceWarning()
				->AddToken(FTextToken::Create(Comment))
				->AddToken(FTextToken::Create(FText::FromString(TEXT(" Component:"))))
				->AddToken(
					FUObjectToken::Create(Component, GetComponentName(Component))
						->OnMessageTokenActivated(FOnMessageTokenActivated::CreateStatic(&OnMessageTokenActivated))
				)
				->AddToken(FDocumentationToken::Create(GetDocumentURL(Details.ToString())));
		}
	}

	void PerformanceWarning(const FText& Comment, const FText& Details, const UActorComponent* Component, const FString& ObjectName, const UObject* Object, const FString* ObjectLinkLabel = nullptr)
	{
		UE_CLOG(Settings->bPostToLog, LogHealthChecker, Warning, TEXT("%s: %s, %s"), *Comment.ToString(), *GetFullNameSafe(Component), *GetFullNameSafe(Object));
		if(Settings->bPostToMapCheck)
		{
			PerformanceWarning()
				->AddToken(FTextToken::Create(Comment))
				->AddToken(FTextToken::Create(FText::FromString(TEXT(" Component:"))))
				->AddToken(
					FUObjectToken::Create(Component, GetComponentName(Component))
						->OnMessageTokenActivated(FOnMessageTokenActivated::CreateStatic(&OnMessageTokenActivated))
				)
				->AddToken(FTextToken::Create(FText::FromString(FString::Printf(TEXT(" %s:"), *ObjectName))))
				->AddToken(FUObjectToken::Create(Object, ObjectLinkLabel ? FText::FromString(*ObjectLinkLabel) : FText()))
				->AddToken(FDocumentationToken::Create(GetDocumentURL(Details.ToString())));
		}
	}

	FString GetDocumentLinkText() const
	{
		return HC4UE_LOCTEXT("Document_Link", "詳細はこちら").ToString();
	}

	FString GetDocumentURL(const FString& Details) const
	{
		if(!DocumentBaseURL.IsEmpty() && !Details.IsEmpty())
		{
			FString DocumentURL = DocumentBaseURL;
			if(!DocumentAIHint.IsEmpty())
			{
				DocumentURL += FGenericPlatformHttp::UrlEncode(FString::Printf(TEXT("%s (%s)"), *Details, *DocumentAIHint));
			}
			else
			{
				DocumentURL += FGenericPlatformHttp::UrlEncode(Details);
			}
			return MoveTemp(DocumentURL);
		}
		return FString();
	}

	FString GetDocumentURLText(const FString& Details) const
	{
		return FString::Printf(TEXT("<a href=\"%s\" target=\"_blank\" style=\"color:#3498db; text-decoration:underline; cursor:pointer;\">%s</a>"), *GetDocumentURL(Details), *GetDocumentLinkText());
	}

private:

	bool bHasMessage = false;
	const UHealthCheckerSettings* Settings = nullptr;

	FString DocumentBaseURL;
	FString DocumentAIHint;
};

struct FHealthCheckerChartData
{
	int32 Value = 0;
	int32 TotalValue = 0;
	FString Unit = TEXT("n");
	FString Label;
	FString TotalLabel;
};

const TCHAR* GetScoreString(EScore Score)
{
	switch(Score)
	{
	case EScore::A: return TEXT("A");
	case EScore::B: return TEXT("B");
	case EScore::C: return TEXT("C");
	case EScore::D: return TEXT("D");
	default: ensure(false); // fall through
	case EScore::F: return TEXT("F");
	}
}

} // namespace HC4UE

namespace HealthCheckerReport
{
	static FHealthCheckerReportView GLastReport;

	const FHealthCheckerReportView& GetLast()
	{
		return GLastReport;
	}

	void SetLast(FHealthCheckerReportView View)
	{
		GLastReport = MoveTemp(View);
	}
}

void UHealthCheckerEditorSubsystem::OpenHealthCheckerSettings()
{
	HC4UE::ShowHealthCheckerSettings();
}

bool UHealthCheckerEditorSubsystem::RunHealthChecker(bool bSkipAutoOpenReport)
{
	using namespace HC4UE;

	const UHealthCheckerSettings& Settings = *GetHealthCheckerSettings();

	FHealthCheckerMessageLog MessageLog;
	MessageLog.Initialize();

	UE_LOG(LogHealthChecker, Log, TEXT("HealthChecker: Start"));

	FScopedSlowTask Progress(100, FText::FromString(TEXT("Health Checking...")));
	Progress.MakeDialog(true);

	auto UpdateProgressTo = [&Progress](float TargetPercentage)
	{
		Progress.EnterProgressFrame(FMath::Max<float>(0, TargetPercentage - Progress.CompletedWork - Progress.CurrentFrameScope));
	};

	UE_LOG(LogHealthChecker, Log, TEXT("Loading AssetRegistry: Start"));

	// アセットレジストリの処理を待つ
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	AssetRegistry.SearchAllAssets(true);
	GAssetRegistry = &AssetRegistry;
	ClearClassInfoCache();

	UE_LOG(LogHealthChecker, Log, TEXT("Loading AssetRegistry: Finished"));

	UpdateProgressTo(10); // 10%まで終了

	// ゲームワールドを取得する
	bool bIsEditorMode = true;
	UWorld* GameWorld = nullptr;
	if(GEngine)
	{
		for(const FWorldContext& WorldContext : GEngine->GetWorldContexts())
		{
			if(WorldContext.WorldType == EWorldType::PIE)
			{
				GameWorld = WorldContext.World();
				bIsEditorMode = false;
				break;
			}
		}
	}

	// ワールドを取得する
	UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();
	if(!EditorWorld)
	{
		UE_LOG(LogHealthChecker, Error, TEXT("Abort HealthChecker: Editor world not found"));
		return false;
	}

	if(!EditorWorld->PersistentLevel)
	{
		UE_LOG(LogHealthChecker, Error, TEXT("Abort HealthChecker: Persistent level not found in %s"), *GetFullNameSafe(EditorWorld));
		return false;
	}

	// 対象のワールドを設定
	UWorld* CurrentWorld = GameWorld ? GameWorld : EditorWorld;
	if(!CurrentWorld->PersistentLevel)
	{
		UE_LOG(LogHealthChecker, Error, TEXT("Abort HealthChecker: Persistent level not found in %s"), *GetFullNameSafe(CurrentWorld));
		return false;
	}

	ERHIFeatureLevel::Type FeatureLeve = GetFeatureLevel(CurrentWorld);
	EWorldType::Type WorldType = CurrentWorld->WorldType;
	FString WorldPackagePath = GetPathNameSafe(CurrentWorld->PersistentLevel->GetPackage());
	FString PersistentLevelName = FPaths::GetBaseFilename(CurrentWorld->PersistentLevel->GetPathName());

	UE_LOG(LogHealthChecker, Log, TEXT("Loading Levels: Start"));

	// レベルの読み込みとキャッシュの生成

	// ワールドパーティションの場合

#if HC4UE_UE5_1 // WorldPartition
	TMap<FString, UWorldPartitionEditorLoaderAdapter*> EditorLoaderAdapters;
	UWorldPartition* EditorWorldPartition = EditorWorld->GetWorldPartition();
	if(EditorWorldPartition && bIsEditorMode)
	{
#if HC4UE_UE5_4 // WorldPartitionUtils
		FWorldPartitionUtils::FSimulateCookedSession SimulateCookedSession(EditorWorld);

		FWorldPartitionStreamingQuerySource QuerySource;
		QuerySource.bSpatialQuery = true;
		QuerySource.Radius = HALF_WORLD_MAX;

		TArray<const IWorldPartitionCell*> Cells;
		if(SimulateCookedSession.GetIntersectingCells({ QuerySource }, Cells))
		{
			for(const IWorldPartitionCell* Cell : Cells)
			{
				FString CellName = Cell->GetDebugName();
				CellName.RemoveFromStart(PersistentLevelName);
				CellName.RemoveFromStart(TEXT("_"));
				UWorldPartitionEditorLoaderAdapter* EditorLoaderAdapter = EditorWorldPartition->CreateEditorLoaderAdapter<FLoaderAdapterShape>(EditorWorld, Cell->GetCellBounds(), CellName);
				EditorLoaderAdapter->GetLoaderAdapter()->SetUserCreated(true);
				EditorLoaderAdapter->GetLoaderAdapter()->Load();
				EditorLoaderAdapters.Emplace(MoveTemp(CellName), EditorLoaderAdapter);

				Progress.EnterProgressFrame(SafeDivide<float>(1, Cells.Num()) * 10.f); // 10～20%を分割更新
			}
		}
#endif

		if(const FBox WorldBounds = EditorWorldPartition->GetRuntimeWorldBounds(); WorldBounds.IsValid)
		{
			FString Label = TEXT("Runtime WorldBounds");
			UWorldPartitionEditorLoaderAdapter* EditorLoaderAdapter = EditorWorldPartition->CreateEditorLoaderAdapter<FLoaderAdapterShape>(EditorWorld, WorldBounds, *Label);
			EditorLoaderAdapter->GetLoaderAdapter()->SetUserCreated(true);
			EditorLoaderAdapter->GetLoaderAdapter()->Load();
			EditorLoaderAdapters.Emplace(MoveTemp(Label), EditorLoaderAdapter);
		}
	}
#endif

	// 通常のレベルの場合

	struct FSubLevelVisibility
	{
		bool bShouldBeVisible = false;
		bool bShouldBeVisibleInEditor = false;
		bool bShouldBeLoaded = false;
		bool bForceCantReuseUnloadedButStillAround = false;
	};
	struct FLevelVisibility
	{
		bool bPersistentLevelShouldBeVisibleInEditor = false;
		TMap<FName, FSubLevelVisibility> SubLevelVisibilities;
	};

	FLevelVisibility LevelVisibility;
	LevelVisibility.bPersistentLevelShouldBeVisibleInEditor = !EditorWorld->PersistentLevel->GetWorldSettings()->bHiddenEdLevel;

	TMap<ELevelCategory, TMap<bool/*Visible*/, int32>> LevelCategoryCount;
	LevelCategoryCount.FindOrAdd(ELevelCategory::Persistent).FindOrAdd(LevelVisibility.bPersistentLevelShouldBeVisibleInEditor) += 1;

	int32 TotalLevelCount = 0;

	const TArray<ULevelStreaming*>& StreamingLevels = EditorWorld->GetStreamingLevels();
	if(StreamingLevels.Num() > 0)
	{
		TotalLevelCount = 1/*Persistent*/ + StreamingLevels.Num();
		
		for(ULevelStreaming* StreamingLevel : StreamingLevels)
		{
			bool bShouldBeVisible = StreamingLevel->ShouldBeVisible();
			if(StreamingLevel->IsA<ULevelStreamingAlwaysLoaded>())
			{
				LevelCategoryCount.FindOrAdd(ELevelCategory::AlwaysLoaded).FindOrAdd(bShouldBeVisible) += 1;
			}
			else
			{
				LevelCategoryCount.FindOrAdd(ELevelCategory::Streaming).FindOrAdd(bShouldBeVisible) += 1;
			}

			FSubLevelVisibility SubLevelVisibility;
			SubLevelVisibility.bShouldBeVisible = StreamingLevel->GetShouldBeVisibleFlag();
			SubLevelVisibility.bShouldBeVisibleInEditor = StreamingLevel->GetShouldBeVisibleInEditor();
			SubLevelVisibility.bShouldBeLoaded = StreamingLevel->ShouldBeLoaded();
			LevelVisibility.SubLevelVisibilities.FindOrAdd(StreamingLevel->GetWorldAssetPackageFName()) = MoveTemp(SubLevelVisibility);
			if(bIsEditorMode)
			{
				StreamingLevel->SetShouldBeVisibleInEditor(true);
			}
		}
	}

	// すべてのロード完了を待つ
	{
		CurrentWorld->FlushLevelStreaming();

		IStreamingManager::Get().UpdateResourceStreaming(CurrentWorld->GetDeltaSeconds(), true);
		IStreamingManager::Get().BlockTillAllRequestsFinished();

#if HC4UE_UE5
		// Make sure all assets are finished compiling. Recreate render state after shader compilation complete
		{
#if HC4UE_UE5_1
			UMaterialInterface::SubmitRemainingJobsForWorld(CurrentWorld);
#endif
			FAssetCompilingManager::Get().FinishAllCompilation();
			FAssetCompilingManager::Get().ProcessAsyncTasks();
			FGlobalComponentRecreateRenderStateContext Context;
		}
#endif

		// Flush all rendering commands issued by UpdateAllPrimitiveSceneInfos inside the FGlobalComponentRecreateRenderStateContext.
		// Some rendering commands may trigger some shader compilations that we need to be issued and wait for completion before rendering the RVT.
		FlushRenderingCommands();

#if HC4UE_UE5
		// FGlobalComponentRecreateRenderStateContext can create new shaderJobs, make sure to wait on them.
		FAssetCompilingManager::Get().FinishAllCompilation();
		FAssetCompilingManager::Get().ProcessAsyncTasks();
#else
		if(GShaderCompilingManager)
		{
			GShaderCompilingManager->FinishAllCompilation();
			GShaderCompilingManager->ProcessAsyncResults(false, true);
		}
		if(GDistanceFieldAsyncQueue)
		{
			GDistanceFieldAsyncQueue->BlockUntilAllBuildsComplete();
		}
#endif
	}

	if(StreamingLevels.Num() > 0 && bIsEditorMode)
	{
		for(auto& SubLevelVisibility : LevelVisibility.SubLevelVisibilities)
		{
			if(ULevelStreaming* StreamingLevel = EditorWorld->GetLevelStreamingForPackageName(SubLevelVisibility.Key))
			{
				if(ULevel* Level = StreamingLevel->GetLoadedLevel())
				{
#if HC4UE_UE5_4 // ForceCantReuseUnloadedButStillAround
					SubLevelVisibility.Value.bForceCantReuseUnloadedButStillAround = Level->GetForceCantReuseUnloadedButStillAround();
					SubLevelVisibility.Value.bForceCantReuseUnloadedButStillAround = true;
#endif
				}
			}
		}
	}

	UE_LOG(LogHealthChecker, Log, TEXT("Loading Levels: Finished"));

	UpdateProgressTo(20); // 20%まで終了

	struct FHealthCheckerReport
	{
		TArray<FHealthCheckerChartData> ChartData;
		FScore Score;
		FText Description;
		TArray<FText> DetailsArray;
	};
	TMap<FName, FHealthCheckerReport> HealthCheckerReport;

	TArray<FScore> AllScoreArray;

auto RunImpl = [&]()->bool
{
	UE_LOG(LogHealthChecker, Log, TEXT("Check: Start"));

	// マップのロードと表示パフォーマンスチェック
	TMap<FString, float> MapLoadTimes;
	float TotalMapLoadTime = 0;

	// ワールドパーティションの場合

#if HC4UE_UE5_1 // WorldPartition
	if(EditorWorldPartition && Settings.MapLoadTimeScoreSettings.bAllowHealthCheck && bIsEditorMode)
	{
		UE_LOG(LogHealthChecker, Log, TEXT("Load Performance: Start"));

		// 一度セルをすべて非表示に戻す
		for(auto It : EditorLoaderAdapters)
		{
			It.Value->GetLoaderAdapter()->Unload();
		}

		// セルを１つずつ表示して表示にかかる時間を計測する
		for(auto It : EditorLoaderAdapters)
		{
			FAutoScopedDurationTimer Timer;
			It.Value->GetLoaderAdapter()->Load();
			float Time = Timer.GetTime();
			MapLoadTimes.Emplace(It.Key, Time);
			TotalMapLoadTime += Time;

			Progress.EnterProgressFrame(SafeDivide<float>(1, EditorLoaderAdapters.Num()) * 10.f); // 20～30%を分割更新

			if(Progress.ShouldCancel())
			{
				return false; // abort RunImpl
			}
		}

		if(MapLoadTimes.Num() > 0)
		{
			MapLoadTimes.ValueSort([](const double& A, const double& B){ return A >= B; });
			for(auto It : MapLoadTimes)
			{
				UE_LOG(LogHealthChecker, Log, TEXT("'%s' took %.3f sec to loading and visible."), *It.Key, It.Value);
			}
		}

		UE_LOG(LogHealthChecker, Log, TEXT("Load Performance: Finished"));
	}
#endif

	// 通常のレベルの場合

	if(StreamingLevels.Num() > 0 && Settings.MapLoadTimeScoreSettings.bAllowHealthCheck && bIsEditorMode)
	{
		UE_LOG(LogHealthChecker, Log, TEXT("Load Performance: Start"));

		// 一度レベルをすべて非表示に戻す
		for(ULevelStreaming* StreamingLevel : StreamingLevels)
		{
			StreamingLevel->SetShouldBeVisibleInEditor(false);
		}
		SetLevelsVisibility(EditorWorld->PersistentLevel, false);

		EditorWorld->FlushLevelStreaming();

		// レベルを１つずつ表示して表示にかかる時間を計測する
		{
			FAutoScopedDurationTimer Timer;
			SetLevelsVisibility(EditorWorld->PersistentLevel, true);
			float Time = Timer.GetTime();
			MapLoadTimes.Emplace(EditorWorld->PersistentLevel->GetPathName(), Time);
			TotalMapLoadTime += Time;
		}
		for(ULevelStreaming* StreamingLevel : StreamingLevels)
		{
			FAutoScopedDurationTimer Timer;
			StreamingLevel->SetShouldBeVisibleInEditor(true);
			EditorWorld->FlushLevelStreaming();
			float Time = Timer.GetTime();
			MapLoadTimes.Emplace(StreamingLevel->GetWorldAssetPackageName(), Time);
			TotalMapLoadTime += Time;

			Progress.EnterProgressFrame(SafeDivide<float>(1, StreamingLevels.Num()) * 10.f); // 30～40%を分割更新

			if(Progress.ShouldCancel())
			{
				return false; // abort RunImpl
			}
		}

		if(MapLoadTimes.Num() > 0)
		{
			MapLoadTimes.ValueSort([](const double& A, const double& B){ return A >= B; });
			for(auto It : MapLoadTimes)
			{
				UE_LOG(LogHealthChecker, Log, TEXT("'%s' took %.3f sec to loading and visible."), *It.Key, It.Value);
			}
		}

		UE_LOG(LogHealthChecker, Log, TEXT("Load Performance: Finished"));
	}

	UpdateProgressTo(40); // 40%まで終了

	if(Progress.ShouldCancel())
	{
		return false; // abort RunImpl
	}

	// テクスチャサイズの取得

	struct FTextureInfo
	{
		FName TextureName;
		TWeakObjectPtr<const UTexture> Texture;
		int32 NumMips = 1;
		int32 MaxResLODBias = 0;
		int32 MaxAllowedSizeX = 0;
		int32 MaxAllowedSizeY = 0;
		EPixelFormat Format = PF_Unknown;
		int32 DroppedMips = 0;
		int32 CurSizeX = 0;
		int32 CurSizeY = 0;
		bool bIsStreamingTexture = false;
		bool bIsForced = false;
		bool bIsVirtual = false;
		bool bIsCompressed = false;
		bool bIsStreamedIn = false;
	};
	TArray<FTextureInfo> TextureInfos;

	int32 ProgressTextureCount = 0;
	for(TObjectIterator<UTexture> It; It; ++It)
	{
		++ProgressTextureCount;
	}

	auto IsTextureUncompressed = [](const UTexture* Texture)
	{
#if HC4UE_UE5
		return Texture->IsUncompressed();
#else
		return (Texture->CompressionSettings == TC_Grayscale ||
				Texture->CompressionSettings == TC_Displacementmap ||
				Texture->CompressionSettings == TC_VectorDisplacementmap ||
				Texture->CompressionSettings == TC_HDR ||
				Texture->CompressionSettings == TC_EditorIcon ||
				Texture->CompressionSettings == TC_DistanceFieldFont ||
				Texture->CompressionSettings == TC_HalfFloat);
#endif
	};

	IRenderAssetStreamingManager& StreamingManager = IStreamingManager::Get().GetRenderAssetStreamingManager();
	TMap<FString, FRenderedTextureStats> RenderedTextureAssets;
	StreamingManager.AddRenderedTextureStats(RenderedTextureAssets);

	for(TObjectIterator<UTexture> It; It; ++It)
	{
		UTexture* Texture = *It;

		FTextureInfo TextureInfo;
		TextureInfo.TextureName = *Texture->GetPathName();
		TextureInfo.Texture = Texture;
		TextureInfo.MaxResLODBias = Texture->GetCachedLODBias();
		TextureInfo.MaxAllowedSizeX = FMath::Max<int32>(static_cast<int32>(Texture->GetSurfaceWidth()) >> TextureInfo.MaxResLODBias, 1);
		TextureInfo.MaxAllowedSizeY = FMath::Max<int32>(static_cast<int32>(Texture->GetSurfaceHeight()) >> TextureInfo.MaxResLODBias, 1);
		TextureInfo.DroppedMips = TextureInfo.MaxResLODBias;
		TextureInfo.CurSizeX = FMath::Max<int32>(static_cast<int32>(Texture->GetSurfaceWidth()) >> TextureInfo.DroppedMips, 1);
		TextureInfo.CurSizeY = FMath::Max<int32>(static_cast<int32>(Texture->GetSurfaceHeight()) >> TextureInfo.DroppedMips, 1);
		TextureInfo.bIsStreamingTexture = Texture->GetStreamingIndex() != INDEX_NONE;
		TextureInfo.bIsForced = Texture->ShouldMipLevelsBeForcedResident() && TextureInfo.bIsStreamingTexture;
		TextureInfo.bIsVirtual = Texture->IsCurrentlyVirtualTextured();
		TextureInfo.bIsCompressed = !IsTextureUncompressed(Texture);
		TextureInfo.bIsStreamedIn = RenderedTextureAssets.Contains(Texture->GetName());

		if(UTexture2D* Texture2D = Cast<UTexture2D>(Texture))
		{
			TextureInfo.NumMips = Texture2D->GetNumMips();
			TextureInfo.MaxResLODBias = TextureInfo.NumMips - Texture2D->GetNumMipsAllowed(false);
			TextureInfo.MaxAllowedSizeX = FMath::Max<int32>(Texture2D->GetSizeX() >> TextureInfo.MaxResLODBias, 1);
			TextureInfo.MaxAllowedSizeY = FMath::Max<int32>(Texture2D->GetSizeY() >> TextureInfo.MaxResLODBias, 1);
			TextureInfo.Format = Texture2D->GetPixelFormat();
			TextureInfo.DroppedMips = Texture2D->GetNumMips() - Texture2D->GetNumResidentMips();
			TextureInfo.CurSizeX = FMath::Max<int32>(Texture2D->GetSizeX() >> TextureInfo.DroppedMips, 1);
			TextureInfo.CurSizeY = FMath::Max<int32>(Texture2D->GetSizeY() >> TextureInfo.DroppedMips, 1);
		}
		else
		if(UTexture2DArray* Texture2DArray = Cast<UTexture2DArray>(Texture))
		{
			auto GetNumResidentMips = [](const UTexture2DArray* Texture2DArray)->int32
			{
				// from UTexture2DArray::GetNumResidentMips()
				if(Texture2DArray && Texture2DArray->GetResource())
				{
					if(Texture2DArray->GetStreamableResourceState().IsValid())
					{
						return Texture2DArray->GetStreamableResourceState().NumResidentLODs;
					}
					else
					{
						return Texture2DArray->GetResource()->GetCurrentMipCount();
					}
				}
				return 0;
			};

			TextureInfo.NumMips = Texture2DArray->GetNumMips();
			TextureInfo.Format = Texture2DArray->GetPixelFormat();
			TextureInfo.DroppedMips = Texture2DArray->GetNumMips() - GetNumResidentMips(Texture2DArray);
			TextureInfo.CurSizeX = FMath::Max<int32>(Texture2DArray->GetSizeX() >> TextureInfo.DroppedMips, 1);
			TextureInfo.CurSizeY = FMath::Max<int32>(Texture2DArray->GetSizeY() >> TextureInfo.DroppedMips, 1);
		}
		else
		if(UTextureCube* TextureCube = Cast<UTextureCube>(Texture))
		{
			TextureInfo.NumMips = TextureCube->GetNumMips();
			TextureInfo.Format = TextureCube->GetPixelFormat();
		}
		else
		if(UVolumeTexture* Texture3D = Cast<UVolumeTexture>(Texture))
		{
			TextureInfo.NumMips = Texture3D->GetNumMips();
			TextureInfo.Format = Texture3D->GetPixelFormat();
		}
		else
		if(UTextureRenderTarget2D* RenderTexture = Cast<UTextureRenderTarget2D>(Texture))
		{
			TextureInfo.NumMips = RenderTexture->GetNumMips();
			TextureInfo.Format = RenderTexture->GetFormat();
		}

		TextureInfos.Emplace(MoveTemp(TextureInfo));

		Progress.EnterProgressFrame(SafeDivide<float>(1, ProgressTextureCount) * 10.f); // 40～50%を分割更新

		if(Progress.ShouldCancel())
		{
			return false; // abort RunImpl
		}
	}

	UpdateProgressTo(50); // 50%まで終了

	if(Progress.ShouldCancel())
	{
		return false; // abort RunImpl
	}

	// ナビメッシュの形状チェック
	TArray<FNavMeshPolygon> ErrorNavMeshPolygons;
	int32 TotalNavMeshPolygonsCount = 0;
	TArray<TWeakObjectPtr<const UActorComponent>> NavMeshComponents;

#if RECAST_INTERNAL_DEBUG_DATA
	if(UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(EditorWorld))
	{
		if(const ARecastNavMesh* NavMesh = Cast<ARecastNavMesh>(NavSys->GetDefaultNavDataInstance()))
		{
			FNavMeshSceneProxyData NavMeshRenderData;
			const FVector& NavMeshRayStartOffset = NavMeshRenderData.NavMeshDrawOffset;
#if HC4UE_UE5_2 // NavigationDataResolution
			FVector NavMeshRayEndOffset = FVector(0, 0, NavMesh->GetCellHeight(ENavigationDataResolution::Default) + 1) + NavMeshRayStartOffset;
#else
			FVector NavMeshRayEndOffset = FVector(0, 0, NavMesh->CellHeight + 1) + NavMeshRayStartOffset;
#endif

			FRecastDebugGeometry NavMeshGeometry;
#if HC4UE_UE5_5 // NavMeshGeometry
			NavMesh->GetDebugGeometryForTile(NavMeshGeometry, FNavTileRef());
#elif HC4UE_UE5_1 // NavMeshGeometry
			NavMesh->GetDebugGeometryForTile(NavMeshGeometry, INDEX_NONE);
#else
			NavMesh->GetDebugGeometry(NavMeshGeometry);
#endif

			int32 ProgressNavMeshPolygonsCount = 0;
			for(int32 AreaIdx = 0; AreaIdx < RECAST_MAX_AREAS; ++AreaIdx)
			{
				ProgressNavMeshPolygonsCount += NavMeshGeometry.AreaIndices[AreaIdx].Num() / 3;
			}

			FCollisionQueryParams QueryParams;
			QueryParams.bTraceComplex = true;

			FPolygonVertices TempPolyVertices = { FVector::ZeroVector, FVector::ZeroVector, FVector::ZeroVector };

			for(int32 AreaIdx = 0; AreaIdx < RECAST_MAX_AREAS; ++AreaIdx)
			{
				const TArray<int32>& MeshIndices = NavMeshGeometry.AreaIndices[AreaIdx];
				for(int32 MeshIndex = 0; MeshIndex < MeshIndices.Num(); MeshIndex += 3)
				{
					TempPolyVertices[0] = NavMeshGeometry.MeshVerts[MeshIndices[MeshIndex + 0]];
					TempPolyVertices[1] = NavMeshGeometry.MeshVerts[MeshIndices[MeshIndex + 1]];
					TempPolyVertices[2] = NavMeshGeometry.MeshVerts[MeshIndices[MeshIndex + 2]];
					TempPolyVertices.Sort([](const FVector& A, const FVector& B){ return A.Z < B.Z; });

					++TotalNavMeshPolygonsCount;

					FNavMeshPolygon NavMeshPolygon(TempPolyVertices[0], TempPolyVertices[1], TempPolyVertices[2]);
					FHitResult VerticalHitResult(ForceInit);

					{
						// NavMeshComponents取得のために中心位置から縦方向にレイキャスト
						const FVector NavMeshPolygonCenter = NavMeshPolygon.GetCenter();
						if(EditorWorld->LineTraceSingleByChannel(
							VerticalHitResult,
							NavMeshPolygonCenter + NavMeshRayStartOffset,
							NavMeshPolygonCenter - NavMeshRayEndOffset,
							ECC_WorldStatic, QueryParams))
						{
							if(UPrimitiveComponent* HitComponent = VerticalHitResult.GetComponent())
							{
								NavMeshComponents.AddUnique(HitComponent);
							}
						}
					}

					// 頂点から垂直方向にレイキャスト
					bool bVerticalErrorNavMesh = false;
					if(!EditorWorld->LineTraceSingleByChannel(
						VerticalHitResult,
						NavMeshPolygon.V0() + NavMeshRayStartOffset,
						NavMeshPolygon.V0() - NavMeshRayEndOffset,
						ECC_WorldStatic, QueryParams))
					{
						if(UPrimitiveComponent* HitComponent = VerticalHitResult.GetComponent())
						{
							NavMeshComponents.AddUnique(HitComponent);
						}
						bVerticalErrorNavMesh = true;
					}
					if(!EditorWorld->LineTraceSingleByChannel(
						VerticalHitResult,
						NavMeshPolygon.V1() + NavMeshRayStartOffset,
						NavMeshPolygon.V1() - NavMeshRayEndOffset,
						ECC_WorldStatic, QueryParams))
					{
						if(UPrimitiveComponent* HitComponent = VerticalHitResult.GetComponent())
						{
							NavMeshComponents.AddUnique(HitComponent);
						}
						bVerticalErrorNavMesh = true;
					}
					if(!EditorWorld->LineTraceSingleByChannel(
						VerticalHitResult,
						NavMeshPolygon.V2() + NavMeshRayStartOffset,
						NavMeshPolygon.V2() - NavMeshRayEndOffset,
						ECC_WorldStatic, QueryParams))
					{
						if(UPrimitiveComponent* HitComponent = VerticalHitResult.GetComponent())
						{
							NavMeshComponents.AddUnique(HitComponent);
						}
						bVerticalErrorNavMesh = true;
					}

					if(bVerticalErrorNavMesh)
					{
						FHitResult EdgeHitResult1to0(ForceInit);
						FHitResult EdgeHitResult2to1(ForceInit);
						FHitResult EdgeHitResult2to0(ForceInit);

						// ポリゴンエッジのレイキャスト
						bool bErrorNavMesh = false;
						if(EditorWorld->LineTraceSingleByChannel(
							EdgeHitResult1to0,
							NavMeshPolygon.V1() + NavMeshRayStartOffset,
							NavMeshPolygon.V0() + NavMeshRayStartOffset,
							ECC_WorldStatic, QueryParams))
						{
							if(UPrimitiveComponent* HitComponent = EdgeHitResult1to0.GetComponent())
							{
								NavMeshComponents.AddUnique(HitComponent);
							}
							NavMeshPolygon.EdgeHitResult = MoveTemp(EdgeHitResult1to0);
							bErrorNavMesh = true;
						}
						if(EditorWorld->LineTraceSingleByChannel(
							EdgeHitResult2to1,
							NavMeshPolygon.V2() + NavMeshRayStartOffset,
							NavMeshPolygon.V1() + NavMeshRayStartOffset,
							ECC_WorldStatic, QueryParams))
						{
							if(UPrimitiveComponent* HitComponent = EdgeHitResult2to1.GetComponent())
							{
								NavMeshComponents.AddUnique(HitComponent);
							}
							NavMeshPolygon.EdgeHitResult = MoveTemp(EdgeHitResult2to1);
							bErrorNavMesh = true;
						}
						if(EditorWorld->LineTraceSingleByChannel(
							EdgeHitResult2to0,
							NavMeshPolygon.V2() + NavMeshRayStartOffset,
							NavMeshPolygon.V0() + NavMeshRayStartOffset,
							ECC_WorldStatic, QueryParams))
						{
							if(UPrimitiveComponent* HitComponent = EdgeHitResult2to0.GetComponent())
							{
								NavMeshComponents.AddUnique(HitComponent);
							}
							NavMeshPolygon.EdgeHitResult = MoveTemp(EdgeHitResult2to0);
							bErrorNavMesh = true;
						}

						if(bErrorNavMesh)
						{
							auto IsUniquePolygon = [&NavMeshPolygon, &ErrorNavMeshPolygons]()
							{
								const FPolygonVertices& A = NavMeshPolygon.GetVertices();
								for(const FNavMeshPolygon& ErrorNavMeshPolygon : ErrorNavMeshPolygons)
								{
									const FPolygonVertices& B = ErrorNavMeshPolygon.GetVertices();
									for(int32 i = 0; i < 3; ++i)
									{
										for(int32 j = 0; j < 3; ++j)
										{
											if(A[i].Equals(B[j]))
											{
												return false;
											}
										}
									}
								}
								return true;
							};

							if(IsUniquePolygon())
							{
								FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Error_NavMesh_Polygons", "埋もれているナビメッシュが存在します");
								UE_CLOG(Settings.bPostToLog && Settings.ErrorNavMeshPolygonsRatioScoreSettings.bAllowHealthCheck, LogHealthChecker, Warning, TEXT("%s: %s, NavMesh %s"), *MapCheckComment.ToString(), *GetFullNameSafe(NavMeshPolygon.EdgeHitResult.GetComponent()), *NavMeshPolygon.GetCenter().ToString());
								if(Settings.bPostToMapCheck && Settings.ErrorNavMeshPolygonsRatioScoreSettings.bAllowHealthCheck)
								{
									FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Error_NavMesh_Polygons_Details");
									MessageLog.PerformanceWarning()
										->AddToken(FTextToken::Create(MapCheckComment))
										->AddToken(FTextToken::Create(FText::FromString(TEXT(" Component:"))))
										->AddToken(
											FUObjectToken::Create(NavMeshPolygon.EdgeHitResult.GetComponent(), FHealthCheckerMessageLog::GetComponentName(NavMeshPolygon.EdgeHitResult.GetComponent()))
												->OnMessageTokenActivated(FOnMessageTokenActivated::CreateStatic(&FHealthCheckerMessageLog::OnMessageTokenActivated))
										)
										->AddToken(FTextToken::Create(FText::FromString(TEXT(" "))))
										->AddToken(FActionToken::Create(FText::FromString(TEXT("NavMesh")), FText::FromString(TEXT("Focus NavMesh Polygon")),
											FOnActionTokenExecuted::CreateWeakLambda(CurrentWorld, [WeakWorld = TWeakObjectPtr<UWorld>(CurrentWorld), NavMeshPolygon = NavMeshPolygon, DrawNavMeshPolygonTimer = Settings.DrawNavMeshPolygonTimer]()
											{
												if(UPrimitiveComponent* HitComponent = NavMeshPolygon.EdgeHitResult.GetComponent())
												{
													uint32 LineBatchId = GetTypeHash(FGuid::NewGuid());

													FNavMeshSceneProxyData NavMeshRenderData;
													const FVector& NavMeshDrawOffset = NavMeshRenderData.NavMeshDrawOffset;

													UWorld* World = WeakWorld.Get();
													if(World)
													{
														if(ULineBatchComponent* LineBatcher = GetPersistentLineBatcher(World))
														{
															LineBatcher->DrawMesh(
																{ NavMeshPolygon.V0() + NavMeshDrawOffset, NavMeshPolygon.V1() + NavMeshDrawOffset, NavMeshPolygon.V2() + NavMeshDrawOffset },
#if HC4UE_UE5_3 // LineBatchId
																{ 0, 1, 2 }, FColorList::VioletRed, 0, -1.f, LineBatchId
#else
																{ 0, 1, 2 }, FColorList::VioletRed, 0, DrawNavMeshPolygonTimer
#endif
															);
														}
													}

													FBox PolygonBoundingBox(NavMeshPolygon.V0(), NavMeshPolygon.V0());
													PolygonBoundingBox += NavMeshPolygon.V1();
													PolygonBoundingBox += NavMeshPolygon.V2();
													for(FLevelEditorViewportClient* LevelViewportClient : GEditor->GetLevelViewportClients())
													{
														LevelViewportClient->FocusViewportOnBox(PolygonBoundingBox);
													}

													if(World)
													{
#if HC4UE_UE5
#define HC4UE_FCoreTicker FTSTicker
#else
#define HC4UE_FCoreTicker FTicker
#endif
														HC4UE_FCoreTicker::GetCoreTicker().AddTicker(
															FTickerDelegate::CreateWeakLambda(World, [WeakWorld = TWeakObjectPtr<UWorld>(World), LineBatchId = LineBatchId, DrawNavMeshPolygonTimer = DrawNavMeshPolygonTimer](float DeltaTime)
															{
																if(UWorld* World = WeakWorld.Get())
																{
																	if(ULineBatchComponent* LineBatcher = GetPersistentLineBatcher(World))
																	{
#if HC4UE_UE5_3 // LineBatchId
																		LineBatcher->ClearBatch(LineBatchId);
#else
																		LineBatcher->TickComponent(DrawNavMeshPolygonTimer, LEVELTICK_All, nullptr);
#endif
																	}
																}
																return false;
															}), DrawNavMeshPolygonTimer);
#undef HC4UE_FCoreTicker
													}
												}
											})))
										->AddToken(FDocumentationToken::Create(MessageLog.GetDocumentURL(MapCheckDocuments.ToString())));
								}

								ErrorNavMeshPolygons.Emplace(MoveTemp(NavMeshPolygon));
							}
						}
					}

					Progress.EnterProgressFrame(SafeDivide<float>(1, ProgressNavMeshPolygonsCount) * 10.f); // 50～60%を分割更新

					if(Progress.ShouldCancel())
					{
						return false; // abort RunImpl
					}
				}
			}
		}
	}
#endif

	UpdateProgressTo(60); // 60%まで終了

	if(Progress.ShouldCancel())
	{
		return false; // abort RunImpl
	}

	int32 ProgressActorCount = 0;
	for(FActorIterator It(CurrentWorld); It; ++It)
	{
		++ProgressActorCount;
	}

	TMap<TWeakObjectPtr<const ULightComponent>, FSphere> LightComponents;
	TMap<TWeakObjectPtr<const UPrimitiveComponent>, FSphere> PrimitiveComponents;

	// アクターの情報を取得する
	TMap<FString, FActorInfo> ActorInfos;
	for(FActorIterator It(CurrentWorld); It; ++It)
	{
		AActor* Actor = *It;

		if(Settings.bIgnoreEditorOnlyActorsAndComponents && Actor->IsEditorOnly())
		{
			continue;
		}

		if(Actor->IsA<AGroupActor>()
		|| Actor->IsA<AEditorUtilityActor>()
#if HC4UE_UE5_1 // WorldPartition
		|| Actor->IsA<AWorldPartitionMiniMap>()
#endif
		)
		{
			continue;
		}

		FActorInfo& ActorInfo = ActorInfos.Emplace(Actor->GetFullName());

		ActorInfo.Actor = Actor;
		ActorInfo.ActorLabelName = Actor->GetActorLabel();
		ActorInfo.ActorFullName = Actor->GetFullName();
		ActorInfo.ActorName = Actor->GetFName();
		ActorInfo.LevelName = *GetNameSafe(Actor->GetLevel());
		ActorInfo.LevelPathName = *GetNameSafe(Actor->GetOutermost());
		if(ActorInfo.LevelName == TEXT("PersistentLevel"))
		{
			ActorInfo.LevelName = *FPaths::GetBaseFilename(ActorInfo.LevelPathName.ToString());
		}
		ActorInfo.bIsBlueprintActor = IsBlueprintClass(Actor);

		if(Actor->IsA<APawn>())
		{
			ActorInfo.bIsPawnActor = true;
		}
		else
		if(Actor->IsA<AStaticMeshActor>())
		{
			ActorInfo.bIsStaticMeshActor = true;
		}
		else
		if(Actor->IsA<ALandscape>())
		{
			ActorInfo.bIsLandscapeActor = true;
		}
		else
		if(Actor->IsA<ASkyLight>()
		|| Actor->IsA<AReflectionCapture>()
		|| Actor->IsA<AExponentialHeightFog>()
		|| HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(Foliage, InstancedFoliageActor))
#if HC4UE_UE5_1 // WorldPartition
		|| Actor->IsA<AWorldPartitionHLOD>()
#endif
		)
		{
			ActorInfo.bIsRenderingActor = true;
		}
		else
		if(Actor->IsA<ALevelScriptActor>()
		|| Actor->IsA<AWorldSettings>()
#if HC4UE_UE5_1 // WorldPartition
		|| Actor->IsA<AWorldDataLayers>()
#endif
		|| Actor->IsA<APlayerStart>()
		|| Actor->IsA<ARecastNavMesh>()
		|| Actor->IsA<ANavigationData>()
		|| HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(CinematicCamera, CineCameraActor))
		|| HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(GameplayDebugger, GameplayDebuggerPlayerManager))
		|| (Actor->GetName() == TEXT("ChaosDebugDrawActor"))
		|| HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(MassRepresentation, MassVisualizer))
		|| HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(MassSpawner, MassSpawner))
		|| HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(SmartObjectsModule, SmartObjectSubsystemRenderingActor))
		|| HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(ZoneGraph, ZoneGraphData))
		|| HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(PointCloud, SliceAndDiceManager))
		|| HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(Landscape, LandscapeGizmoActor))
		|| HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(Landscape, LandscapeGizmoActiveActor))
		)
		{
			ActorInfo.bIsGameplayActor = true;
		}
		else
		if(HC4UE::IsChildOf(Actor, HC4UE_GET_SCRIPT_CLASS(WorldAudioDataSystem, WorldAudioDataClusterActor))
		)
		{
			ActorInfo.bIsAudioActor = true;
		}
		else
		if(Actor->IsA<ABrush>())
		{
			if(Actor->IsA<AVolume>())
			{
				ActorInfo.bIsVolumeActor = true;
			}
			else
			{
				ActorInfo.bIsGeometryActor = true;
			}
		}

		ActorInfo.bTickEnabled = Actor->IsActorTickEnabled();
		ActorInfo.bIsMovable = Actor->IsRootComponentMovable();

		const TSet<UActorComponent*>& Components = Actor->GetComponents();
		for(UActorComponent* Component : Components)
		{
			if(!Component)
			{
				int32 ComponentIndex = ActorInfo.ComponentInfos.Num();
				ActorInfo.MissingComponentIndex.FindOrAdd(Actor).Emplace(ComponentIndex);
				continue;
			}

			if(Settings.bIgnoreEditorOnlyActorsAndComponents && Component->IsEditorOnly())
			{
				continue;
			}

			++ActorInfo.ComponentCount;

			FComponentInfo ComponentInfo;
			ComponentInfo.ComponentName = Component->GetFName();
			ComponentInfo.Component = Component;
			ComponentInfo.bIsRootComponent = Component == Actor->GetRootComponent();
			ComponentInfo.bHasComplexCollision = Component->IsPhysicsStateCreated();

			if(const USceneComponent* SceneComponent = Cast<USceneComponent>(Component))
			{
				++ActorInfo.SceneComponentCount;
				ComponentInfo.bSimulatePhysics = SceneComponent->IsAnySimulatingPhysics();
				ComponentInfo.bIsCollisionEnabled = SceneComponent->IsCollisionEnabled();
				ComponentInfo.bUseAttachParentBound = SceneComponent->bUseAttachParentBound;
				ComponentInfo.ComponentMobility = SceneComponent->Mobility;

				ComponentInfo.BoundsSphereRadius = GetLocalBounds(SceneComponent).GetSphere();
				if(USceneComponent* ParentSceneComponent = SceneComponent->GetAttachParent())
				{
					ComponentInfo.ParentBoundsSphereRadius = GetLocalBounds(ParentSceneComponent).GetSphere();
				}
			}

			if(const UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component))
			{
				PrimitiveComponents.Emplace(PrimitiveComponent, GetLocalBounds(PrimitiveComponent).GetSphere());

				++ActorInfo.PrimitiveComponentCount;
				ComponentInfo.bGenerateOverlapEvents = PrimitiveComponent->GetGenerateOverlapEvents();
				ComponentInfo.bHasNavMesh = NavMeshComponents.Contains(PrimitiveComponent);
				ComponentInfo.bCastShadows = PrimitiveComponent->CastShadow;
				ComponentInfo.bCastDynamicShadows = PrimitiveComponent->bCastDynamicShadow;

				if(const UBodySetup* BodySetup = const_cast<UPrimitiveComponent*>(PrimitiveComponent)->GetBodySetup())
				{
					ComponentInfo.bHasSimpleCollision = (BodySetup->AggGeom.ConvexElems.Num() > 0);
				}

				if(const IInterface_CollisionDataProvider* CollisionDataProvider = Cast<IInterface_CollisionDataProvider>(PrimitiveComponent))
				{
					ComponentInfo.bHasComplexCollision = CollisionDataProvider->ContainsPhysicsTriMeshData(false);
				}

				int32 NumMaterials = PrimitiveComponent->GetNumMaterials();
				if(NumMaterials > 0)
				{
					ComponentInfo.bMissingMaterials = PrimitiveComponent->IsVisible() && (NumMaterials == 0);
					ActorInfo.MaterialCount += NumMaterials;

					for(int32 MaterialIndex = 0; MaterialIndex < NumMaterials; ++MaterialIndex)
					{
						if(!PrimitiveComponent->GetMaterial(MaterialIndex))
						{
							ComponentInfo.MissingMaterialIndex.FindOrAdd(PrimitiveComponent).Emplace(MaterialIndex);
						}
					}

					TArray<UMaterialInterface*> Materials;
					PrimitiveComponent->GetUsedMaterials(Materials);
					for(const UMaterialInterface* Material : Materials)
					{
						if(!Material)
						{
							continue;
						}

						if(IsMaterialOpaqueBlendMode(Material))
						{
							ComponentInfo.MaterialBlendMode = EMaterialBlendMode::Opaque;
						}
						else
						if(Material->IsMasked())
						{
							ComponentInfo.MaterialBlendMode = EMaterialBlendMode::Masked;
						}
						else
						{
							// from UMaterialInterface::GetRelevance_Internal()
							const bool bIsMobile = FeatureLeve <= ERHIFeatureLevel::ES3_1;
#if HC4UE_UE5_3
							const bool bUsesSingleLayerWaterMaterial = Material->GetShadingModels().HasShadingModel(MSM_SingleLayerWater);
#else
							const FMaterialResource* MaterialResource = Material->GetMaterialResource(FeatureLeve);
							const bool bUsesSingleLayerWaterMaterial = MaterialResource ? MaterialResource->GetShadingModels().HasShadingModel(MSM_SingleLayerWater) : false;
#endif
							const bool bIsSinglePassWaterTranslucent = bIsMobile && bUsesSingleLayerWaterMaterial;
							if(IsTranslucentBlendMode(Material->GetBlendMode()) || bIsSinglePassWaterTranslucent)
							{
								ComponentInfo.MaterialBlendMode = EMaterialBlendMode::Translucent;
							}
							else
							{
								ComponentInfo.MaterialBlendMode = EMaterialBlendMode::Unknown;
							}
						}
					}
				}
			}

			if(const ULightComponent* LightComponent = Cast<ULightComponent>(Component))
			{
				if(LightComponent->IsA<UDirectionalLightComponent>())
				{
					LightComponents.Emplace(LightComponent);
				}
				else
				if(const ULocalLightComponent* LocalLightComponent = Cast<ULocalLightComponent>(LightComponent))
				{
					LightComponents.Emplace(LightComponent, FSphere(LightComponent->GetComponentLocation(), LocalLightComponent->AttenuationRadius));
				}

				ComponentInfo.bHasLightComponent = true;

				FLightInfo LightInfo;

				LightInfo.LightName = ComponentInfo.ComponentName;
				LightInfo.LightMobility = LightComponent->Mobility;
				LightInfo.bLightCastShadows = LightComponent->CastShadows;
				LightInfo.bLightCastDynamicShadows = LightComponent->CastDynamicShadows;

				if(LightComponent->IsA<UDirectionalLightComponent>())
				{
					LightInfo.LightType = ELightType::DirectionalLight;
				}
				else
				if(LightComponent->IsA<UPointLightComponent>())
				{
					LightInfo.LightType = ELightType::PointLight;
				}
				else
				if(LightComponent->IsA<USpotLightComponent>())
				{
					LightInfo.LightType = ELightType::SpotLight;
				}
				else
				if(LightComponent->IsA<URectLightComponent>())
				{
					LightInfo.LightType = ELightType::RectLight;
				}
				else
				{
					LightInfo.LightType = ELightType::UnknownLight;
				}

				ActorInfo.LightInfos.Emplace(MoveTemp(LightInfo));
			}

			if(const UBrushComponent* BrushComponent = Cast<UBrushComponent>(Component))
			{
				if(CheckErrorBrushPolygons(BrushComponent))
				{
					ComponentInfo.bErrorBrushPolygons = true;
				}
				++ActorInfo.BrushComponentCount;
			}

			if(Component->IsA<UAudioComponent>()
			|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(AudioGameplay, AudioComponentGroup))
			|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(AudioGameplay, AudioGameplayComponent))
			|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(AudioMixer, SynthComponent))
			)
			{
				ComponentInfo.bHasAudioComponent = true;
			}

			if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Foliage, ProceduralFoliageComponent)))
			{
				ComponentInfo.bIsFoliage = true;
			}

			if(const UAudioComponent* AudioComponent = Cast<UAudioComponent>(Component))
			{
				++ActorInfo.AudioComponentCount;
				if(!ComponentInfo.bIsRootComponent)
				{
					ComponentInfo.AutoManageAttachment = AudioComponent->bAutoManageAttachment ? EAutoManageAttachment::Auto : EAutoManageAttachment::Manual;
				}
#if HC4UE_UE5
				ComponentInfo.AudioPlayMode = AudioComponent->bCanPlayMultipleInstances ? EAudioPlayMode::Multiple : EAudioPlayMode::Single;
#endif
			}

			auto GetParticleMeshInfos = [](FComponentInfo& ComponentInfo, const UObject* ParticleAsset)
			{
				TArray<UStaticMesh*> StaticMeshes;
				TArray<USkeletalMesh*> SkeletalMeshes;
				GeMeshesFromAsset(ParticleAsset, StaticMeshes, SkeletalMeshes);

				for(const UStaticMesh* StaticMesh : StaticMeshes)
				{
					int32 NumVertices = 0, NumTriangles = 0;
					bool bIsNaniteMesh = IsNaniteMesh(StaticMesh);
					bool bSameMaterialsInMaterialSlots = IsSameMaterialsInMaterialSlots(StaticMesh);
					if(GetMeshVertices(StaticMesh, bIsNaniteMesh, NumVertices, NumTriangles))
					{
						if(NumVertices > 0)
						{
							FName MeshName = *GetPathNameSafe(StaticMesh);
							ComponentInfo.ParticleMeshInfos.Add(MeshName, { NumVertices, NumTriangles, bIsNaniteMesh, bSameMaterialsInMaterialSlots, StaticMesh });
						}
					}
				}

				for(const USkeletalMesh* SkeletalMesh : SkeletalMeshes)
				{
					const FReferenceSkeleton& RefSkeleton = SkeletalMesh->GetRefSkeleton();
					if(RefSkeleton.GetNum() > ComponentInfo.BoneCount)
					{
						ComponentInfo.SkeletonBoneCount = RefSkeleton.GetRawBoneNum();
						ComponentInfo.BoneCount = RefSkeleton.GetNum();
						if(!GetLowestLodBoneCount(SkeletalMesh, ComponentInfo.LowestLodBoneCount))
						{
							ComponentInfo.LowestLodBoneCount = ComponentInfo.BoneCount;
						}
						ComponentInfo.BoneReductionRate = SafeDivideToPercentage<float>(ComponentInfo.LowestLodBoneCount, ComponentInfo.BoneCount);
					}
					int32 NumVertices = 0, NumTriangles = 0;
					bool bIsNaniteMesh = IsNaniteMesh(SkeletalMesh);
					bool bSameMaterialsInMaterialSlots = IsSameMaterialsInMaterialSlots(SkeletalMesh);
					if(GetMeshVertices(SkeletalMesh, IsNaniteMesh(SkeletalMesh), NumVertices, NumTriangles))
					{
						if(NumVertices > 0)
						{
							FName MeshName = *GetPathNameSafe(SkeletalMesh);
							ComponentInfo.ParticleMeshInfos.Add(MeshName, { NumVertices, NumTriangles, bIsNaniteMesh, bSameMaterialsInMaterialSlots, SkeletalMesh });
						}
					}
				}
			};

			if(const UNiagaraComponent* NiagaraComponent = Cast<UNiagaraComponent>(Component))
			{
				if(!ComponentInfo.bIsRootComponent)
				{
					ComponentInfo.AutoManageAttachment = NiagaraComponent->bAutoManageAttachment ? EAutoManageAttachment::Auto : EAutoManageAttachment::Manual;
				}

				if(UNiagaraSystem* NiagaraSystem = NiagaraComponent ? NiagaraComponent->GetAsset() : nullptr)
				{
					GetParticleMeshInfos(ComponentInfo, NiagaraSystem);
					ComponentInfo.NiagaraInfo = GetNiagaraInfo(NiagaraSystem);
				}
			}
			else
			if(const UParticleSystemComponent* ParticleSystemComponent = Cast<UParticleSystemComponent>(Component))
			{
				if(!ComponentInfo.bIsRootComponent)
				{
					ComponentInfo.AutoManageAttachment = ParticleSystemComponent->bAutoManageAttachment ? EAutoManageAttachment::Auto : EAutoManageAttachment::Manual;
				}

				if(UParticleSystem* ParticleSystem = ParticleSystemComponent ? ParticleSystemComponent->Template : nullptr)
				{
					GetParticleMeshInfos(ComponentInfo, ParticleSystem);
				}
			}

			if(const UMeshComponent* MeshComponent = Cast<UMeshComponent>(Component))
			{
				++ActorInfo.MeshComponentCount;

				if(MeshComponent->GetNumOverrideMaterials() > 0 && MeshComponent->GetNumOverrideMaterials() > MeshComponent->GetNumMaterials())
				{
					ComponentInfo.bMismatchNumOverrideMaterial = true;
				}

				if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(GeometryFramework, BaseDynamicMeshComponent))
				|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(ProceduralMeshComponent, ProceduralMeshComponent))
				)
				{
					ComponentInfo.bHasDynamicMeshComponent = true;
				}
				else
				if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(CustomMeshComponent, CustomMeshComponent)))
				{
					ComponentInfo.bHasGeometryComponent = true;
				}
				else
				if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(CableComponent, CableComponent))
				|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(ModelingComponents, LineSetComponent))
				|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(ModelingComponents, PointSetComponent))
				|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(ModelingComponents, TriangleSetComponent))
				)
				{
					ComponentInfo.bHasCustomVertexComponent = true;
				}
				else
				if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(GeometryCache, GeometryCacheComponent))
				|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(GeometryCollectionEngine, GeometryCollectionComponent))
				)
				{
					ComponentInfo.bHasStaticMeshComponent = true;
					ComponentInfo.bSimulatePhysics = true;
				}
				else
				if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Paper2D, PaperFlipbookComponent))
				|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Paper2D, PaperGroupedSpriteComponent))
				|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Paper2D, PaperSpriteComponent))
				|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Paper2D, PaperTileMapComponent))
				|| HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(UMG, WidgetComponent))
				)
				{
					ComponentInfo.bHasUIComponent = true;
				}
				else
				if(const USkinnedMeshComponent* SkinnedMeshComponent = Cast<USkinnedMeshComponent>(Component))
				{
#if HC4UE_UE5_1
					USkinnedAsset* SkinnedAsset = SkinnedMeshComponent->GetSkinnedAsset();
					USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(SkinnedAsset);
#else
					USkeletalMesh* SkinnedAsset = SkinnedMeshComponent->SkeletalMesh;
					USkeletalMesh* SkeletalMesh = SkinnedAsset;
#endif
					if(SkinnedAsset)
					{
						const FReferenceSkeleton& RefSkeleton = SkinnedAsset->GetRefSkeleton();
						if(RefSkeleton.GetNum() > ComponentInfo.BoneCount)
						{
							ComponentInfo.SkeletonBoneCount = RefSkeleton.GetRawBoneNum();
							ComponentInfo.BoneCount = RefSkeleton.GetNum();
							if(!GetLowestLodBoneCount(SkeletalMesh, ComponentInfo.LowestLodBoneCount))
							{
								ComponentInfo.LowestLodBoneCount = ComponentInfo.BoneCount;
							}
							ComponentInfo.BoneReductionRate = SafeDivideToPercentage<float>(ComponentInfo.LowestLodBoneCount, ComponentInfo.BoneCount);
						}

						ComponentInfo.bIsNaniteMesh = IsNaniteMesh(SkinnedMeshComponent);
						ComponentInfo.Mesh = SkinnedAsset;
						ComponentInfo.MeshName = *GetPathNameSafe(SkinnedAsset);
						ComponentInfo.bSameMaterialsInMaterialSlots = IsSameMaterialsInMaterialSlots(SkinnedAsset);

						if(SkeletalMesh)
						{
							GetMeshVertices(SkeletalMesh, ComponentInfo.bIsNaniteMesh, ComponentInfo.NumVertices, ComponentInfo.NumTriangles);
						}
					}

					++ActorInfo.MeshCount;
					++ActorInfo.SkinningMeshCount;

					ComponentInfo.VisibilityBasedAnimTickOption = SkinnedMeshComponent->VisibilityBasedAnimTickOption;
					ComponentInfo.bMissingMeshes = SkinnedMeshComponent->IsVisible() && (SkinnedAsset == nullptr);
					ComponentInfo.bNoLodsMesh = SkinnedMeshComponent->GetNumLODs() == 0;

					if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(ChaosClothAssetEngine, ChaosClothComponent)))
					{
						ComponentInfo.bHasDynamicMeshComponent = true;
						ComponentInfo.bSimulatePhysics = true;
					}
					else
					if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Engine, InstancedSkinnedMeshComponent))) // Component->IsA<UInstancedSkinnedMeshComponent>()
					{
						ComponentInfo.bHasSkeletalMeshComponent = true;
						ComponentInfo.bInstancing = true;
					}
					else
					if(Component->IsA<USkeletalMeshComponent>() || Component->IsA<UPoseableMeshComponent>())
					{
						ComponentInfo.bHasSkeletalMeshComponent = true;
					}
				}
				else
				if(const UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Component))
				{
					++ActorInfo.MeshCount;
					++ActorInfo.StaticMeshCount;

					ComponentInfo.bIsNaniteMesh = IsNaniteMesh(StaticMeshComponent);
					ComponentInfo.Mesh = StaticMeshComponent->GetStaticMesh();
					ComponentInfo.MeshName = *GetPathNameSafe(StaticMeshComponent->GetStaticMesh());
					ComponentInfo.bMissingMeshes = StaticMeshComponent->IsVisible() && (StaticMeshComponent->GetStaticMesh() == nullptr);

					if(const UStaticMesh* StaticMesh = StaticMeshComponent->GetStaticMesh())
					{
						ComponentInfo.bSameMaterialsInMaterialSlots = IsSameMaterialsInMaterialSlots(StaticMesh);
						ComponentInfo.bNoLodsMesh = StaticMesh->GetNumLODs() == 0;
						GetMeshVertices(StaticMesh, ComponentInfo.bIsNaniteMesh, ComponentInfo.NumVertices, ComponentInfo.NumTriangles);
					}

					if(Component->IsA<UInstancedStaticMeshComponent>())
					{
						ComponentInfo.bInstancing = true;
						ComponentInfo.bHasStaticMeshComponent = true;
						if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Foliage, FoliageInstancedStaticMeshComponent)))
						{
							ComponentInfo.bIsFoliage = true;
						}
					}
					else
					if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Foliage, InteractiveFoliageComponent)))
					{
						ComponentInfo.bHasStaticMeshComponent = true;
						ComponentInfo.bIsFoliage = true;
					}
#if HC4UE_UE5 // Nanite
					else
					if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Landscape, LandscapeNaniteComponent)))
					{
						ComponentInfo.bHasLandscapeComponent = true;
#if HC4UE_UE5_1 // NaniteEnabled
						if(ALandscape* Landscape = Cast<ALandscape>(Actor))
						{
							ComponentInfo.bIsNaniteMesh = Landscape->IsNaniteEnabled();
						}
#else
						ComponentInfo.bIsNaniteMesh = true;
#endif
					}
#endif
					else
					if(Component->IsA<USplineMeshComponent>())
					{
						ComponentInfo.bHasCustomVertexComponent = true;
					}
					else
					if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Water, WaterBodyMeshComponent)))
					{
						ComponentInfo.bHasWaterComponent = true;
					}
					else
					if(IsSameClass<UStaticMeshComponent>(Component))
					{
						ComponentInfo.bHasStaticMeshComponent = true;
					}
				}
				else
				if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Water, WaterMeshComponent)))
				{
					ComponentInfo.bHasWaterComponent = true;
				}
			}
			else
			if(Component->IsA<UBillboardComponent>()
			//|| Component->IsA<UMaterialBillboardComponent>()
			|| Component->IsA<USplineComponent>()
			|| Component->IsA<ULineBatchComponent>()
			)
			{
				ComponentInfo.bHasCustomVertexComponent = true;
			}
			else
			if(Component->IsA<UMaterialBillboardComponent>())
			{
				ComponentInfo.bHasCustomVertexComponent = true;
			}
			else
			if(Component->IsA<UBrushComponent>()
			|| Component->IsA<UShapeComponent>()
			)
			{
				ComponentInfo.bHasGeometryComponent = true;
			}
			else
			if(Component->IsA<UFXSystemComponent>())
			{
				ComponentInfo.bHasParticleComponent = true;
			}
			else
			if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Landscape, LandscapeComponent)))
			{
				ComponentInfo.bHasLandscapeComponent = true;
			}
			else
			if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Landscape, LandscapeSplinesComponent)))
			{
				ComponentInfo.bHasCustomVertexComponent = true;
			}
			else
			if(HC4UE::IsChildOf(Component, HC4UE_GET_SCRIPT_CLASS(Water, WaterBodyComponent)))
			{
				ComponentInfo.bHasWaterComponent = true;
			}

			ActorInfo.ComponentInfos.Emplace(MoveTemp(ComponentInfo));
		}

		if(ActorInfo.bIsStaticMeshActor && ActorInfo.PrimitiveComponentCount == 1)
		{
			if(const AStaticMeshActor* StaticMeshActor = Cast<const AStaticMeshActor>(ActorInfo.Actor.Get()))
			{
				if(StaticMeshActor->GetStaticMeshComponent() && StaticMeshActor->GetStaticMeshComponent()->GetStaticMesh())
				{
					ActorInfo.StaticMeshActorComponent = StaticMeshActor->GetStaticMeshComponent();
					ActorInfo.StaticMeshActorMeshName = *StaticMeshActor->GetStaticMeshComponent()->GetStaticMesh()->GetPathName();
				}
			}
		}

		Progress.EnterProgressFrame(SafeDivide<float>(1, ProgressActorCount) * 10.f); // 60～70%を分割更新

		if(Progress.ShouldCancel())
		{
			return false; // abort RunImpl
		}
	}

	TMap<TWeakObjectPtr<const ULightComponent>, TArray<TWeakObjectPtr<const UPrimitiveComponent>>> AffectedByLightComponents;
	for(auto& LightIt : LightComponents)
	{
		if(const ULightComponent* LightComponent = LightIt.Key.Get())
		{
			if(LightComponent->CastShadows && LightComponent->CastDynamicShadows && LightComponent->Mobility == ELightMobility::Movable)
			{
				auto& TempPrimitiveComponents = AffectedByLightComponents.Emplace(LightComponent);
				if(LightIt.Value.W > 0.f)
				{
					for(const auto& PrimitiveIt : PrimitiveComponents)
					{
						if(LightIt.Value.Intersects(PrimitiveIt.Value))
						{
							TempPrimitiveComponents.Emplace(PrimitiveIt.Key);
						}
					}
				}
				else
				{
					if(const UDirectionalLightComponent* DirectionalLightComponent = Cast<UDirectionalLightComponent>(LightComponent))
					{
						double DynamicShadowDistanceMovableLight = DirectionalLightComponent->DynamicShadowDistanceMovableLight;
						for(const auto& PrimitiveIt : PrimitiveComponents)
						{
							double LightDistance = FVector::Distance(LightIt.Value.Center, PrimitiveIt.Value.Center);
							if((LightDistance - PrimitiveIt.Value.W) <= DynamicShadowDistanceMovableLight)
							{
								TempPrimitiveComponents.Emplace(PrimitiveIt.Key);
							}
						}
					}
					else
					{
						PrimitiveComponents.GetKeys(TempPrimitiveComponents);
					}
				}
			}
		}
	}

	UE_LOG(LogHealthChecker, Log, TEXT("Check: Finished"));

	UpdateProgressTo(70); // 70%まで終了

	if(Progress.ShouldCancel())
	{
		return false; // abort RunImpl
	}

	bool bSkipStaticMeshActorSameMeshCheck = false;
	if(Settings.bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled)
	{
		auto IsDynamicInstancingEnabled = [&FeatureLeve]()
		{
			static TConsoleVariableData<int32>* CVarMeshDrawCommandsDynamicInstancing = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.MeshDrawCommands.DynamicInstancing"));
			if(CVarMeshDrawCommandsDynamicInstancing &&
			   CVarMeshDrawCommandsDynamicInstancing->GetValueOnAnyThread() > 0 &&
			   UseGPUScene(GMaxRHIShaderPlatform, FeatureLeve))
			{
				return true;
			}
			return false;
		};
		bSkipStaticMeshActorSameMeshCheck = IsDynamicInstancingEnabled();
	}

	UE_LOG(LogHealthChecker, Log, TEXT("Report: Start"));

	{
		// ログを収集

		TMap<EActorCategory, int32> ActorCategoryCount;
		InitializeCategoryMap(ActorCategoryCount, 0);

		TMap<EActorCategory, int32> ComponentCount;
		InitializeCategoryMap(ComponentCount, 0);

		TMap<EActorCategory, int32> ComponentMaxCount;
		InitializeCategoryMap(ComponentMaxCount, 0);
		int32 MaxAllComponentMaxCount = 0;

		TMap<EActorCategory, int32> SceneComponentCount;
		InitializeCategoryMap(SceneComponentCount, 0);

		TMap<EActorCategory, int32> PrimitiveComponentCount;
		InitializeCategoryMap(PrimitiveComponentCount, 0);

		TMap<EActorCategory, int32> MeshComponentCount;
		InitializeCategoryMap(MeshComponentCount, 0);

		TMap<EActorCategory, int32> AudioComponentCount;
		InitializeCategoryMap(AudioComponentCount, 0);

		TMap<EActorCategory, int32> ActorTickCount;
		InitializeCategoryMap(ActorTickCount, 0);
		int32 TotalActorTickCount = 0;

		TMap<EActorCategory, int32> BlueprintCount;
		InitializeCategoryMap(BlueprintCount, 0);
		int32 TotalBlueprintCount = 0;

		TMap<EActorCategory, int32> NeedsAttachParentBoundsCount;
		InitializeCategoryMap(NeedsAttachParentBoundsCount, 0);

		TMap<EActorCategory, int32> NeedsAutoManageAttachmentCount;
		InitializeCategoryMap(NeedsAutoManageAttachmentCount, 0);

		TMap<EActorCategory, int32> NeedsMultipleAudioPlayModeCount;
		InitializeCategoryMap(NeedsMultipleAudioPlayModeCount, 0);

		TMap<EActorCategory, int32> SameMaterialsInMaterialSlotsCount;
		InitializeCategoryMap(SameMaterialsInMaterialSlotsCount, 0);

		TMap<EActorCategory, int32> MismatchNumOverrideMaterialCount;
		InitializeCategoryMap(MismatchNumOverrideMaterialCount, 0);

		TMap<EActorCategory, int32> MissingMaterialsCount;
		InitializeCategoryMap(MissingMaterialsCount, 0);

		TMap<EActorCategory, int32> MissingMeshesCount;
		InitializeCategoryMap(MissingMeshesCount, 0);

		TMap<EActorCategory, int32> NoLodsMeshCount;
		InitializeCategoryMap(NoLodsMeshCount, 0);

		TMap<EActorCategory, int32> MissingComponentsCount;
		InitializeCategoryMap(MissingComponentsCount, 0);

		TMap<EActorCategory, int32> CastDynamicShadows;
		InitializeCategoryMap(CastDynamicShadows, 0);

		TMap<EActorCategory, int32> MovableLightCastDynamicShadows;
		InitializeCategoryMap(MovableLightCastDynamicShadows, 0);

		TMap<EActorCategory, int32> NavMeshCount;
		InitializeCategoryMap(NavMeshCount, 0);

		TMap<EActorCategory, int32> MeshCount;
		InitializeCategoryMap(MeshCount, 0);

		TMap<EActorCategory, int32> StaticMeshCount;
		InitializeCategoryMap(StaticMeshCount, 0);

		TMap<EActorCategory, int32> SkinningMeshCount;
		InitializeCategoryMap(SkinningMeshCount, 0);

		TMap<EActorCategory, int32> MaterialCount;
		InitializeCategoryMap(MaterialCount, 0);

		TMap<EActorCategory, TFixedArray<int32, (int32)EMaterialBlendMode::MAX>> MaterialBlendMode;
		{
			TFixedArray<int32, (int32)EMaterialBlendMode::MAX> DefaultValue;
			InitializeFixedArray(DefaultValue, 0);
			InitializeCategoryMap(MaterialBlendMode, DefaultValue);
		}

		TMap<FName, int32> StaticMeshActorSameMeshCount;
		int32 TotalStaticMeshActorSameMeshCount = 0;

		TMap<FName, int32> StaticMeshVertexCount;
		TMap<FName, int32> StaticMeshHardEdgeVertexCount;

		TMap<FName, int32> StaticMeshNaniteVertexCount;
		TMap<FName, int32> StaticMeshNaniteHardEdgeVertexCount;

		TMap<FName, int32> SkeletalMeshVertexCount;
		TMap<FName, int32> SkeletalMeshHardEdgeVertexCount;

		TMap<FName, int32> SkeletalMeshNaniteVertexCount;
		TMap<FName, int32> SkeletalMeshNaniteHardEdgeVertexCount;

		TMap<FName, int32> ParticleMeshVertexCount;
		TMap<FName, int32> ParticleMeshHardEdgeVertexCount;

		TMap<FName, int32> ParticleMeshNaniteVertexCount;
		TMap<FName, int32> ParticleMeshNaniteHardEdgeVertexCount;

		TMap<FName, int32> SkeletalMeshBoneCount;
		int32 MaxSkeletalMeshBoneCount = 0;

		TMap<FName, int32> SkeletalMeshLowestLodBoneCount;
		TMap<FName, float> SkeletalMeshBoneReductionRate;
		float MaxSkeletalMeshBoneReductionRate = 0;

		int32 TotalNiagaraSystemCount = 0;
		int32 TotalNiagaraEmitterCount = 0;
		int32 NiagaraStatefulEmitterCount = 0;
		int32 NiagaraCloseToStatelessEmitterCount = 0;

		TMap<ENiagaraSystemFlag, TArray<FName>> NiagaraSystemOptimizationHints;
		int32 TotalNiagaraSystemOptimizationHints = 0;

		TMap<ENiagaraEmitterFlag, TArray<FName>> NiagaraEmitterOptimizationHints;
		int32 TotalNiagaraEmitterOptimizationHints = 0;

		TMap<FName, int32> PostProcessPixelShaderInstructions;
		int32 TotalPostProcessPixelShaderInstructions = 0;

		TSet<FString> ErrorBrushPolygonsComponentNames;
		TSet<FString> WarningAttachParentBoundsComponentNames;
		TSet<FString> WarningAutoManageAttachmentComponentNames;
		TSet<FString> WarningAudioPlayModeComponentNames;
		TSet<FString> SameMaterialsInMaterialSlotsComponentNames;
		TSet<FString> MismatchNumOverrideMaterialComponentNames;
		TSet<FString> MissingMaterialsComponentNames;
		TSet<FString> MissingMeshesComponentNames;
		TSet<FString> NoLodsMeshComponentNames;
		TSet<FString> MissingComponentsActorNames;

		TMap<ELightType, TMap<ELightMobility, TMap<bool/*bLightCastDynamicShadows*/, int32>>> SceneLightInfo;
		int32 TotalSceneLightCount = 0;

		TMap<EActorCategory, TMap<EMobilityAndOverlapType, int32>> MobilityAndOverlapCount;

		int32 TotalActorCount = 0;
		int32 TotalStaticMeshActorCount = 0;
		int32 TotalComponentCount = 0;
		int32 TotalSceneComponentCount = 0;
		int32 TotalPrimitiveComponentCount = 0;
		int32 TotalMeshComponentCount = 0;
		int32 TotalAudioComponentCount = 0;
		int32 TotalBrushComponentCount = 0;

		for(const auto& ActorIt : ActorInfos)
		{
			const FActorInfo& ActorInfo = ActorIt.Value;

			auto AccumulateCount = [&](EActorCategory ActorCategory)
			{
				if(IsValidCategory(ActorCategory))
				{
					++ActorCategoryCount[ActorCategory];
					++TotalActorCount;

					ComponentCount[ActorCategory] += ActorInfo.ComponentCount;
					TotalComponentCount += ActorInfo.ComponentCount;

					ComponentMaxCount[ActorCategory] = FMath::Max(ComponentMaxCount[ActorCategory], ActorInfo.ComponentCount);
					MaxAllComponentMaxCount = FMath::Max(MaxAllComponentMaxCount, ComponentMaxCount[ActorCategory]);

					SceneComponentCount[ActorCategory] += ActorInfo.SceneComponentCount;
					TotalSceneComponentCount += ActorInfo.SceneComponentCount;

					PrimitiveComponentCount[ActorCategory] += ActorInfo.PrimitiveComponentCount;
					TotalPrimitiveComponentCount += ActorInfo.PrimitiveComponentCount;

					MeshComponentCount[ActorCategory] += ActorInfo.MeshComponentCount;
					TotalMeshComponentCount += ActorInfo.MeshComponentCount;

					AudioComponentCount[ActorCategory] += ActorInfo.AudioComponentCount;
					TotalAudioComponentCount += ActorInfo.AudioComponentCount;

					TotalBrushComponentCount += ActorInfo.BrushComponentCount;

					MeshCount[ActorCategory] += ActorInfo.MeshCount;
					StaticMeshCount[ActorCategory] += ActorInfo.StaticMeshCount;
					SkinningMeshCount[ActorCategory] += ActorInfo.SkinningMeshCount;
					MaterialCount[ActorCategory] += ActorInfo.MaterialCount;

					if(ActorInfo.bTickEnabled)
					{
						ActorTickCount[ActorCategory] += 1;
						TotalActorTickCount += 1;
					}
					if(ActorInfo.bIsBlueprintActor)
					{
						BlueprintCount[ActorCategory] += 1;
						TotalBlueprintCount += 1;
					}

					if((ActorInfo.ComponentCount > 1) && !ActorInfo.bIsMovable)
					{
						for(const FComponentInfo& ComponentInfo : ActorInfo.ComponentInfos)
						{
							if(ComponentInfo.bUseAttachParentBound)
							{
								continue;
							}
							if((ComponentInfo.BoundsSphereRadius.W > 0.0) && (ComponentInfo.ParentBoundsSphereRadius.W > 0.0))
							{
								if(ComponentInfo.ParentBoundsSphereRadius.Intersects(ComponentInfo.BoundsSphereRadius))
								{
									if((ComponentInfo.BoundsSphereRadius.W / ComponentInfo.ParentBoundsSphereRadius.W) < (double)Settings.WarningAttachParentBoundsScale)
									{
										++NeedsAttachParentBoundsCount[ActorCategory];
										WarningAttachParentBoundsComponentNames.Emplace(GetComponentName(ActorInfo, ComponentInfo));

										if(Settings.NeedsAttachParentBoundsCountScoreSettings.bAllowHealthCheck)
										{
											FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Needs_AttachParentBounds", "AttachParentBoundsを設定してください");
											FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Needs_AttachParentBounds_Details");
											MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get());
										}
									}
								}
							}
						}
					}

					if(ActorInfo.ComponentCount > 1)
					{
						int32 NumAudioPlayModeSingle = 0;
						for(const FComponentInfo& ComponentInfo : ActorInfo.ComponentInfos)
						{
							if(ComponentInfo.AudioPlayMode == EAudioPlayMode::Single)
							{
								if(++NumAudioPlayModeSingle > 1)
								{
									NeedsMultipleAudioPlayModeCount[ActorCategory] += 1;
									WarningAudioPlayModeComponentNames.Emplace(GetComponentName(ActorInfo, ComponentInfo));

									if(Settings.NeedsMultipleAudioPlayModeCountScoreSettings.bAllowHealthCheck)
									{
										FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Needs_Multiple_AudioPlayMode", "AudioPlayModeを設定してください");
										FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Needs_Multiple_AudioPlayMode_Details");
										MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get());
									}
								}
							}
						}
					}

					if(ActorInfo.MissingComponentIndex.Num() > 0)
					{
						MissingComponentsCount[ActorCategory] += 1;
						MissingComponentsActorNames.Emplace(GetActorName(ActorInfo));

						if(Settings.MissingComponentsCountScoreSettings.bAllowHealthCheck)
						{
							for(auto It : ActorInfo.MissingComponentIndex)
							{
								for(int32 ComponentIndex : It.Value)
								{
									FText MapCheckComment = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("MapCheck_Missing_Actors_ComponentIndex", "アクターのコンポーネント配列の{0}番に空のコンポーネントが存在します"), ComponentIndex);
									FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Missing_Actors_Component_Details");
									MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, It.Key.Get());
								}
							}
						}
					}

					for(const FComponentInfo& ComponentInfo : ActorInfo.ComponentInfos)
					{
						if(ComponentInfo.MissingMaterialIndex.Num() > 0)
						{
							for(auto It : ComponentInfo.MissingMaterialIndex)
							{
								for(int32 MaterialIndex : It.Value)
								{
									FText MapCheckComment = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("MapCheck_Missing_Components_MaterialIndex", "コンポーネントのマテリアル配列の{0}番に空のマテリアルが存在します"), MaterialIndex);
									FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Missing_Components_Material_Details");
									MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, It.Key.Get());
								}
							}
						}

						if(ComponentInfo.bCastShadows && ComponentInfo.bCastDynamicShadows && ComponentInfo.ComponentMobility == EComponentMobility::Movable)
						{
							CastDynamicShadows[ActorCategory] += 1;

							if(Settings.CastDynamicShadowRatioScoreSettings.bAllowHealthCheck)
							{
								FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Dynamic_Shadow_Ratio", "移動オブジェクトにダイナミックシャドウが設定されています");
								FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Dynamic_Shadow_Ratio_Details");
								MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get());
							}

							auto ContainsAffectedByLightComponents = [&AffectedByLightComponents, &ComponentInfo]()
							{
								for(const auto& It : AffectedByLightComponents)
								{
									if(It.Value.Contains(ComponentInfo.Component))
									{
										return true;
									}
								}
								return false;
							};

							if(ContainsAffectedByLightComponents())
							{
								MovableLightCastDynamicShadows[ActorCategory] += 1;
							}
						}
						if(ComponentInfo.MaterialBlendMode < EMaterialBlendMode::MAX)
						{
							MaterialBlendMode[ActorCategory][(int32)ComponentInfo.MaterialBlendMode] += 1;
						}
						if(ComponentInfo.bHasNavMesh)
						{
							NavMeshCount[ActorCategory] += 1;
						}

						EMobilityAndOverlapType MobilityAndOverlapType = EMobilityAndOverlapType::NoCollision;
						if(ComponentInfo.bIsCollisionEnabled)
						{
							if(ComponentInfo.ComponentMobility == EComponentMobility::Movable)
							{
								MobilityAndOverlapType = ComponentInfo.bGenerateOverlapEvents ? EMobilityAndOverlapType::MovableAndOverlap : EMobilityAndOverlapType::Movable;
							}
							else
							{
								MobilityAndOverlapType = ComponentInfo.bGenerateOverlapEvents ? EMobilityAndOverlapType::StaticAndOverlap : EMobilityAndOverlapType::Static;
							}
							if(MobilityAndOverlapType == EMobilityAndOverlapType::MovableAndOverlap)
							{
								if(Settings.OverlapCountScoreSettings.bAllowHealthCheck)
								{
									FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Movable_Overlap_Component", "移動オブジェクトにオーバーラップが有効になっています");
									FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Overlap_Distribution_Details");
									MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get());
								}
							}
						}
						MobilityAndOverlapCount.FindOrAdd(ActorCategory).FindOrAdd(MobilityAndOverlapType) += 1;

						if(ComponentInfo.bErrorBrushPolygons)
						{
							ErrorBrushPolygonsComponentNames.Emplace(GetComponentName(ActorInfo, ComponentInfo));

							if(Settings.ErrorBrushPolygonsRatioScoreSettings.bAllowHealthCheck)
							{
								FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Error_Brush_Polygons", "穴の空いたブラシが存在します");
								FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Error_Brush_Polygons_Details");
								MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get());
							}
						}

						if(ComponentInfo.AutoManageAttachment == EAutoManageAttachment::Manual)
						{
							NeedsAutoManageAttachmentCount[ActorCategory] += 1;
							WarningAutoManageAttachmentComponentNames.Emplace(GetComponentName(ActorInfo, ComponentInfo));

							if(Settings.NeedsAutoManageAttachmentCountScoreSettings.bAllowHealthCheck)
							{
								FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Needs_AutoManageAttachment", "AutoManageAttachmentを設定してください");
								FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Needs_AutoManageAttachment_Details");
								MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get());
							}
						}

						if(ComponentInfo.bSameMaterialsInMaterialSlots)
						{
							SameMaterialsInMaterialSlotsCount[ActorCategory] += 1;
							SameMaterialsInMaterialSlotsComponentNames.Emplace(GetComponentName(ActorInfo, ComponentInfo));

							if(Settings.SameMaterialsInMaterialSlotsCountScoreSettings.bAllowHealthCheck)
							{
								FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Same_Materials_In_Material_Slots", "複数のマテリアルスロットに同じマテリアルが重複して存在します");
								FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Same_Materials_In_Material_Slots_Details");
								MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get(), TEXT("Mesh"), ComponentInfo.Mesh.Get());
							}
						}
						for(auto It : ComponentInfo.ParticleMeshInfos)
						{
							if(It.Value.bSameMaterialsInMaterialSlots)
							{
								SameMaterialsInMaterialSlotsCount[ActorCategory] += 1;
								SameMaterialsInMaterialSlotsComponentNames.Emplace(GetComponentName(ActorInfo, ComponentInfo));

								if(Settings.SameMaterialsInMaterialSlotsCountScoreSettings.bAllowHealthCheck)
								{
									FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Same_Materials_In_Material_Slots", "複数のマテリアルスロットに同じマテリアルが重複して存在します");
									FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Same_Materials_In_Material_Slots_Details");
									MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get(), TEXT("Mesh"), It.Value.Mesh.Get());
								}
							}
						}
						if(ComponentInfo.bMismatchNumOverrideMaterial)
						{
							MismatchNumOverrideMaterialCount[ActorCategory] += 1;
							MismatchNumOverrideMaterialComponentNames.Emplace(GetComponentName(ActorInfo, ComponentInfo));

							if(Settings.MismatchNumOverrideMaterialCountScoreSettings.bAllowHealthCheck)
							{
								FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Mismatch_OverrideMaterial_Count", "オーバーライドマテリアルの数が元のマテリアルの数と一致していません");
								FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Mismatch_OverrideMaterial_Count_Details");
								MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get(), TEXT("Mesh"), ComponentInfo.Mesh.Get());
							}
						}

						if(!ComponentInfo.bMissingMeshes && ComponentInfo.bMissingMaterials)
						{
							MissingMaterialsCount[ActorCategory] += 1;
							MissingMaterialsComponentNames.Emplace(GetComponentName(ActorInfo, ComponentInfo));

							if(Settings.MissingMaterialsCountScoreSettings.bAllowHealthCheck)
							{
								FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Missing_Components_Material", "マテリアルがアサインされていません");
								FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Missing_Components_Material_Details");
								MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get(), TEXT("Mesh"), ComponentInfo.Mesh.Get());
							}
						}

						auto CalcHardEdgeVertices = [](int32 NumVertices, int32 NumTriangles)
						{
							return FMath::Max(0, NumVertices - NumTriangles / 2);
						};

						if(ComponentInfo.bMissingMeshes)
						{
							MissingMeshesCount[ActorCategory] += 1;
							MissingMeshesComponentNames.Emplace(GetComponentName(ActorInfo, ComponentInfo));

							if(Settings.MissingMeshesCountScoreSettings.bAllowHealthCheck)
							{
								FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_Missing_Components_Mesh", "メッシュがアサインされていません");
								FText MapCheckDocuments = HC4UE_GET_LOCTEXT("Missing_Components_Mesh_Details");
								MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get());
							}
						}
						else
						{
							if(ComponentInfo.bNoLodsMesh && !ComponentInfo.bIsNaniteMesh)
							{
								NoLodsMeshCount[ActorCategory] += 1;
								NoLodsMeshComponentNames.Emplace(GetComponentName(ActorInfo, ComponentInfo));

								if(Settings.NoLodsMeshCountScoreSettings.bAllowHealthCheck)
								{
									FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_No_LODs_Meshes", "LODが生成されていません");
									FText MapCheckDocuments = HC4UE_GET_LOCTEXT("No_LODs_Meshes_Details");
									MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get(), TEXT("Mesh"), ComponentInfo.Mesh.Get());
								}
							}

							if(!ComponentInfo.MeshName.IsNone())
							{
								if(ComponentInfo.BoneCount > 0)
								{
									SkeletalMeshBoneCount.FindOrAdd(ComponentInfo.MeshName) = ComponentInfo.BoneCount;
									MaxSkeletalMeshBoneCount = FMath::Max(MaxSkeletalMeshBoneCount, ComponentInfo.BoneCount);
									if(ComponentInfo.BoneCount > Settings.IgnoreBoneReductionRateBoneCountThreshold)
									{
										SkeletalMeshLowestLodBoneCount.FindOrAdd(ComponentInfo.MeshName) = ComponentInfo.LowestLodBoneCount;
										SkeletalMeshBoneReductionRate.FindOrAdd(ComponentInfo.MeshName) = ComponentInfo.BoneReductionRate;
										MaxSkeletalMeshBoneReductionRate = FMath::Max(MaxSkeletalMeshBoneReductionRate, ComponentInfo.BoneReductionRate);
									}
								}

								TMap<FName, int32>* TargetVertexCount = nullptr;
								TMap<FName, int32>* TargetHardEdgeVertexCount = nullptr;
								TMap<FName, int32>* TargetNaniteVertexCount = nullptr;
								TMap<FName, int32>* TargetNaniteHardEdgeVertexCount = nullptr;

								if(ActorCategory == EActorCategory::StaticMesh)
								{
									TargetVertexCount = &StaticMeshVertexCount;
									TargetHardEdgeVertexCount = &StaticMeshHardEdgeVertexCount;
									TargetNaniteVertexCount = &StaticMeshNaniteVertexCount;
									TargetNaniteHardEdgeVertexCount = &StaticMeshNaniteHardEdgeVertexCount;
								}
								else
								if(ActorCategory == EActorCategory::SkeletalMesh)
								{
									TargetVertexCount = &SkeletalMeshVertexCount;
									TargetHardEdgeVertexCount = &SkeletalMeshHardEdgeVertexCount;
									TargetNaniteVertexCount = &SkeletalMeshNaniteVertexCount;
									TargetNaniteHardEdgeVertexCount = &SkeletalMeshNaniteHardEdgeVertexCount;
								}

								if(TargetVertexCount && ComponentInfo.NumVertices > 0)
								{
									if(!ComponentInfo.bIsNaniteMesh)
									{
										TargetVertexCount->FindOrAdd(ComponentInfo.MeshName) = ComponentInfo.NumVertices;
										int32 HardEdgeVertices = CalcHardEdgeVertices(ComponentInfo.NumVertices, ComponentInfo.NumTriangles);
										if(HardEdgeVertices > 0)
										{
											TargetHardEdgeVertexCount->FindOrAdd(ComponentInfo.MeshName) = HardEdgeVertices;
										}
									}
									else
									{
										TargetNaniteVertexCount->FindOrAdd(ComponentInfo.MeshName) = ComponentInfo.NumVertices;
										int32 HardEdgeVertices = CalcHardEdgeVertices(ComponentInfo.NumVertices, ComponentInfo.NumTriangles);
										if(HardEdgeVertices > 0)
										{
											TargetNaniteHardEdgeVertexCount->FindOrAdd(ComponentInfo.MeshName) = HardEdgeVertices;
										}
									}
								}
							}
						}

						if(ActorCategory == EActorCategory::Particle && ComponentInfo.ParticleMeshInfos.Num() > 0)
						{
							for(auto& ParticleMeshInfo : ComponentInfo.ParticleMeshInfos)
							{
								if(ParticleMeshInfo.Value.NumVertices == 0)
								{
									continue;
								}

								if(!ParticleMeshInfo.Value.bIsNaniteMesh)
								{
									ParticleMeshVertexCount.FindOrAdd(ParticleMeshInfo.Key) = ParticleMeshInfo.Value.NumVertices;
									int32 HardEdgeVertices = CalcHardEdgeVertices(ParticleMeshInfo.Value.NumVertices, ParticleMeshInfo.Value.NumTriangles);
									if(HardEdgeVertices > 0)
									{
										ParticleMeshHardEdgeVertexCount.FindOrAdd(ParticleMeshInfo.Key) = HardEdgeVertices;
									}
								}
								else
								{
									ParticleMeshNaniteVertexCount.FindOrAdd(ParticleMeshInfo.Key) = ParticleMeshInfo.Value.NumVertices;
									int32 HardEdgeVertices = CalcHardEdgeVertices(ParticleMeshInfo.Value.NumVertices, ParticleMeshInfo.Value.NumTriangles);
									if(HardEdgeVertices > 0)
									{
										ParticleMeshNaniteHardEdgeVertexCount.FindOrAdd(ParticleMeshInfo.Key) = HardEdgeVertices;
									}
								}
							}
						}

						if(!ComponentInfo.NiagaraInfo.SystemName.IsNone())
						{
							if(ComponentInfo.NiagaraInfo.MissingEmitterIndex.Num() > 0)
							{
								for(auto It : ComponentInfo.NiagaraInfo.MissingEmitterIndex)
								{
									for(int32 EmitterIndex : It.Value)
									{
										FText MapCheckComment = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("MapCheck_Missing_NiagaraSystems_EmitterIndex", "NiagaraSystemのエミッター配列の{0}番に空のエミッターが存在します"), EmitterIndex);
										FText MapCheckDocuments = HC4UE_LOCTEXT("Missing_NiagaraSystems_Emitter_Details", "NiagaraSystemのエミッター配列に空のエミッターが存在します。エミッタークラスがなくなったり、内部データが壊れている可能性があります。Niagaraエディターでアセットを開いて確認してください。");
										MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get(), TEXT("System"), It.Key.Get());
									}
								}
							}

							if(ComponentInfo.NiagaraInfo.MissingMaterialIndex.Num() > 0)
							{
								for(auto It : ComponentInfo.NiagaraInfo.MissingMaterialIndex)
								{
									for(int32 MaterialIndex : It.Value)
									{
										FText MapCheckComment = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("MapCheck_Missing_NiagaraRenderers_MaterialIndex", "NiagaraSystemのRenderer配列の{0}番に空のRendererが存在します"), MaterialIndex);
										FText MapCheckDocuments = HC4UE_LOCTEXT("Missing_NiagaraRenderers_Material_Details", "NiagaraSystemのRendererに空のマテリアルが含まれています。Rendererにマテリアル設定がされていないか、メッシュのマテリアルやオーバーライドマテリアルに空のマテリアルが含まれていないか確認してください。");
										FString LinkLabel = GetObjectName(It.Key.Get(), 1);
										MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get(), TEXT("Renderer"), It.Key.Get(), &LinkLabel);
									}
								}
							}

							auto GetNiagaraSystemMapCheckComment = [&Settings](const ENiagaraSystemFlag& SystemFlag, FText& MapCheckComment, FText& MapCheckDocuments)
							{
								switch(SystemFlag)
								{
								case ENiagaraSystemFlag::A_NoValidation:
									MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_System_Optimization_Hints_A", "Niagara設定にValidationRulesを設定して下さい");
									MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_System_Optimization_Hints_A_Details");
									return true;
								case ENiagaraSystemFlag::B_MissingEffectType:
									MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_System_Optimization_Hints_B", "NiagaraSystemにEffectTypeが設定されていません");
									MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_System_Optimization_Hints_B_Details");
									return true;
								case ENiagaraSystemFlag::C_NotFixedBounds:
									MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_System_Optimization_Hints_C", "NiagaraSystemのBoundsが毎フレーム再計算されています");
									MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_System_Optimization_Hints_C_Details");
									return true;
								case ENiagaraSystemFlag::D_LongWarmupTime:
									MapCheckComment = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("MapCheck_Niagara_System_Optimization_Hints_D", "NiagaraSystemのWarmupTimeの時間が{0}秒を超えています"), Settings.WarningNiagaraWarmupTime);
									MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_System_Optimization_Hints_D_Details");
									return true;
								case ENiagaraSystemFlag::E_MultipleLightRenderers:
									MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_System_Optimization_Hints_E", "１つのNiagaraエミッター内に複数のLight Rendererが存在しています");
									MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_System_Optimization_Hints_E_Details");
									return true;
								}

								ensure(false);
								return false;
							};

							++TotalNiagaraSystemCount;
							for(const ENiagaraSystemFlag& SystemFlag : ComponentInfo.NiagaraInfo.SystemFlags)
							{
								NiagaraSystemOptimizationHints.FindOrAdd(SystemFlag).Emplace(ComponentInfo.NiagaraInfo.SystemName);
								++TotalNiagaraSystemOptimizationHints;

								if(Settings.NiagaraSystemOptimizationHintsScoreSettings.bAllowHealthCheck)
								{
									FText MapCheckComment, MapCheckDocuments;
									if(GetNiagaraSystemMapCheckComment(SystemFlag, MapCheckComment, MapCheckDocuments))
									{
										MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get(), TEXT("System"), ComponentInfo.NiagaraInfo.System.Get());
									}
								}
							}

							for(const FNiagaraEmitterInfo& EmitterInfo : ComponentInfo.NiagaraInfo.EmitterInfos)
							{
								auto GetNiagaraEmitterMapCheckComment = [&Settings](const ENiagaraEmitterFlag& EmitterFlag, FText& MapCheckComment, FText& MapCheckDocuments)
								{
									switch(EmitterFlag)
									{
									case ENiagaraEmitterFlag::A_LifeCycleIsSelf:
										MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_Emitter_Optimization_Hints_A", "Emitter StateがSelfのためエミッターごとのループ制御が行われています");
										MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_Emitter_Optimization_Hints_A_Details");
										return true;
									case ENiagaraEmitterFlag::B_NeedsSpriteCutout:
										MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_Emitter_Optimization_Hints_B", "半透明のSprite RendererにCutoutTextureが設定されていません");
										MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_Emitter_Optimization_Hints_B_Details");
										return true;
									case ENiagaraEmitterFlag::C_NeedsEmitterSourceMode:
										MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_Emitter_Optimization_Hints_C", "パーティクルが１つしか発生しないのでSource ModeをParticlesからEmitterに変更できます");
										MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_Emitter_Optimization_Hints_C_Details");
										return true;
									case ENiagaraEmitterFlag::D_ManyRenderer:
										MapCheckComment = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("MapCheck_Niagara_Emitter_Optimization_Hints_D", "NiagaraSystemのRendererの数が{0}個を超えています"), Settings.WarningNiagaraRendererCount);
										MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_Emitter_Optimization_Hints_D_Details");
										return true;
									case ENiagaraEmitterFlag::E_SkeletalMeshSampling:
										MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_Emitter_Optimization_Hints_E", "Mesh RendererでSkeletalMeshのサンプリング描画が行われています");
										MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_Emitter_Optimization_Hints_E_Details");
										return true;
									case ENiagaraEmitterFlag::F_MeshRendererWithDistanceFieldMesh:
										MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_Emitter_Optimization_Hints_F", "Mesh RendererでDistanceFieldがONのメッシュが使用されています");
										MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_Emitter_Optimization_Hints_F_Details");
										return true;
									case ENiagaraEmitterFlag::G_MeshRendererWithCollisionMesh:
										MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_Emitter_Optimization_Hints_G", "Mesh Rendererで使用されないコリジョンを持つメッシュが使用されています");
										MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_Emitter_Optimization_Hints_G_Details");
										return true;
									case ENiagaraEmitterFlag::H_MeshRendererWithMultiUVMesh:
										MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_Emitter_Optimization_Hints_H", "Mesh Rendererで複数のUVを持つメッシュが使用されています");
										MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_Emitter_Optimization_Hints_H_Details");
										return true;
									case ENiagaraEmitterFlag::I_LargeVolumeTexture:
										MapCheckComment = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("MapCheck_Niagara_Emitter_Optimization_Hints_I", "Mesh RendererでVolumeTextureのサイズが{0}x{0}x{0}を超えているテクスチャが存在します"), Settings.WarningNiagaraVolumeTextureSize);
										MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_Emitter_Optimization_Hints_I_Details");
										return true;
									case ENiagaraEmitterFlag::J_StatefulEmitter:
										return false;
									case ENiagaraEmitterFlag::K_CloseToStatelessEmitter:
										MapCheckComment = HC4UE_LOCTEXT("MapCheck_Niagara_Emitter_Optimization_Hints_K", "Stateless化が可能なNiagaraエミッターが存在します");
										MapCheckDocuments = HC4UE_GET_LOCTEXT("Niagara_Stateful_Emitter_Details");
										return true;
									}

									ensure(false);
									return false;
								};

								++TotalNiagaraEmitterCount;
								for(const ENiagaraEmitterFlag& EmitterFlag : EmitterInfo.EmitterFlags)
								{
									bool bAllowHealthCheck = false;
									if(EmitterFlag == ENiagaraEmitterFlag::J_StatefulEmitter)
									{
										bAllowHealthCheck = Settings.NiagaraStatefulEmitterRatioScoreSettings.bAllowHealthCheck;
										++NiagaraStatefulEmitterCount;
									}
									else
									if(EmitterFlag == ENiagaraEmitterFlag::K_CloseToStatelessEmitter)
									{
										bAllowHealthCheck = Settings.NiagaraStatefulEmitterRatioScoreSettings.bAllowHealthCheck;
										++NiagaraCloseToStatelessEmitterCount;
									}
									else
									{
										bAllowHealthCheck = Settings.NiagaraEmitterOptimizationHintsScoreSettings.bAllowHealthCheck;
										NiagaraEmitterOptimizationHints.FindOrAdd(EmitterFlag).Emplace(EmitterInfo.EmitterName);
										++TotalNiagaraEmitterOptimizationHints;
									}

									if(bAllowHealthCheck)
									{
										FText MapCheckComment, MapCheckDocuments;
										if(GetNiagaraEmitterMapCheckComment(EmitterFlag, MapCheckComment, MapCheckDocuments))
										{
											MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ComponentInfo.Component.Get(), TEXT("Emitter"), EmitterInfo.Emitter.Get());
										}
									}
								}
							}
						}
					}
				}
			};

			if(ActorInfo.HasAnySkeletalMeshComponent())
			{
				AccumulateCount(EActorCategory::SkeletalMesh);
			}
			else
			if(ActorInfo.HasAnyStaticMeshComponent() || ActorInfo.bIsLandscapeActor || ActorInfo.HasAnyLandscapeComponent() || ActorInfo.HasAnyWaterComponent())
			{
				AccumulateCount(EActorCategory::StaticMesh);
			}
			else
			if(ActorInfo.HasAnyParticleComponent())
			{
				AccumulateCount(EActorCategory::Particle);
			}
			else
			if(ActorInfo.bIsAudioActor || ActorInfo.HasAnyAudioComponent())
			{
				AccumulateCount(EActorCategory::Audio);
			}
			else
			if(ActorInfo.bIsRenderingActor)
			{
				AccumulateCount(EActorCategory::Rendering);
			}
			else
			if(ActorInfo.bIsGameplayActor)
			{
				AccumulateCount(EActorCategory::Gameplay);
			}
			else
			if(ActorInfo.bIsVolumeActor)
			{
				AccumulateCount(EActorCategory::Volume);
			}
			else
			if(ActorInfo.bIsGeometryActor
			|| ActorInfo.HasAnyDynamicMeshComponent() || ActorInfo.HasAnyGeometryComponent() || ActorInfo.HasAnyCustomVertexComponent()
			)
			{
				AccumulateCount(EActorCategory::Geometry);
			}
			else
			if(ActorInfo.HasAnyLightComponent())
			{
				AccumulateCount(EActorCategory::Rendering);
			}
			else
			{
				AccumulateCount(EActorCategory::Other);

				if(!ActorInfo.ActorLabelName.IsEmpty())
				{
					UE_LOG(LogHealthChecker, Warning, TEXT("Other Category Actor: %s: %s"), *ActorInfo.ActorLabelName, *ActorInfo.ActorFullName);
				}
				else
				{
					UE_LOG(LogHealthChecker, Warning, TEXT("Other Category Actor: %s"), *ActorInfo.ActorFullName);
				}
			}

			if(ActorInfo.bIsStaticMeshActor && !bSkipStaticMeshActorSameMeshCheck)
			{
				if(!ActorInfo.StaticMeshActorMeshName.IsNone())
				{
					const FName& StaticMeshActorMeshName = ActorInfo.StaticMeshActorMeshName;
					if(!StaticMeshActorSameMeshCount.Find(StaticMeshActorMeshName))
					{
						StaticMeshActorSameMeshCount.Emplace(StaticMeshActorMeshName, 1);
					}
					else
					{
						if(Settings.StaticMeshActorSameMeshCountScoreSettings.bAllowHealthCheck)
						{
							FText MapCheckComment = HC4UE_LOCTEXT("MapCheck_StaticMeshActor_Same_Mesh_Count", "同じスタティクメッシュがアサインされているStaticMeshActorが存在します");
							FText MapCheckDocuments = HC4UE_GET_LOCTEXT("StaticMeshActor_Same_Mesh_Count_Details");
							MessageLog.PerformanceWarning(MapCheckComment, MapCheckDocuments, ActorInfo.StaticMeshActorComponent.Get(), TEXT("Mesh"), ActorInfo.StaticMeshActorComponent.IsValid() ? ActorInfo.StaticMeshActorComponent.Get()->GetStaticMesh() : nullptr);
						}

						++StaticMeshActorSameMeshCount[StaticMeshActorMeshName];
						++TotalStaticMeshActorSameMeshCount;
					}
				}
				++TotalStaticMeshActorCount;
			}

			for(const FLightInfo& LightInfo : ActorInfo.LightInfos)
			{
				if(LightInfo.LightType != ELightType::MAX)
				{
					SceneLightInfo.FindOrAdd(LightInfo.LightType).FindOrAdd(LightInfo.LightMobility).FindOrAdd(LightInfo.bLightCastShadows && LightInfo.bLightCastDynamicShadows) += 1;
					++TotalSceneLightCount;
				}
			}

			Progress.EnterProgressFrame(SafeDivide<float>(1, ActorInfos.Num()) * 10.f); // 70～80%まで分割更新

			if(Progress.ShouldCancel())
			{
				return false; // abort RunImpl
			}
		}

		UpdateProgressTo(80); // 80%まで終了

		if(CurrentWorld->PostProcessVolumes.Num() > 0)
		{
			for(const IInterface_PostProcessVolume* PostProcessVolumeInterface : CurrentWorld->PostProcessVolumes)
			{
				if(const FPostProcessSettings* PostProcessSettings = PostProcessVolumeInterface->GetProperties().Settings)
				{
					for(const FWeightedBlendable& Blendable : PostProcessSettings->WeightedBlendables.Array)
					{
#if HC4UE_UE5
						if(UMaterialInterface* Material = Cast<UMaterialInterface>(Blendable.Object.Get()))
#else
						if(UMaterialInterface* Material = Cast<UMaterialInterface>(Blendable.Object))
#endif
						{
							FMaterialStatistics Stats = UMaterialEditingLibrary::GetStatistics(Material);
							PostProcessPixelShaderInstructions.Emplace(Material->GetPathName(), Stats.NumPixelShaderInstructions);
							TotalPostProcessPixelShaderInstructions += Stats.NumPixelShaderInstructions;
							if(Stats.NumPixelShaderInstructions >= Settings.WarningPostProcessPixelShaderInstructions && Settings.PostProcessPixelShaderInstructionsScoreSettings.bAllowHealthCheck)
							{
								FText MapCheckComment = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("MapCheck_PostProcess_PixelShader_Instructions", "ポストプロセスのピクセルシェーダー命令数が {0} をオーバーしています"), Settings.WarningPostProcessPixelShaderInstructions);
								UE_CLOG(Settings.bPostToLog, LogHealthChecker, Warning, TEXT("%s: %s, %s"), *MapCheckComment.ToString(), *GetFullNameSafe(Material), *GetFullNameSafe((UObject*)PostProcessVolumeInterface));
								if(Settings.bPostToMapCheck)
								{
									FText MapCheckDocuments = HC4UE_GET_LOCTEXT("PostProcess_PixelShader_Instructions_Details");
									MessageLog.PerformanceWarning()
										->AddToken(FTextToken::Create(MapCheckComment))
										->AddToken(FTextToken::Create(FText::FromString(TEXT(" Material:"))))
										->AddToken(FUObjectToken::Create(Material))
										->AddToken(FTextToken::Create(FText::FromString(TEXT(" PostProcess:"))))
										->AddToken(FUObjectToken::Create((UObject*)PostProcessVolumeInterface))
										->AddToken(FDocumentationToken::Create(MessageLog.GetDocumentURL(MapCheckDocuments.ToString())));
								}
							}
						}
					}
				}
			}
		}

		TMap<ETextureSize, TMap<bool/*Compressed*/, int32>> StreamingTextureSizeMap;
		TMap<ETextureSize, TMap<bool/*Compressed*/, int32>> NonStreamingTextureSizeMap;
		TMap<ETextureSize, TMap<bool/*Compressed*/, int32>> StreamedInTextureSizeMap;
		TMap<bool/*Compressed*/, int32> StreamingTextureCount;
		TMap<bool/*Compressed*/, int32> NonStreamingTextureCount;
		TMap<bool/*Compressed*/, int32> StreamedInTextureCount;
		for(const FTextureInfo& TextureInfo : TextureInfos)
		{
			ETextureSize TextureSize = GetTextureSize(TextureInfo.CurSizeX, TextureInfo.CurSizeY);
			if(TextureInfo.bIsStreamingTexture)
			{
				StreamingTextureSizeMap.FindOrAdd(TextureSize).FindOrAdd(TextureInfo.bIsCompressed) += 1;
				StreamingTextureCount.FindOrAdd(TextureInfo.bIsCompressed) += 1;
			}
			else
			{
				NonStreamingTextureSizeMap.FindOrAdd(TextureSize).FindOrAdd(TextureInfo.bIsCompressed) += 1;
				NonStreamingTextureCount.FindOrAdd(TextureInfo.bIsCompressed) += 1;
			}

			if(TextureInfo.bIsStreamedIn)
			{
				StreamedInTextureSizeMap.FindOrAdd(TextureSize).FindOrAdd(TextureInfo.bIsCompressed) += 1;
				StreamedInTextureCount.FindOrAdd(TextureInfo.bIsCompressed) += 1;
			}

			{
				//static_assert((int32)EReportWarningTextureSize::MAX == (int32)ETextureSize::MAX, "Mismatch between EReportWarningTextureSize and HC4UE::ETextureSize");
				int32 WarningTextureSize = TextureInfo.bIsCompressed ? (int32)Settings.WarningCompressedTextureSize : (int32)Settings.WarningUncompressedTextureSize;
				if((int32)TextureSize <= WarningTextureSize)
				{
					FText WordCompressed = HC4UE_LOCTEXT("Word_Compressed", "圧縮");
					FText WordUncompressed = HC4UE_LOCTEXT("Word_Uncompressed", "非圧縮");
					FText MapCheckComment = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("MapCheck_Large_Texture", "大きなサイズの{0}テクスチャ ({1}x{2}) を発見しました"), TextureInfo.bIsCompressed ? WordCompressed : WordUncompressed, TextureInfo.CurSizeX, TextureInfo.CurSizeY);
					UE_CLOG(Settings.bPostToLog, LogHealthChecker, Warning, TEXT("%s: %s"), *MapCheckComment.ToString(), *GetFullNameSafe(TextureInfo.Texture.Get()));
					if(Settings.bPostToMapCheck)
					{
						FText MapCheckDocuments;
						bool bAllowHealthCheck = true;
						if(TextureInfo.bIsStreamingTexture)
						{
							MapCheckDocuments = TextureInfo.bIsCompressed ? HC4UE_GET_LOCTEXT("Streaming_Compress_Texture_Details") : HC4UE_GET_LOCTEXT("Streaming_Uncompress_Texture_Details");
							bAllowHealthCheck = Settings.StreamingTextureCountScoreSettings.bAllowHealthCheck;
						}
						else
						{
							MapCheckDocuments = TextureInfo.bIsCompressed ? HC4UE_GET_LOCTEXT("Non_Streaming_Compress_Texture_Details") : HC4UE_GET_LOCTEXT("Non_Streaming_Uncompress_Texture_Details");
							bAllowHealthCheck = Settings.NonStreamingTextureCountScoreSettings.bAllowHealthCheck;
						}
						if(bAllowHealthCheck)
						{
							MessageLog.PerformanceWarning()
								->AddToken(FTextToken::Create(MapCheckComment))
								->AddToken(FTextToken::Create(FText::FromString(TEXT(" Texture:"))))
								->AddToken(FUObjectToken::Create(TextureInfo.Texture.Get()))
								->AddToken(FDocumentationToken::Create(MessageLog.GetDocumentURL(MapCheckDocuments.ToString())));
						}
					}
				}
			}

			Progress.EnterProgressFrame(SafeDivide<float>(1, TextureInfos.Num()) * 10.f); // 80～90%まで分割更新

			if(Progress.ShouldCancel())
			{
				return false; // abort RunImpl
			}
		}

		UpdateProgressTo(90); // 90%まで終了

		// 結果を出力
		UE_LOG(LogHealthChecker, Log, TEXT("===== HealthChecker Summary ====="));

		auto IsValidCategory = [&ActorCategoryCount](EActorCategory ActorCategory)->bool
		{
			return HC4UE::IsValidCategory(ActorCategory) && (ActorCategoryCount[ActorCategory] > 0);
		};

		TArray<FString> StringArray, StringArray2;
		TArray<FHealthCheckerChartData> ChartDataArray, ChartDataArray2;

		static constexpr int32 MaxReportCount = 45;
		int32 CurrentReportCount = 0;
		auto ProgressReport = [&Progress, &CurrentReportCount]()
		{
			++CurrentReportCount;
			ensure(CurrentReportCount <= MaxReportCount);
			Progress.EnterProgressFrame(SafeDivide<float>(1, MaxReportCount) * 10.f); // 90～100%を分割更新
		};

		if(TotalLevelCount > 0 && Settings.LevelCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetLevelCountScoreDescription = [&Settings](EScore LevelCountScore, int32 LevelCount)
			{
				if(LevelCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Level_Distribution_Description", "レベルの数が{0}個以内 ({1}n) に収まっています。"), Settings.LevelCountScoreSettings[LevelCountScore], LevelCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Level_Distribution_Over_Description", "レベルの数が{0}個をオーバー ({1}n) しています。"), Settings.LevelCountScoreSettings[EScore::D], LevelCount);
				}
			};
			auto GetLevelCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Level_Distribution_Details", "管理するレベルが多すぎると管理コストやストリーミングが複雑化するため注意が必要です。");
			};

			for(const auto& It : LevelCategoryCount)
			{
				for(const auto& It2 : It.Value)
				{
					if(It2.Value > 0)
					{
						FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
						FString Label = GetLevelCategoryName(It.Key) + (It2.Key ? TEXT(" (Visible)") : TEXT(" (Hide)"));
						ChartData.Label = Label;
						ChartData.Value = It2.Value;
						ChartData.TotalValue = TotalLevelCount;
						ChartData.TotalLabel = TEXT("Total Level Ratio");
						StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *Label, SafeDivideToPercentage<float>(It2.Value, TotalLevelCount), It2.Value, TotalLevelCount));
					}
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalLevelCount, Settings.LevelCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Level_Distribution"), { MoveTemp(ChartDataArray), Score, GetLevelCountScoreDescription(Score.Score, TotalLevelCount), { GetLevelCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Level_Distribution", "Level Distribution");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(MapLoadTimes.Num() > 0 && Settings.MapLoadTimeScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto SecToMilliSec = [](float Sec)
			{
				return Sec * 1000;
			};
			auto GetMapLoadTimeScoreDescription = [&Settings, &SecToMilliSec](EScore MapLoadTimeScore, int32 MapLoadTimeScoreCount)
			{
				if(MapLoadTimeScore == EScore::A)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Map_Load_Time_Ranking_Description", "マップのロード時間が全て{0}ミリ秒以内に収まっています。"), SecToMilliSec(Settings.MapLoadTimeScoreSettings[MapLoadTimeScore]));
				}
				else
				if(MapLoadTimeScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Map_Load_Time_Ranking_Range_Description", "マップのロード時間が{0}ミリ秒より大きく{1}ミリ秒以内のものが{2}個存在します。"), SecToMilliSec(Settings.MapLoadTimeScoreSettings[GetBeforeScore(MapLoadTimeScore)]), SecToMilliSec(Settings.MapLoadTimeScoreSettings[MapLoadTimeScore]), MapLoadTimeScoreCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Map_Load_Time_Ranking_Over_Description", "マップのロード時間が{0}ミリ秒より大きいものが{1}個存在します。"), SecToMilliSec(Settings.MapLoadTimeScoreSettings[EScore::D]), MapLoadTimeScoreCount);
				}
			};
			auto GetMapLoadTimeScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Map_Load_Time_Details", "マップのロードに時間かかる場合はマップの表示が間に合わなかったり、不要なアセットの読み込みが多くなります。レベルの分割やワールドパーティションのセルの分割を検討して下さい。");
			};

			TArray<FScore> ScoreArray;
			MapLoadTimes.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			bool bHasValue = false;
			for(const auto& It : MapLoadTimes)
			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = FPaths::GetBaseFilename(It.Key);
				ChartData.Value = SecToMilliSec(It.Value);
				if(ChartData.Value > 0)
				{
					bHasValue = true;
				}
				ChartData.Unit = TEXT("ms");
				ChartData.TotalValue = SecToMilliSec(TotalMapLoadTime);
				ChartData.TotalLabel = TEXT("Total Map Load Time Ratio");
				StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%.1fs/%.1fs)"), *ChartData.Label, SafeDivideToPercentage<float>(It.Value, TotalMapLoadTime), It.Value, TotalMapLoadTime));
				ScoreArray.Emplace(GetScore(It.Value, Settings.MapLoadTimeScoreSettings));
			}
			if(StringArray.Num() > 0)
			{
				FScore WorstScore;
				for(int32 i = ((int32)EScore::MAX - 1); i >= 0; --i)
				{
					if(ScoreArray.RemoveAll([&i](const FScore& Score){ return Score.Score == (EScore)i; }) > 0)
					{
						WorstScore = { (EScore)i, Settings.MapLoadTimeScoreSettings.ScoreWeight, Settings.MapLoadTimeScoreSettings.bAllowHealthCheck };
						break;
					}
				}
				if(bHasValue)
				{
					const FScore& Score = AllScoreArray.Emplace_GetRef(WorstScore);
					HealthCheckerReport.Add(TEXT("Map_Load_Time"), { MoveTemp(ChartDataArray), Score, GetMapLoadTimeScoreDescription(Score.Score, ScoreArray.Num()), { GetMapLoadTimeScoreDetails() } });
				}

				FText GraphName = HC4UE_LOCTEXT("Map_Load_Time", "Map Load Time");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: Total %.2fs, %s"), *GraphName.ToString(), TotalMapLoadTime, *StringJoin(StringArray, TEXT(", "), Settings.MaxDisplayMapLoadTimeRanking));
			}
		}

		ProgressReport();

		if(Settings.ActorCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetActorCountScoreDescription = [&Settings](EScore ActorCountScore, int32 ActorCount)
			{
				if(ActorCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Actor_Category_Distribution_Description", "アクターの数が{0}個以内 ({1}n) に収まっています。"), Settings.ActorCountScoreSettings[ActorCountScore], ActorCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Actor_Category_Distribution_Over_Description", "アクターの数が{0}個をオーバー ({1}n) しています。"), Settings.ActorCountScoreSettings[EScore::D], ActorCount);
				}
			};
			auto GetActorCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Actor_Category_Distribution_Details", "シーンに存在するアクターが多すぎると管理コストや実行時のオーバーヘッドが大きくなるので注意が必要です。");
			};

			for(const auto& It : ActorCategoryCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = TotalActorCount;
					ChartData.TotalLabel = TEXT("Total Actor Ratio");
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalActorCount, Settings.ActorCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Actor_Category_Distribution"), { MoveTemp(ChartDataArray), Score, GetActorCountScoreDescription(Score.Score, TotalActorCount), { GetActorCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Actor_Category_Distribution", "Actor Category Distribution");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.ComponentMaxCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetComponentMaxCountScoreDescription = [&Settings](EScore ComponentMaxCountScore, int32 ComponentMaxCount)
			{
				if(ComponentMaxCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Child_Component_Max_Description", "アクターの持つコンポーネントの最大数が{0}個以内 ({1}n) に収まっています。"), Settings.ComponentMaxCountScoreSettings[ComponentMaxCountScore], ComponentMaxCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Child_Component_Max_Over_Description", "アクターの持つコンポーネントの最大数が{0}個をオーバー ({1}n) しています。"), Settings.ComponentMaxCountScoreSettings[EScore::D], ComponentMaxCount);
				}
			};
			auto GetComponentMaxCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Child_Component_Max_Details", "大量のコンポーネントが１つのアクターに登録されているとパフォーマンスに影響を及ぼす可能性があります。");
			};

			for(const auto& It : ComponentMaxCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = 0;
					StringArray.Emplace(FString::Printf(TEXT("%s: %dn"), *ChartData.Label, ChartData.Value));
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(MaxAllComponentMaxCount, Settings.ComponentMaxCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Child_Component_Max"), { MoveTemp(ChartDataArray), Score, GetComponentMaxCountScoreDescription(Score.Score, MaxAllComponentMaxCount), { GetComponentMaxCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Child_Component_Max", "Child Component Max");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.ComponentAverageCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetComponentAverageCountScoreDescription = [&Settings](EScore ComponentAverageCountScore, int32 ComponentAverageCount)
			{
				if(ComponentAverageCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Child_Component_Average_Description", "アクターの持つコンポーネントの平均数が{0}個以内 ({1}n) に収まっています。"), Settings.ComponentAverageCountScoreSettings[ComponentAverageCountScore], ComponentAverageCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Child_Component_Average_Over_Description", "アクターの持つコンポーネントの平均数が{0}個をオーバー ({1}n) しています。"), Settings.ComponentAverageCountScoreSettings[EScore::D], ComponentAverageCount);
				}
			};
			auto GetComponentAverageCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Child_Component_Average_Details", "大量のコンポーネントが１つのアクターに登録されているとパフォーマンスに影響を及ぼす可能性があります。");
			};

			int32 MaxComponentAverageCount = 0;
			for(const auto& It : ComponentCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = SafeDivide(It.Value, ActorCategoryCount[It.Key]);
					ChartData.TotalValue = 0;
					StringArray.Emplace(FString::Printf(TEXT("%s: %dn"), *ChartData.Label, ChartData.Value));
					MaxComponentAverageCount = FMath::Max(ChartData.Value, MaxComponentAverageCount);
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(MaxComponentAverageCount, Settings.ComponentAverageCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Child_Component_Average"), { MoveTemp(ChartDataArray), Score, GetComponentAverageCountScoreDescription(Score.Score, MaxComponentAverageCount), { GetComponentAverageCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Child_Component_Average", "Child Component Average");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.ActorTickRatioScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetActorTickRatioScoreDescription = [&Settings](EScore ActorTickRatioScore, int32 TotalActorTickCount, int32 TotalActorCount)
			{
				if(ActorTickRatioScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Actor_Tick_Count_Description", "Tick処理を行うアクターの数が{0}%以内 ({1}n / {2}n = {3}%) に収まっています。"), Settings.ActorTickRatioScoreSettings[ActorTickRatioScore], TotalActorTickCount, TotalActorCount, SafeDivideToPercentage<float>(TotalActorTickCount, TotalActorCount));
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Actor_Tick_Count_Over_Description", "Tick処理を行うアクターの数が{0}%をオーバー ({1}n / {2}n = {3}%) しています。"), Settings.ActorTickRatioScoreSettings[EScore::D], TotalActorTickCount, TotalActorCount, SafeDivideToPercentage<float>(TotalActorTickCount, TotalActorCount));
				}
			};
			auto GetActorTickRatioScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Actor_Tick_Count_Details", "シーンに存在するアクターのTickの数が多すぎると実行時のパフォーマンスに影響を及ぼす可能性があります。");
			};

			for(const auto& It : ActorTickCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = TotalActorCount;
					ChartData.TotalLabel = TEXT("Total Actor Ratio");
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(SafeDivideToPercentage<float>(TotalActorTickCount, TotalActorCount), Settings.ActorTickRatioScoreSettings));
				HealthCheckerReport.Add(TEXT("Actor_Tick_Count"), { MoveTemp(ChartDataArray), Score, GetActorTickRatioScoreDescription(Score.Score, TotalActorTickCount, TotalActorCount), { GetActorTickRatioScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Actor_Tick_Count", "Actor Tick Count");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.BlueprintRatioScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetBlueprintRatioScoreDescription = [&Settings](EScore BlueprintRatioScore, int32 TotalBlueprintCount, int32 TotalActorCount)
			{
				if(BlueprintRatioScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Blueprint_Ratio_Description", "ブループリント化されているアクターの数が{0}%以内 ({1}n / {2}n = {3}%) に収まっています。"), Settings.BlueprintRatioScoreSettings[BlueprintRatioScore], TotalBlueprintCount, TotalActorCount, SafeDivideToPercentage<float>(TotalBlueprintCount, TotalActorCount));
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Blueprint_Ratio_Over_Description", "ブループリント化されているアクターの数が{0}%をオーバー ({1}n / {2}n = {3}%) しています。"), Settings.BlueprintRatioScoreSettings[EScore::D], TotalBlueprintCount, TotalActorCount, SafeDivideToPercentage<float>(TotalBlueprintCount, TotalActorCount));
				}
			};
			auto GetBlueprintRatioScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Blueprint_Ratio_Details", "");
			};

			for(const auto& It : BlueprintCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = ActorCategoryCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(SafeDivideToPercentage<float>(TotalBlueprintCount, TotalActorCount), Settings.BlueprintRatioScoreSettings));
				HealthCheckerReport.Add(TEXT("Blueprint_Ratio"), { MoveTemp(ChartDataArray), Score, GetBlueprintRatioScoreDescription(Score.Score, TotalBlueprintCount, TotalActorCount), { GetBlueprintRatioScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Blueprint_Ratio", "Blueprint Ratio");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.StaticMeshActorSameMeshCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetStaticMeshActorSameMeshCountScoreDescription = [&Settings](EScore StaticMeshActorSameMeshCountScore, int32 StaticMeshActorSameMeshCount)
			{
				if(StaticMeshActorSameMeshCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("StaticMeshActor_Same_Mesh_Count_Description", "同じスタティックメッシュがアサインされているStaticMeshActorが{0}個以内 ({1}n) に収まっています。"), Settings.StaticMeshActorSameMeshCountScoreSettings[StaticMeshActorSameMeshCountScore], StaticMeshActorSameMeshCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("StaticMeshActor_Same_Mesh_Count_Over_Description", "同じスタティックメッシュがアサインされているStaticMeshActorが{0}個をオーバー ({1}n) しています。"), Settings.StaticMeshActorSameMeshCountScoreSettings[EScore::D], StaticMeshActorSameMeshCount);
				}
			};
			auto GetStaticMeshActorSameMeshCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("StaticMeshActor_Same_Mesh_Count_Details", "同じスタティックメッシュを持つStaticMeshActorはHierarchicalInstancedStaticMeshComponentなどのインスタンシング機能を使用して高速化が可能です。");
			};

			StaticMeshActorSameMeshCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			for(const auto& It : StaticMeshActorSameMeshCount)
			{
				if(IsValidCategory(EActorCategory::StaticMesh) && It.Value > 1)
				{
					if(StringArray.Num() < Settings.MaxDisplayStaticMeshActorSameMesh)
					{
						FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
						ChartData.Label = FPaths::GetExtension(It.Key.ToString());
						ChartData.Value = It.Value;
						ChartData.TotalValue = TotalStaticMeshActorCount;
						ChartData.TotalLabel = TEXT("Total StaticMeshActor Ratio");
						StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
					}
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalStaticMeshActorSameMeshCount, Settings.StaticMeshActorSameMeshCountScoreSettings));
				HealthCheckerReport.Add(TEXT("StaticMeshActor_Same_Mesh_Count"), { MoveTemp(ChartDataArray), Score, GetStaticMeshActorSameMeshCountScoreDescription(Score.Score, TotalStaticMeshActorSameMeshCount), { GetStaticMeshActorSameMeshCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("StaticMeshActor_Same_Mesh_Count", "StaticMeshActor Same Mesh Count");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: All: %.1f%%(%dn/%dn), %s"), *GraphName.ToString(), SafeDivideToPercentage<float>(TotalStaticMeshActorCount, TotalStaticMeshActorSameMeshCount), TotalStaticMeshActorCount, TotalStaticMeshActorSameMeshCount, *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.NeedsAttachParentBoundsCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetNeedsAttachParentBoundsCountScoreDescription = [&Settings](EScore NeedsAttachParentBoundsCountScore, int32 NeedsAttachParentBoundsCount)
			{
				if(NeedsAttachParentBoundsCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Needs_AttachParentBounds_Description", "AttachParentBoundsの設定が必要なコンポーネントが{0}個以内 ({1}n) に収まっています。"), Settings.NeedsAttachParentBoundsCountScoreSettings[NeedsAttachParentBoundsCountScore], NeedsAttachParentBoundsCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Needs_AttachParentBounds_Over_Description", "AttachParentBoundsの設定が必要なコンポーネントが{0}個をオーバー ({1}n) しています。"), Settings.NeedsAttachParentBoundsCountScoreSettings[EScore::D], NeedsAttachParentBoundsCount);
				}
			};
			auto GetNeedsAttachParentBoundsCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Needs_AttachParentBounds_Details", "AttachParentBoundsを設定してバウンスを親のコンポーネントとまとめることで高速化が可能です。");
			};

			for(const auto& It : NeedsAttachParentBoundsCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = SceneComponentCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalNeedsAttachParentBoundsCount = GetTotalCount(NeedsAttachParentBoundsCount);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalNeedsAttachParentBoundsCount, Settings.NeedsAttachParentBoundsCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Needs_AttachParentBounds"), { MoveTemp(ChartDataArray), Score, GetNeedsAttachParentBoundsCountScoreDescription(Score.Score, TotalNeedsAttachParentBoundsCount), { GetNeedsAttachParentBoundsCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Needs_AttachParentBounds", "Needs AttachParentBounds");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s (e.g. %s)"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")), *StringJoin(WarningAttachParentBoundsComponentNames, TEXT(", "), Settings.MaxDisplayNeedsAttachParentBounds));
			}
		}

		ProgressReport();

		if(Settings.NeedsAutoManageAttachmentCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetNeedsAutoManageAttachmentCountScoreDescription = [&Settings](EScore NeedsAutoManageAttachmentCountScore, int32 NeedsAutoManageAttachmentCount)
			{
				if(NeedsAutoManageAttachmentCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Needs_AutoManageAttachment_Description", "AutoManageAttachmentの設定が必要なコンポーネントが{0}個以内 ({1}n) に収まっています。"), Settings.NeedsAutoManageAttachmentCountScoreSettings[NeedsAutoManageAttachmentCountScore], NeedsAutoManageAttachmentCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Needs_AutoManageAttachment_Over_Description", "AutoManageAttachmentの設定が必要なコンポーネントが{0}個をオーバー ({1}n) しています。"), Settings.NeedsAutoManageAttachmentCountScoreSettings[EScore::D], NeedsAutoManageAttachmentCount);
				}
			};
			auto GetNeedsAutoManageAttachmentCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Needs_AutoManageAttachment_Details", "AutoManageAttachmentを使用することで親のコンポーネントと一体化し高速化が可能です。");
			};

			for(const auto& It : NeedsAutoManageAttachmentCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = SceneComponentCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalNeedsAutoManageAttachmentCount = GetTotalCount(NeedsAutoManageAttachmentCount);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalNeedsAutoManageAttachmentCount, Settings.NeedsAutoManageAttachmentCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Needs_AutoManageAttachment"), { MoveTemp(ChartDataArray), Score, GetNeedsAutoManageAttachmentCountScoreDescription(Score.Score, TotalNeedsAutoManageAttachmentCount), { GetNeedsAutoManageAttachmentCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Needs_AutoManageAttachment", "Needs AutoManageAttachment");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s (e.g. %s)"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")), *StringJoin(WarningAutoManageAttachmentComponentNames, TEXT(", "), Settings.MaxDisplayNeedsAutoManageAttachment));
			}
		}

		ProgressReport();

		if(Settings.NeedsMultipleAudioPlayModeCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetNeedsMultipleAudioPlayModeCountScoreDescription = [&Settings](EScore NeedsMultipleAudioPlayModeCountScore, int32 NeedsMultipleAudioPlayModeCount)
			{
				if(NeedsMultipleAudioPlayModeCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Needs_Multiple_AudioPlayMode_Description", "MultipleAudioPlayModeの設定が必要なコンポーネントが{0}個以内 ({1}n) に収まっています。"), Settings.NeedsMultipleAudioPlayModeCountScoreSettings[NeedsMultipleAudioPlayModeCountScore], NeedsMultipleAudioPlayModeCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Needs_Multiple_AudioPlayMode_Over_Description", "MultipleAudioPlayModeの設定が必要なコンポーネントが{0}個をオーバー ({1}n) しています。"), Settings.NeedsMultipleAudioPlayModeCountScoreSettings[EScore::D], NeedsMultipleAudioPlayModeCount);
				}
			};
			auto GetNeedsMultipleAudioPlayModeCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Needs_Multiple_AudioPlayMode_Details", "複数のオーディオを１つのコンポーネントで再生することで高速化が可能です。");
			};

			for(const auto& It : NeedsMultipleAudioPlayModeCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = AudioComponentCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalNeedsMultipleAudioPlayModeCount = GetTotalCount(NeedsMultipleAudioPlayModeCount);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalNeedsMultipleAudioPlayModeCount, Settings.NeedsMultipleAudioPlayModeCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Needs_Multiple_AudioPlayMode"), { MoveTemp(ChartDataArray), Score, GetNeedsMultipleAudioPlayModeCountScoreDescription(Score.Score, TotalNeedsMultipleAudioPlayModeCount), { GetNeedsMultipleAudioPlayModeCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Needs_Multiple_AudioPlayMode", "Needs Multiple AudioPlayMode");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s (e.g. %s)"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")), *StringJoin(WarningAudioPlayModeComponentNames, TEXT(", "), Settings.MaxDisplayNeedsAudioPlayMode));
			}
		}

		ProgressReport();

		if(Settings.SameMaterialsInMaterialSlotsCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetSameMaterialsInMaterialSlotsCountScoreDescription = [&Settings](EScore SameMaterialsInMaterialSlotsCountScore, int32 SameMaterialsInMaterialSlotsCount)
			{
				if(SameMaterialsInMaterialSlotsCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Same_Materials_In_Material_Slots_Description", "複数のマテリアルスロットに同じマテリアルが重複して存在するメッシュが{0}個以内 ({1}n) に収まっています。"), Settings.SameMaterialsInMaterialSlotsCountScoreSettings[SameMaterialsInMaterialSlotsCountScore], SameMaterialsInMaterialSlotsCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Same_Materials_In_Material_Slots_Over_Description", "複数のマテリアルスロットに同じマテリアルが重複して存在するメッシュが{0}個をオーバー ({1}n) しています。"), Settings.SameMaterialsInMaterialSlotsCountScoreSettings[EScore::D], SameMaterialsInMaterialSlotsCount);
				}
			};
			auto GetSameMaterialsInMaterialSlotsCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Same_Materials_In_Material_Slots_Details", "特別な理由がない限り同じマテリアルを使用するマテリアルスロットはマージが可能です。");
			};

			for(const auto& It : SameMaterialsInMaterialSlotsCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = MaterialCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalSameMaterialsInMaterialSlotsCount = GetTotalCount(SameMaterialsInMaterialSlotsCount);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalSameMaterialsInMaterialSlotsCount, Settings.SameMaterialsInMaterialSlotsCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Same_Materials_In_Material_Slots"), { MoveTemp(ChartDataArray), Score, GetSameMaterialsInMaterialSlotsCountScoreDescription(Score.Score, TotalSameMaterialsInMaterialSlotsCount), { GetSameMaterialsInMaterialSlotsCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Same_Materials_In_Material_Slots", "Same Materials in Material Slots");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s (e.g. %s)"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")), *StringJoin(SameMaterialsInMaterialSlotsComponentNames, TEXT(", "), Settings.MaxDisplaySameMaterialsInMaterialSlots));
			}
		}

		ProgressReport();

		if(Settings.MismatchNumOverrideMaterialCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetMismatchNumOverrideMaterialCountScoreDescription = [&Settings](EScore MismatchNumOverrideMaterialCountScore, int32 MismatchNumOverrideMaterialCount)
			{
				if(MismatchNumOverrideMaterialCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Mismatch_OverrideMaterial_Count_Description", "オーバーライドマテリアルの数が元のマテリアルの数と一致しないコンポーネントが{0}個以内 ({1}n) に収まっています。"), Settings.MismatchNumOverrideMaterialCountScoreSettings[MismatchNumOverrideMaterialCountScore], MismatchNumOverrideMaterialCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Mismatch_OverrideMaterial_Count_Over_Description", "オーバーライドマテリアルの数が元のマテリアルの数と一致しないコンポーネントが{0}個をオーバー ({1}n) しています。"), Settings.MismatchNumOverrideMaterialCountScoreSettings[EScore::D], MismatchNumOverrideMaterialCount);
				}
			};
			auto GetMismatchNumOverrideMaterialCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Mismatch_OverrideMaterial_Count_Details", "コンポーネントのオーバーライドマテリアルの数が元のマテリアルの数と一致していないため、不必要なマテリアルのロードが起きている可能性があります。");
			};

			for(const auto& It : MismatchNumOverrideMaterialCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = MaterialCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalMismatchNumOverrideMaterialCount = GetTotalCount(MismatchNumOverrideMaterialCount);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalMismatchNumOverrideMaterialCount, Settings.MismatchNumOverrideMaterialCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Mismatch_OverrideMaterial_Count"), { MoveTemp(ChartDataArray), Score, GetMismatchNumOverrideMaterialCountScoreDescription(Score.Score, TotalMismatchNumOverrideMaterialCount), { GetMismatchNumOverrideMaterialCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Mismatch_OverrideMaterial_Count", "Mismatch OverrideMaterial Count");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s (e.g. %s)"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")), *StringJoin(MismatchNumOverrideMaterialComponentNames, TEXT(", "), Settings.MaxDisplayMismatchNumOverrideMaterial));
			}
		}

		ProgressReport();

		if(Settings.MissingMaterialsCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetMissingMaterialsCountScoreDescription = [&Settings](EScore MissingMaterialsCountScore, int32 MissingMaterialsCount)
			{
				if(MissingMaterialsCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Missing_Components_Material_Description", "マテリアルがアサインされていないコンポーネントが{0}個以内 ({1}n) に収まっています。"), Settings.MissingMaterialsCountScoreSettings[MissingMaterialsCountScore], MissingMaterialsCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Missing_Components_Material_Over_Description", "マテリアルがアサインされていないコンポーネントが{0}個をオーバー ({1}n) しています。"), Settings.MissingMaterialsCountScoreSettings[EScore::D], MissingMaterialsCount);
				}
			};
			auto GetMissingMaterialsCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Missing_Components_Material_Details", "コンポーネントのマテリアルに空のマテリアルが存在します。メッシュのマテリアルやオーバーライドマテリアルに空のマテリアルが含まれていないか確認してください。");
			};

			for(const auto& It : MissingMaterialsCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = MeshComponentCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalMissingMaterialsCount = GetTotalCount(MissingMaterialsCount);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalMissingMaterialsCount, Settings.MissingMaterialsCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Missing_Components_Material"), { MoveTemp(ChartDataArray), Score, GetMissingMaterialsCountScoreDescription(Score.Score, TotalMissingMaterialsCount), { GetMissingMaterialsCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Missing_Components_Material", "Missing Components Material");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s (e.g. %s)"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")), *StringJoin(MissingMaterialsComponentNames, TEXT(", "), Settings.MaxDisplayMissingMaterials));
			}
		}

		ProgressReport();

		if(Settings.MissingMeshesCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetMissingMeshesCountScoreDescription = [&Settings](EScore MissingMeshesCountScore, int32 MissingMeshesCount)
			{
				if(MissingMeshesCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Missing_Components_Mesh_Description", "メッシュがアサインされていないコンポーネントが{0}個以内 ({1}n) に収まっています。"), Settings.MissingMeshesCountScoreSettings[MissingMeshesCountScore], MissingMeshesCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Missing_Components_Mesh_Over_Description", "メッシュがアサインされていないコンポーネントが{0}個をオーバー ({1}n) しています。"), Settings.MissingMeshesCountScoreSettings[EScore::D], MissingMeshesCount);
				}
			};
			auto GetMissingMeshesCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Missing_Components_Mesh_Details", "メッシュがアサインされていないため必要のないコンポーネントの可能性があります。");
			};

			for(const auto& It : MissingMeshesCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = MeshCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalMissingMeshesCount = GetTotalCount(MissingMeshesCount);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalMissingMeshesCount, Settings.MissingMeshesCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Missing_Components_Mesh"), { MoveTemp(ChartDataArray), Score, GetMissingMeshesCountScoreDescription(Score.Score, TotalMissingMeshesCount), { GetMissingMeshesCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Missing_Components_Mesh", "Missing Components Mesh");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s (e.g. %s)"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")), *StringJoin(MissingMeshesComponentNames, TEXT(", "), Settings.MaxDisplayMissingMeshes));
			}
		}

		ProgressReport();

		if(Settings.NoLodsMeshCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetNoLodsMeshCountScoreDescription = [&Settings](EScore NoLodsMeshCountScore, int32 NoLodsMeshCount)
			{
				if(NoLodsMeshCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("No_LODs_Meshes_Description", "LODが生成されていないメッシュが{0}個以内 ({1}n) に収まっています。"), Settings.NoLodsMeshCountScoreSettings[NoLodsMeshCountScore], NoLodsMeshCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("No_LODs_Meshes_Over_Description", "LODが生成されていないメッシュが{0}個をオーバー ({1}n) しています。"), Settings.NoLodsMeshCountScoreSettings[EScore::D], NoLodsMeshCount);
				}
			};
			auto GetNoLodsMeshCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("No_LODs_Meshes_Details", "LODを生成することでパフォーマンスが安定する可能性があります。");
			};

			for(const auto& It : NoLodsMeshCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = MeshCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalNoLodsMeshCount = GetTotalCount(NoLodsMeshCount);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalNoLodsMeshCount, Settings.NoLodsMeshCountScoreSettings));
				HealthCheckerReport.Add(TEXT("No_LODs_Meshes"), { MoveTemp(ChartDataArray), Score, GetNoLodsMeshCountScoreDescription(Score.Score, TotalNoLodsMeshCount), { GetNoLodsMeshCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("No_LODs_Meshes", "No LODs Meshes");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s (e.g. %s)"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")), *StringJoin(NoLodsMeshComponentNames, TEXT(", "), Settings.MaxDisplayNoLodsMeshes));
			}
		}

		ProgressReport();

		if(Settings.MissingComponentsCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetMissingComponentsCountScoreDescription = [&Settings](EScore MissingComponentsCountScore, int32 MissingComponentsCount)
			{
				if(MissingComponentsCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Missing_Actors_Component_Description", "コンポーネント配列に空のコンポーネントが存在するアクターが{0}個以内 ({1}n) に収まっています。"), Settings.MissingComponentsCountScoreSettings[MissingComponentsCountScore], MissingComponentsCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Missing_Actors_Component_Over_Description", "コンポーネント配列に空のコンポーネントが存在するアクターが{0}個をオーバー ({1}n) しています。"), Settings.MissingComponentsCountScoreSettings[EScore::D], MissingComponentsCount);
				}
			};
			auto GetMissingComponentsCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Missing_Actors_Component_Details", "コンポーネント配列に空のコンポーネントが存在するアクターが存在します。内部データを正しく保つためにBPのリペアレントを推奨します。");
			};

			for(const auto& It : MissingComponentsCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = ActorCategoryCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalMissingComponentsCount = GetTotalCount(MissingComponentsCount);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalMissingComponentsCount, Settings.MissingComponentsCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Missing_Actors_Component"), { MoveTemp(ChartDataArray), Score, GetMissingComponentsCountScoreDescription(Score.Score, TotalMissingComponentsCount), { GetMissingComponentsCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Missing_Actors_Component", "Missing Actors Component");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s (e.g. %s)"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")), *StringJoin(MissingComponentsActorNames, TEXT(", "), Settings.MaxDisplayMissingComponents));
			}
		}

		ProgressReport();

		if(FPlatformMisc::IsDebuggerPresent())
		{

		// StaticMesh
		(void)HC4UE_LOCTEXT("StaticMesh_Vertex_Ranking_Description", "スタティックメッシュの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("StaticMesh_Vertex_Ranking_Range_Description", "スタティックメッシュの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("StaticMesh_Vertex_Ranking_Over_Description", "スタティックメッシュの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("StaticMesh_Vertex_Ranking_Details", "メッシュの頂点数が多すぎるとロード時間やGPUに影響を及ぼします。");
		(void)HC4UE_LOCTEXT("StaticMesh_Vertex_Ranking", "StaticMesh Vertex Ranking");

		(void)HC4UE_LOCTEXT("StaticMesh_Hard_Edge_Vertex_Ranking_Description", "スタティックメッシュのハードエッジの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("StaticMesh_Hard_Edge_Vertex_Ranking_Range_Description", "スタティックメッシュのハードエッジの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("StaticMesh_Hard_Edge_Vertex_Ranking_Over_Description", "スタティックメッシュのハードエッジの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("StaticMesh_Hard_Edge_Vertex_Ranking_Details", "共有頂点の割合を上げることで頂点キャッシュが効きやすくなりGPUの高速化が可能です。");
		(void)HC4UE_LOCTEXT("StaticMesh_Hard_Edge_Vertex_Ranking", "StaticMesh Hard Edge Vertex Ranking");

		(void)HC4UE_LOCTEXT("StaticMesh_Nanite_Vertex_Ranking_Description", "Nanite化されているスタティックメッシュの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("StaticMesh_Nanite_Vertex_Ranking_Range_Description", "Nanite化されているスタティックメッシュの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("StaticMesh_Nanite_Vertex_Ranking_Over_Description", "Nanite化されているスタティックメッシュの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("StaticMesh_Nanite_Vertex_Ranking_Details", "Nanite化されているメッシュの頂点数が多すぎると実行時のリソース消費量に影響を及ぼします。");
		(void)HC4UE_LOCTEXT("StaticMesh_Nanite_Vertex_Ranking", "StaticMesh Nanite Vertex Ranking");

		(void)HC4UE_LOCTEXT("StaticMesh_Nanite_Hard_Edge_Vertex_Ranking_Description", "Nanite化されているスタティックメッシュのハードエッジの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("StaticMesh_Nanite_Hard_Edge_Vertex_Ranking_Range_Description", "Nanite化されているスタティックメッシュのハードエッジの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("StaticMesh_Nanite_Hard_Edge_Vertex_Ranking_Over_Description", "Nanite化されているスタティックメッシュのハードエッジの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("StaticMesh_Nanite_Hard_Edge_Vertex_Ranking_Details", "Nanite化されているメッシュの頂点数が多すぎると実行時のリソース消費量に影響を及ぼします。");
		(void)HC4UE_LOCTEXT("StaticMesh_Nanite_Hard_Edge_Vertex_Ranking", "StaticMesh Nanite Hard Edge Vertex Ranking");

		// SkeletalMesh
		(void)HC4UE_LOCTEXT("SkeletalMesh_Vertex_Ranking_Description", "スケルタルメッシュの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Vertex_Ranking_Range_Description", "スケルタルメッシュの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Vertex_Ranking_Over_Description", "スケルタルメッシュの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Vertex_Ranking_Details", "メッシュの頂点数が多すぎるとロード時間やGPUに影響を及ぼします。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Vertex_Ranking", "SkeletalMesh Vertex Ranking");

		(void)HC4UE_LOCTEXT("SkeletalMesh_Hard_Edge_Vertex_Ranking_Description", "スケルタルメッシュのハードエッジの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Hard_Edge_Vertex_Ranking_Range_Description", "スケルタルメッシュのハードエッジの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Hard_Edge_Vertex_Ranking_Over_Description", "スケルタルメッシュのハードエッジの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Hard_Edge_Vertex_Ranking_Details", "共有頂点の割合を上げることで頂点キャッシュが効きやすくなりGPUの高速化が可能です。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Hard_Edge_Vertex_Ranking", "SkeletalMesh Hard Edge Vertex Ranking");

		(void)HC4UE_LOCTEXT("SkeletalMesh_Nanite_Vertex_Ranking_Description", "Nanite化されているスケルタルメッシュの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Nanite_Vertex_Ranking_Range_Description", "Nanite化されているスケルタルメッシュの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Nanite_Vertex_Ranking_Over_Description", "Nanite化されているスケルタルメッシュの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Nanite_Vertex_Ranking_Details", "Nanite化されているメッシュの頂点数が多すぎると実行時のリソース消費量に影響を及ぼします。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Nanite_Vertex_Ranking", "SkeletalMesh Nanite Vertex Ranking");

		(void)HC4UE_LOCTEXT("SkeletalMesh_Nanite_Hard_Edge_Vertex_Ranking_Description", "Nanite化されているスケルタルメッシュのハードエッジの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Nanite_Hard_Edge_Vertex_Ranking_Range_Description", "Nanite化されているスケルタルメッシュのハードエッジの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Nanite_Hard_Edge_Vertex_Ranking_Over_Description", "Nanite化されているスケルタルメッシュのハードエッジの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Nanite_Hard_Edge_Vertex_Ranking_Details", "Nanite化されているメッシュの頂点数が多すぎると実行時のリソース消費量に影響を及ぼします。");
		(void)HC4UE_LOCTEXT("SkeletalMesh_Nanite_Hard_Edge_Vertex_Ranking", "SkeletalMesh Nanite Hard Edge Vertex Ranking");

		// ParticleMesh
		(void)HC4UE_LOCTEXT("ParticleMesh_Vertex_Ranking_Description", "パーティクルメッシュの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Vertex_Ranking_Range_Description", "パーティクルメッシュの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Vertex_Ranking_Over_Description", "パーティクルメッシュの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Vertex_Ranking_Details", "メッシュの頂点数が多すぎるとロード時間やGPUに影響を及ぼします。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Vertex_Ranking", "ParticleMesh Vertex Ranking");

		(void)HC4UE_LOCTEXT("ParticleMesh_Hard_Edge_Vertex_Ranking_Description", "パーティクルメッシュのハードエッジの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Hard_Edge_Vertex_Ranking_Range_Description", "パーティクルメッシュのハードエッジの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Hard_Edge_Vertex_Ranking_Over_Description", "パーティクルメッシュのハードエッジの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Hard_Edge_Vertex_Ranking_Details", "共有頂点の割合を上げることで頂点キャッシュが効きやすくなりGPUの高速化が可能です。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Hard_Edge_Vertex_Ranking", "ParticleMesh Hard Edge Vertex Ranking");

		(void)HC4UE_LOCTEXT("ParticleMesh_Nanite_Vertex_Ranking_Description", "Nanite化されているパーティクルメッシュの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Nanite_Vertex_Ranking_Range_Description", "Nanite化されているパーティクルメッシュの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Nanite_Vertex_Ranking_Over_Description", "Nanite化されているパーティクルメッシュの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Nanite_Vertex_Ranking_Details", "Nanite化されているメッシュの頂点数が多すぎると実行時のリソース消費量に影響を及ぼします。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Nanite_Vertex_Ranking", "ParticleMesh Nanite Vertex Ranking");

		(void)HC4UE_LOCTEXT("ParticleMesh_Nanite_Hard_Edge_Vertex_Ranking_Description", "Nanite化されているパーティクルメッシュのハードエッジの頂点数が全て{0}頂点以内に収まっています。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Nanite_Hard_Edge_Vertex_Ranking_Range_Description", "Nanite化されているパーティクルメッシュのハードエッジの頂点数が{0}頂点より多く{1}頂点以内のものが{2}個存在します。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Nanite_Hard_Edge_Vertex_Ranking_Over_Description", "Nanite化されているパーティクルメッシュのハードエッジの頂点数が{0}頂点より多いもの{1}個存在します。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Nanite_Hard_Edge_Vertex_Ranking_Details", "Nanite化されているメッシュの頂点数が多すぎると実行時のリソース消費量に影響を及ぼします。");
		(void)HC4UE_LOCTEXT("ParticleMesh_Nanite_Hard_Edge_Vertex_Ranking", "ParticleMesh Nanite Hard Edge Vertex Ranking");

		}

		auto ReportVertexRanking = [&StringArray, &ChartDataArray, &AllScoreArray, &HealthCheckerReport](const TCHAR* VertexRankingLocKey, TMap<FName, int32>& VertexCount, const FIntScoreSettings& VertexCountScoreSettings, int32 MaxDisplayVertexRanking)
		{
			if(!VertexCountScoreSettings.bAllowHealthCheck)
			{
				return;
			}

			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetScoreDescription = [&VertexRankingLocKey, &VertexCountScoreSettings](EScore Score, int32 ScoreCount)
			{
				if(Score == EScore::A)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_GET_LOCTEXT_FORMAT("%s_Description", VertexRankingLocKey), VertexCountScoreSettings[Score]);
				}
				else
				if(Score <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_GET_LOCTEXT_FORMAT("%s_Range_Description", VertexRankingLocKey), VertexCountScoreSettings[GetBeforeScore(Score)], VertexCountScoreSettings[Score], ScoreCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_GET_LOCTEXT_FORMAT("%s_Over_Description", VertexRankingLocKey), VertexCountScoreSettings[EScore::D], ScoreCount);
				}
			};
			auto GetScoreDetails = [&VertexRankingLocKey]()
			{
				return HC4UE_GET_LOCTEXT_FORMAT("%s_Details", VertexRankingLocKey);
			};

			TArray<FScore> ScoreArray;
			for(const auto& It : VertexCount)
			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = FPaths::GetExtension(It.Key.ToString());
				ChartData.Value = It.Value;
				ChartData.TotalValue = 0;
				ChartData.Unit = TEXT("vtx");
				StringArray.Emplace(FString::Printf(TEXT("%s: %d%s"), *ChartData.Label, It.Value, *ChartData.Unit));
				ScoreArray.Emplace(GetScore(It.Value, VertexCountScoreSettings));
			}
			if(StringArray.Num() > 0)
			{
				FScore WorstScore;
				for(int32 i = ((int32)EScore::MAX - 1); i >= 0; --i)
				{
					if(ScoreArray.RemoveAll([&i](const FScore& Score){ return Score.Score == (EScore)i; }) > 0)
					{
						WorstScore = { (EScore)i, VertexCountScoreSettings.ScoreWeight, VertexCountScoreSettings.bAllowHealthCheck };
						break;
					}
				}
				const FScore& Score = AllScoreArray.Emplace_GetRef(WorstScore);
				HealthCheckerReport.Add(VertexRankingLocKey, { MoveTemp(ChartDataArray), Score, GetScoreDescription(Score.Score, ScoreArray.Num()), { GetScoreDetails() } });

				FText GraphName = HC4UE_GET_LOCTEXT_VAR(VertexRankingLocKey);
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", "), MaxDisplayVertexRanking));
			}
		};

		{
			StaticMeshVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("StaticMesh_Vertex_Ranking"), StaticMeshVertexCount, Settings.StaticMeshCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		{
			StaticMeshHardEdgeVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("StaticMesh_Hard_Edge_Vertex_Ranking"), StaticMeshHardEdgeVertexCount, Settings.StaticMeshHardEdgeVertexCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		{
			StaticMeshNaniteVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("StaticMesh_Nanite_Vertex_Ranking"), StaticMeshNaniteVertexCount, Settings.StaticMeshNaniteCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		{
			StaticMeshNaniteHardEdgeVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("StaticMesh_Nanite_Hard_Edge_Vertex_Ranking"), StaticMeshNaniteHardEdgeVertexCount, Settings.StaticMeshNaniteHardEdgeVertexCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		{
			SkeletalMeshVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("SkeletalMesh_Vertex_Ranking"), SkeletalMeshVertexCount, Settings.SkeletalMeshCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		{
			SkeletalMeshHardEdgeVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("SkeletalMesh_Hard_Edge_Vertex_Ranking"), SkeletalMeshHardEdgeVertexCount, Settings.SkeletalMeshHardEdgeVertexCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		{
			SkeletalMeshNaniteVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("SkeletalMesh_Nanite_Vertex_Ranking"), SkeletalMeshNaniteVertexCount, Settings.SkeletalMeshNaniteCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		{
			SkeletalMeshNaniteHardEdgeVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("SkeletalMesh_Nanite_Hard_Edge_Vertex_Ranking"), SkeletalMeshNaniteHardEdgeVertexCount, Settings.SkeletalMeshNaniteHardEdgeVertexCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		if(Settings.BoneCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetBoneCountScoreDescription = [&Settings](EScore BoneCountScore, int32 MaxBoneCount)
			{
				if(BoneCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Bone_Count_Ranking_Description", "スケルタルメッシュのボーンの数が{0}本以内 ({1}n) に収まっています。"), Settings.BoneCountScoreSettings[BoneCountScore], MaxBoneCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Bone_Count_Ranking_Over_Description", "スケルタルメッシュのボーンの数が{0}本をオーバー ({1}n) しています。"), Settings.BoneCountScoreSettings[EScore::D], MaxBoneCount);
				}
			};
			auto GetBoneCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Bone_Count_Ranking_Details", "スケルタルメッシュのボーンの数が多すぎるとGPUとCPU負荷が高くなるので注意が必要です。");
			};

			SkeletalMeshBoneCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			for(const auto& It : SkeletalMeshBoneCount)
			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = FPaths::GetExtension(It.Key.ToString());
				ChartData.Value = It.Value;
				ChartData.TotalValue = 0;
				StringArray.Emplace(FString::Printf(TEXT("%s: %d%s"), *ChartData.Label, It.Value, *ChartData.Unit));
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(MaxSkeletalMeshBoneCount, Settings.BoneCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Bone_Count_Ranking"), { MoveTemp(ChartDataArray), Score, GetBoneCountScoreDescription(Score.Score, MaxSkeletalMeshBoneCount), { GetBoneCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Bone_Count_Ranking", "Bone Count Ranking");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", "), Settings.MaxDisplayBoneCountRanking));
			}
		}

		ProgressReport();

		if(Settings.BoneReductionRateScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetBoneReductionRateScoreDescription = [&Settings](EScore BoneReductionRateScore, float BoneReductionRate)
			{
				if(BoneReductionRateScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("LOD_Bone_Reduction_Description", "スケルタルメッシュのボーンLODの割合が{0}%以下 ({1}%) に収まっています。"), Settings.BoneReductionRateScoreSettings[BoneReductionRateScore], BoneReductionRate);
				}
				else
				if(BoneReductionRate < 100.f)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("LOD_Bone_Reduction_Over_Description", "スケルタルメッシュのボーンLODの割合が{0}%をオーバー ({1}%) しています。"), Settings.BoneReductionRateScoreSettings[EScore::D], BoneReductionRate);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("LOD_Bone_Reduction_Unused_Description", "スケルタルメッシュのボーンLODが使用されていません。"));
				}
			};
			auto GetBoneReductionRateScoreDetails = []()
			{
				return HC4UE_LOCTEXT("LOD_Bone_Reduction_Details", "スケルタルメッシュのボーンLODを設定することでCPUとGPUの高速化が可能です。");
			};

			SkeletalMeshBoneReductionRate.ValueSort([](const float& A, const float& B){ return A >= B; });
			for(const auto& It : SkeletalMeshBoneReductionRate)
			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				FString Label = FPaths::GetExtension(It.Key.ToString());
				ChartData.Label = FString::Printf(TEXT("%s (%d / %d)"), *Label, SkeletalMeshLowestLodBoneCount[It.Key], SkeletalMeshBoneCount[It.Key]);
				ChartData.Value = It.Value;
				ChartData.Unit = TEXT("%");
				ChartData.TotalValue = 0;
				StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%s(%dn/%dn)"), *Label, It.Value, *ChartData.Unit, SkeletalMeshLowestLodBoneCount[It.Key], SkeletalMeshBoneCount[It.Key]));
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(MaxSkeletalMeshBoneReductionRate, Settings.BoneReductionRateScoreSettings));
				HealthCheckerReport.Add(TEXT("LOD_Bone_Reduction"), { MoveTemp(ChartDataArray), Score, GetBoneReductionRateScoreDescription(Score.Score, MaxSkeletalMeshBoneReductionRate), { GetBoneReductionRateScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("LOD_Bone_Reduction", "LOD Bone Reduction");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", "), Settings.MaxDisplayBoneReductionRateRanking));
			}
		}

		ProgressReport();

		{
			ParticleMeshVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("ParticleMesh_Vertex_Ranking"), ParticleMeshVertexCount, Settings.ParticleMeshCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		{
			ParticleMeshHardEdgeVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("ParticleMesh_Hard_Edge_Vertex_Ranking"), ParticleMeshHardEdgeVertexCount, Settings.ParticleMeshHardEdgeVertexCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		{
			ParticleMeshNaniteVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("ParticleMesh_Nanite_Vertex_Ranking"), ParticleMeshNaniteVertexCount, Settings.ParticleMeshNaniteCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		{
			ParticleMeshNaniteHardEdgeVertexCount.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			ReportVertexRanking(TEXT("ParticleMesh_Nanite_Hard_Edge_Vertex_Ranking"), ParticleMeshNaniteHardEdgeVertexCount, Settings.ParticleMeshNaniteHardEdgeVertexCountScoreSettings, Settings.MaxDisplayVertexRanking);
		}

		ProgressReport();

		if(NiagaraStatefulEmitterCount > 0 && Settings.NiagaraStatefulEmitterRatioScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetNiagaraStatefulEmitterRatioScoreDescription = [&Settings](EScore NiagaraStatefulEmitterRatioScore, int32 NiagaraStatefulEmitterCount, int32 TotalNiagaraEmitterCount)
			{
				if(NiagaraStatefulEmitterRatioScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Niagara_Stateful_Emitter_Description", "NiagaraのStatefulエミッターの数が{0}%以内 ({1}n / {2}n = {3}%) に収まっています。"), Settings.NiagaraStatefulEmitterRatioScoreSettings[NiagaraStatefulEmitterRatioScore], NiagaraStatefulEmitterCount, TotalNiagaraEmitterCount, SafeDivideToPercentage<float>(NiagaraStatefulEmitterCount, TotalNiagaraEmitterCount));
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Niagara_Stateful_Emitter_Over_Description", "NiagaraのStatefulエミッターの数が{0}%をオーバー ({1}n / {2}n = {3}%) しています。"), Settings.NiagaraStatefulEmitterRatioScoreSettings[EScore::D], NiagaraStatefulEmitterCount, TotalNiagaraEmitterCount, SafeDivideToPercentage<float>(NiagaraStatefulEmitterCount, TotalNiagaraEmitterCount));
				}
			};
			auto GetNiagaraStatefulEmitterRatioScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Niagara_Stateful_Emitter_Details", "NiagaraのStateless化を行うことで高速化が可能です。");
			};

			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = TEXT("Stateful Emitter");
				ChartData.Value = NiagaraStatefulEmitterCount - NiagaraCloseToStatelessEmitterCount;
				ChartData.TotalValue = TotalNiagaraEmitterCount;
				ChartData.TotalLabel = FString::Printf(TEXT("Total %s Ratio"), *ChartData.Label);
				StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
			}
			if(NiagaraCloseToStatelessEmitterCount > 0)
			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = TEXT("Stateful Emitter (Close to Stateless)");
				ChartData.Value = NiagaraCloseToStatelessEmitterCount;
				ChartData.TotalValue = TotalNiagaraEmitterCount;
				ChartData.TotalLabel = FString::Printf(TEXT("Total %s Ratio"), *ChartData.Label);
				StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
			}
			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = TEXT("Stateless Emitter");
				ChartData.Value = TotalNiagaraEmitterCount - NiagaraStatefulEmitterCount;
				ChartData.TotalValue = TotalNiagaraEmitterCount;
				ChartData.TotalLabel = FString::Printf(TEXT("Total %s Ratio"), *ChartData.Label);
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(SafeDivideToPercentage<float>(NiagaraStatefulEmitterCount, TotalNiagaraEmitterCount), Settings.NiagaraStatefulEmitterRatioScoreSettings));
				HealthCheckerReport.Add(TEXT("Niagara_Stateless_Emitter"), { MoveTemp(ChartDataArray), Score, GetNiagaraStatefulEmitterRatioScoreDescription(Score.Score, NiagaraStatefulEmitterCount, TotalNiagaraEmitterCount), { GetNiagaraStatefulEmitterRatioScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Niagara_Stateless_Emitter", "Niagara Stateless Emitter");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringArray[0]);
			}
		}

		ProgressReport();

		if(NiagaraEmitterOptimizationHints.Num() > 0 && Settings.NiagaraEmitterOptimizationHintsScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();
			NiagaraEmitterOptimizationHints.ValueSort([](const TArray<FName>& A, const TArray<FName>& B){ return A.Num() >= B.Num(); });

			auto GetNiagaraEmitterOptimizationHintsScoreDescription = [&Settings](EScore NiagaraEmitterOptimizationHintsScore, int32 WorstNiagaraEmitterCount, int32 TotalNiagaraEmitterCount)
			{
				if(NiagaraEmitterOptimizationHintsScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_Description", "Niagaraエミッターの最適化の余地の数が{0}%以内 ({1}n / {2}n = {3}%) に収まっています。"), Settings.NiagaraEmitterOptimizationHintsScoreSettings[NiagaraEmitterOptimizationHintsScore], WorstNiagaraEmitterCount, TotalNiagaraEmitterCount, SafeDivideToPercentage<float>(WorstNiagaraEmitterCount, TotalNiagaraEmitterCount));
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_Over_Description", "Niagaraエミッターの最適化の余地の数が{0}%をオーバー ({1}n / {2}n = {3}%) しています。"), Settings.NiagaraEmitterOptimizationHintsScoreSettings[EScore::D], WorstNiagaraEmitterCount, TotalNiagaraEmitterCount, SafeDivideToPercentage<float>(WorstNiagaraEmitterCount, TotalNiagaraEmitterCount));
				}
			};
			auto GetNiagaraEmitterOptimizationHintsScoreDetailsArray = [&NiagaraEmitterOptimizationHints, &Settings]()
			{
				auto GetNiagaraEmitterOptimizationHintsScoreDetails = [&](ENiagaraEmitterFlag NiagaraEmitterFlag)
				{
					switch(NiagaraEmitterFlag)
					{
					case ENiagaraEmitterFlag::A_LifeCycleIsSelf:
						return HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_A_Details", "(A) Emitter StateがSelfのためエミッターごとのループ制御が行われています。必要ない場合はSystemに変更して下さい。");
					case ENiagaraEmitterFlag::B_NeedsSpriteCutout:
						return HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_B_Details", "(B) 半透明のSprite RendererにCutoutTextureが設定されていません。複数のパーティクルが重なり合う場合、CutoutTextureでポリゴンを変形させることでオーバードローが減り高速化が可能です。");
					case ENiagaraEmitterFlag::C_NeedsEmitterSourceMode:
						return HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_C_Details", "(C) パーティクルが常に1つなら、Source ModeをEmitterに変更することで粒子配列生成や更新処理を省略でき、描画負荷を軽減できます。");
					case ENiagaraEmitterFlag::D_ManyRenderer:
						return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_D_Details", "(D) NiagaraSystemのRendererの数が{0}個を超えているためGPUやメモリ負荷に影響が出る可能性があります。"), Settings.WarningNiagaraRendererCount);
					case ENiagaraEmitterFlag::E_SkeletalMeshSampling:
						return HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_E_Details", "(E) Mesh RendererでSkeletalMeshのサンプリング描画が行われています。このNiagaraの描画コストが高くなるため注意が必要です。");
					case ENiagaraEmitterFlag::F_MeshRendererWithDistanceFieldMesh:
						return HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_F_Details", "(F) Mesh RendererでDistanceFieldがONのメッシュが使用されています。このNiagaraの描画コストが高くなるため注意が必要です。");
					case ENiagaraEmitterFlag::G_MeshRendererWithCollisionMesh:
						return HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_G_Details", "(G) Mesh Rendererでコリジョンを持つメッシュが使用されています。NiagaraのMeshパーティクルではStaticMeshのコリジョンを使用しないので削除が可能です。");
					case ENiagaraEmitterFlag::H_MeshRendererWithMultiUVMesh:
						return HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_H_Details", "(H) Mesh Rendererで複数のUVを持つメッシュが使用されています。エフェクト用のモデルで複数のUVを使用するケースは少ないので、無駄なUVが含まれていないか確認して下さい。");
					case ENiagaraEmitterFlag::I_LargeVolumeTexture:
						return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints_I_Details", "(I) Mesh RendererでVolumeTextureのサイズが{0}x{0}x{0}を超えているテクスチャが存在します。このNiagaraの描画コストが高くなるため注意が必要です。"), Settings.WarningNiagaraVolumeTextureSize);
					default: ensure(false); return FText();
					}
				};

				TArray<FText> DetailsArray;
				for(auto It : NiagaraEmitterOptimizationHints)
				{
					DetailsArray.Emplace(GetNiagaraEmitterOptimizationHintsScoreDetails(It.Key));
				}
				return DetailsArray;
			};

			int32 WorstNiagaraEmitterCount = 0;
			for(const auto& It : NiagaraEmitterOptimizationHints)
			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = GetNiagaraEmitterFlagName(It.Key);
				ChartData.Value = It.Value.Num();
				ChartData.TotalValue = TotalNiagaraEmitterCount;
				ChartData.TotalLabel = FString::Printf(TEXT("%s Ratio"), *ChartData.Label);
				StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				if(WorstNiagaraEmitterCount == 0)
				{
					WorstNiagaraEmitterCount = It.Value.Num();
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(SafeDivideToPercentage<float>(WorstNiagaraEmitterCount, TotalNiagaraEmitterCount), Settings.NiagaraEmitterOptimizationHintsScoreSettings));
				HealthCheckerReport.Add(TEXT("Niagara_Emitter_Optimization_Hints"), { MoveTemp(ChartDataArray), Score, GetNiagaraEmitterOptimizationHintsScoreDescription(Score.Score, WorstNiagaraEmitterCount, TotalNiagaraEmitterCount), GetNiagaraEmitterOptimizationHintsScoreDetailsArray() });

				FText GraphName = HC4UE_LOCTEXT("Niagara_Emitter_Optimization_Hints", "Niagara Emitter Optimization Hints");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(NiagaraSystemOptimizationHints.Num() > 0 && Settings.NiagaraSystemOptimizationHintsScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();
			NiagaraSystemOptimizationHints.ValueSort([](const TArray<FName>& A, const TArray<FName>& B){ return A.Num() >= B.Num(); });

			auto GetNiagaraSystemOptimizationHintsScoreDescription = [&Settings](EScore NiagaraSystemOptimizationHintsScore, int32 WorstNiagaraSystemCount, int32 TotalNiagaraSystemCount)
			{
				if(NiagaraSystemOptimizationHintsScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Niagara_System_Optimization_Hints_Description", "NiagaraSystemの最適化の余地の数が{0}%以内 ({1}n / {2}n = {3}%) に収まっています。"), Settings.NiagaraSystemOptimizationHintsScoreSettings[NiagaraSystemOptimizationHintsScore], WorstNiagaraSystemCount, TotalNiagaraSystemCount, SafeDivideToPercentage<float>(WorstNiagaraSystemCount, TotalNiagaraSystemCount));
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Niagara_System_Optimization_Hints_Over_Description", "NiagaraSystemの最適化の余地の数が{0}%をオーバー ({1}n / {2}n = {3}%) しています。"), Settings.NiagaraSystemOptimizationHintsScoreSettings[EScore::D], WorstNiagaraSystemCount, TotalNiagaraSystemCount, SafeDivideToPercentage<float>(WorstNiagaraSystemCount, TotalNiagaraSystemCount));
				}
			};
			auto GetNiagaraSystemOptimizationHintsScoreDetailsArray = [&NiagaraSystemOptimizationHints, &Settings]()
			{
				auto GetNiagaraSystemOptimizationHintsScoreDetails = [&](ENiagaraSystemFlag NiagaraSystemFlag)
				{
					switch(NiagaraSystemFlag)
					{
					case ENiagaraSystemFlag::A_NoValidation:
						return HC4UE_LOCTEXT("Niagara_System_Optimization_Hints_A_Details", "(A) Niagara Editor Validation RuleSetが設定されていないため、NiagaraSystemの整合性のチェックが行われていません。");
					case ENiagaraSystemFlag::B_MissingEffectType:
						return HC4UE_LOCTEXT("Niagara_System_Optimization_Hints_B_Details", "(B) NiagaraSystemにEffectTypeが設定されていないため、Validationやスケーラビリティ制御が制御されていません。");
					case ENiagaraSystemFlag::C_NotFixedBounds:
						return HC4UE_LOCTEXT("Niagara_System_Optimization_Hints_C_Details", "(C) NiagaraSystemのbFixedBoundsがオフのため毎フレームBoundsが再計算されています。");
					case ENiagaraSystemFlag::D_LongWarmupTime:
						return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Niagara_System_Optimization_Hints_D_Details", "(D) NiagaraSystemのWarmupTimeの時間が{0}秒を超えているため、Niagara起動時に大量のシミュレーションを行ってしまいます。"), Settings.WarningNiagaraWarmupTime);
					case ENiagaraSystemFlag::E_MultipleLightRenderers:
						return HC4UE_LOCTEXT("Niagara_System_Optimization_Hints_E_Details", "(E) １つのNiagaraエミッター内に複数のLight Rendererが存在しています。重複ライトは描画負荷への影響が大きいので、間違って設定されていないか確認して下さい。");
					default: ensure(false); return FText();
					}
				};

				TArray<FText> DetailsArray;
				for(auto It : NiagaraSystemOptimizationHints)
				{
					DetailsArray.Emplace(GetNiagaraSystemOptimizationHintsScoreDetails(It.Key));
				}
				return DetailsArray;
			};

			int32 WorstNiagaraSystemCount = 0;
			for(const auto& It : NiagaraSystemOptimizationHints)
			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = GetNiagaraSystemFlagName(It.Key);
				ChartData.Value = It.Value.Num();
				ChartData.TotalValue = TotalNiagaraSystemCount;
				ChartData.TotalLabel = FString::Printf(TEXT("%s Ratio"), *ChartData.Label);
				StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				if(WorstNiagaraSystemCount == 0)
				{
					WorstNiagaraSystemCount = It.Value.Num();
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(SafeDivideToPercentage<float>(WorstNiagaraSystemCount, TotalNiagaraSystemCount), Settings.NiagaraSystemOptimizationHintsScoreSettings));
				HealthCheckerReport.Add(TEXT("Niagara_System_Optimization_Hints"), { MoveTemp(ChartDataArray), Score, GetNiagaraSystemOptimizationHintsScoreDescription(Score.Score, WorstNiagaraSystemCount, TotalNiagaraSystemCount), GetNiagaraSystemOptimizationHintsScoreDetailsArray() });

				FText GraphName = HC4UE_LOCTEXT("Niagara_System_Optimization_Hints", "Niagara System Optimization Hints");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.TranslucentMaterialRatioScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetTranslucentMaterialRatioScoreDescription = [&Settings](EScore TranslucentMaterialRatioScore, int32 TotalTranslucentMaterialCount, int32 TotalMaterialCount)
			{
				if(TranslucentMaterialRatioScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Material_Distribution_Description", "半透明のマテリアルの数が{0}%以内 ({1}n / {2}n = {3}%) に収まっています。"), Settings.TranslucentMaterialRatioScoreSettings[TranslucentMaterialRatioScore], TotalTranslucentMaterialCount, TotalMaterialCount, SafeDivideToPercentage<float>(TotalTranslucentMaterialCount, TotalMaterialCount));
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Material_Distribution_Over_Description", "半透明のマテリアルの数が{0}%をオーバー ({1}n / {2}n = {3}%) しています。"), Settings.TranslucentMaterialRatioScoreSettings[EScore::D], TotalTranslucentMaterialCount, TotalMaterialCount, TotalMaterialCount, SafeDivideToPercentage<float>(TotalTranslucentMaterialCount, TotalMaterialCount));
				}
			};
			auto GetTranslucentMaterialRatioScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Material_Distribution_Details", "半透明のマテリアルの数が多すぎるとGPUのパフォーマンスに問題が出やすいので注意が必要です。");
			};

			int32 TotalMaterialCount = 0;
			int32 TotalTranslucentMaterialCount = 0;
			for(const auto& It : MaterialBlendMode)
			{
				if(IsValidCategory(It.Key))
				{
					int32 TotalCategoryMaterialCount = 0;
					for(const int32& Count : It.Value)
					{
						TotalMaterialCount += Count;
						TotalCategoryMaterialCount += Count;
					}

					StringArray2.Reset();
					for(int32 i = 0; i < (int32)EMaterialBlendMode::MAX; ++i)
					{
						if(It.Value.IsValidIndex(i) && It.Value[i] > 0)
						{
							FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
							ChartData.Label = FString::Printf(TEXT("%s (%s)"), *GetActorCategoryName(It.Key), *GetMaterialBlendModeName((EMaterialBlendMode)i));
							ChartData.Value = It.Value[i];
							ChartData.TotalValue = TotalCategoryMaterialCount;
							ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *GetActorCategoryName(It.Key));
							StringArray2.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
							if(i == (int32)EMaterialBlendMode::Translucent)
							{
								TotalTranslucentMaterialCount += It.Value[i];
							}
						}
					}
					if(StringArray2.Num() > 0)
					{
						StringArray.Emplace(FString::Printf(TEXT("%s: %s"), *GetActorCategoryName(It.Key), *StringJoin(StringArray2, TEXT(", "))));
					}
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(SafeDivideToPercentage<float>(TotalTranslucentMaterialCount, TotalMaterialCount), Settings.TranslucentMaterialRatioScoreSettings));
				HealthCheckerReport.Add(TEXT("Material_Distribution"), { MoveTemp(ChartDataArray), Score, GetTranslucentMaterialRatioScoreDescription(Score.Score, TotalTranslucentMaterialCount, TotalMaterialCount), { GetTranslucentMaterialRatioScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Material_Distribution", "Material Distribution");
				UE_LOG(LogHealthChecker, Log, TEXT("Material %s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.CastDynamicShadowRatioScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetCastDynamicShadowRatioScoreDescription = [&Settings](EScore CastDynamicShadowRatioScore, int32 TotalCastDynamicShadows, int32 TotalPrimitiveComponentCount)
			{
				if(CastDynamicShadowRatioScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Dynamic_Shadow_Ratio_Description", "移動オブジェクトにダイナミックシャドウが設定されているコンポーネントの数が{0}%以内 ({1}n / {2}n = {3}%) に収まっています。"), Settings.CastDynamicShadowRatioScoreSettings[CastDynamicShadowRatioScore], TotalCastDynamicShadows, TotalPrimitiveComponentCount, SafeDivideToPercentage<float>(TotalCastDynamicShadows, TotalPrimitiveComponentCount));
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Dynamic_Shadow_Ratio_Over_Description", "移動オブジェクトにダイナミックシャドウが設定されているコンポーネントの数が{0}%をオーバー ({1}n / {2}n = {3}%) しています。"), Settings.CastDynamicShadowRatioScoreSettings[EScore::D], TotalCastDynamicShadows, TotalPrimitiveComponentCount, SafeDivideToPercentage<float>(TotalCastDynamicShadows, TotalPrimitiveComponentCount));
				}
			};
			auto GetCastDynamicShadowRatioScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Dynamic_Shadow_Ratio_Details", "移動オブジェクトにダイナミックシャドウが有効化されています。必要ない場合は設定をオフにしておくことを推奨します。");
			};

			for(const auto& It : CastDynamicShadows)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = PrimitiveComponentCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalCastDynamicShadows = GetTotalCount(CastDynamicShadows);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(SafeDivideToPercentage<float>(TotalCastDynamicShadows, TotalPrimitiveComponentCount), Settings.CastDynamicShadowRatioScoreSettings));
				HealthCheckerReport.Add(TEXT("Dynamic_Shadow_Ratio"), { MoveTemp(ChartDataArray), Score, GetCastDynamicShadowRatioScoreDescription(Score.Score, TotalCastDynamicShadows, TotalPrimitiveComponentCount), { GetCastDynamicShadowRatioScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Dynamic_Shadow_Ratio", "Dynamic Shadow Ratio");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.MovableLightCastDynamicShadowCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetMovableLightCastDynamicShadowCountScoreDescription = [&Settings](EScore MovableLightCastDynamicShadowCountScore, int32 TotalMovableLightCastDynamicShadows)
			{
				if(MovableLightCastDynamicShadowCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Movable_Light_Dynamic_Shadow_Ratio_Description", "移動オブジェクトにダイナミックシャドウが設定されていて、Movableのライトに影響を受けている可能性があるコンポーネントの数が{0}個以内 ({1}n) に収まっています。"), Settings.MovableLightCastDynamicShadowCountScoreSettings[MovableLightCastDynamicShadowCountScore], TotalMovableLightCastDynamicShadows);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Movable_Light_Dynamic_Shadow_Ratio_Over_Description", "移動オブジェクトにダイナミックシャドウが設定されていて、Movableのライトに影響を受けている可能性があるコンポーネントの数が{0}個をオーバー ({1}n) しています。"), Settings.MovableLightCastDynamicShadowCountScoreSettings[EScore::D], TotalMovableLightCastDynamicShadows);
				}
			};
			auto GetMovableLightCastDynamicShadowCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Movable_Light_Dynamic_Shadow_Ratio_Details", "移動オブジェクトにダイナミックシャドウが有効化されており、Movableのライトの影響も受けています。パフォーマンスの問題になる可能性があるので設定の確認をして下さい。");
			};

			for(const auto& It : MovableLightCastDynamicShadows)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = PrimitiveComponentCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalMovableLightCastDynamicShadows = GetTotalCount(MovableLightCastDynamicShadows);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalMovableLightCastDynamicShadows, Settings.MovableLightCastDynamicShadowCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Movable_Light_Dynamic_Shadow_Ratio"), { MoveTemp(ChartDataArray), Score, GetMovableLightCastDynamicShadowCountScoreDescription(Score.Score, TotalMovableLightCastDynamicShadows), { GetMovableLightCastDynamicShadowCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Movable_Light_Dynamic_Shadow_Ratio", "Movable Light Dynamic Shadow Ratio");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.MovableSceneLightCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetMovableSceneLightCountScoreDescription = [&Settings](EScore MovableSceneLightCountScore, int32 MovableSceneLightCount)
			{
				if(MovableSceneLightCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Scene_Light_Distribution_Description", "Movableのライトの数が{0}個以内 ({1}n) に収まっています。"), Settings.MovableSceneLightCountScoreSettings[MovableSceneLightCountScore], MovableSceneLightCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Scene_Light_Distribution_Over_Description", "Movableのライトの数が{0}個をオーバー ({1}n) しています。"), Settings.MovableSceneLightCountScoreSettings[EScore::D], MovableSceneLightCount);
				}
			};
			auto GetMovableSceneLightCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Scene_Light_Distribution_Details", "Movableのライトの数が多くなるとパフォーマンスに影響を及ぼすので設定を見直して下さい。");
			};

			int32 TotalMovableSceneLightCount = 0;
			for(int32 i = 0; i < (int32)ELightType::MAX; ++i)
			{
				ELightType LightType = (ELightType)i;
				if(const TMap<ELightMobility, TMap<bool/*bLightCastDynamicShadows*/, int32>>* LightInfo = SceneLightInfo.Find(LightType))
				{
					if(const TMap<bool/*bLightCastDynamicShadows*/, int32>* LightInfo2 = LightInfo->Find(ELightMobility::Static))
					{
						int32 StaticLightCount = 0;
						if(const int32* LightCount = LightInfo2->Find(false))
						{
							StaticLightCount += *LightCount;
						}
						if(const int32* LightCount = LightInfo2->Find(true))
						{
							StaticLightCount += *LightCount;
						}
						FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
						ChartData.Label = FString::Printf(TEXT("%s (Static)"), *GetLightTypeName(LightType));
						ChartData.Value = StaticLightCount;
						ChartData.TotalValue = TotalSceneLightCount;
						ChartData.TotalLabel = TEXT("Total SceneLight Ratio");
						StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
					}
					if(const TMap<bool/*bLightCastDynamicShadows*/, int32>* LightInfo2 = LightInfo->Find(ELightMobility::Stationary))
					{
						if(const int32* LightCount = LightInfo2->Find(false))
						{
							FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
							ChartData.Label = FString::Printf(TEXT("%s (Stationary)"), *GetLightTypeName(LightType));
							ChartData.Value = *LightCount;
							ChartData.TotalValue = TotalSceneLightCount;
							ChartData.TotalLabel = TEXT("Total SceneLight Ratio");
							StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
						}
						if(const int32* LightCount = LightInfo2->Find(true))
						{
							FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
							ChartData.Label = FString::Printf(TEXT("%s (Stationary + DynamicShadow)"), *GetLightTypeName(LightType));
							ChartData.Value = *LightCount;
							ChartData.TotalValue = TotalSceneLightCount;
							ChartData.TotalLabel = TEXT("Total SceneLight Ratio");
							StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
						}
					}
					if(const TMap<bool/*bLightCastDynamicShadows*/, int32>* LightInfo2 = LightInfo->Find(ELightMobility::Movable))
					{
						if(const int32* LightCount = LightInfo2->Find(false))
						{
							FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
							ChartData.Label = FString::Printf(TEXT("%s (Movable)"), *GetLightTypeName(LightType));
							ChartData.Value = *LightCount;
							ChartData.TotalValue = TotalSceneLightCount;
							ChartData.TotalLabel = TEXT("Total SceneLight Ratio");
							StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
							TotalMovableSceneLightCount += *LightCount;
						}
						if(const int32* LightCount = LightInfo2->Find(true))
						{
							FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
							ChartData.Label = FString::Printf(TEXT("%s (Movable + Dynamic Shadow)"), *GetLightTypeName(LightType));
							ChartData.Value = *LightCount;
							ChartData.TotalValue = TotalSceneLightCount;
							ChartData.TotalLabel = TEXT("Total SceneLight Ratio");
							StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
							TotalMovableSceneLightCount += *LightCount;
						}
					}
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalMovableSceneLightCount, Settings.MovableSceneLightCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Scene_Light_Distribution"), { MoveTemp(ChartDataArray), Score, GetMovableSceneLightCountScoreDescription(Score.Score, TotalMovableSceneLightCount), { GetMovableSceneLightCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Scene_Light_Distribution", "Scene Light Distribution");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.OverlapCountScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetOverlapCountScoreDescription = [&Settings](EScore OverlapCountScore, int32 OverlapCount)
			{
				if(OverlapCountScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Overlap_Distribution_Description", "オーバーラップを発行するコンポーネントの数が{0}個以内 ({1}n) に収まっています。"), Settings.OverlapCountScoreSettings[OverlapCountScore], OverlapCount);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Overlap_Distribution_Over_Description", "オーバーラップを発行するコンポーネントの数が{0}個をオーバー ({1}n) しています。"), Settings.OverlapCountScoreSettings[EScore::D], OverlapCount);
				}
			};
			auto GetOverlapCountScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Overlap_Distribution_Details", "必要ないものはオーバーラップを発行しないように設定することで高速化できる可能性があります。");
			};

			int32 TotalOverlapCount = 0;
			for(int32 i = 0; i < (int32)EActorCategory::MAX; ++i)
			{
				EActorCategory ActorCategory = (EActorCategory)i;
				if(IsValidCategory(ActorCategory) && MobilityAndOverlapCount.Contains(ActorCategory) && (MobilityAndOverlapCount[ActorCategory].Num() > 0))
				{
					const TMap<EMobilityAndOverlapType, int32>& TempMobilityAndOverlapCount = MobilityAndOverlapCount[ActorCategory];
					TArray<EMobilityAndOverlapType> TargetMobilityAndOverlapType = { EMobilityAndOverlapType::StaticAndOverlap, EMobilityAndOverlapType::Movable, EMobilityAndOverlapType::MovableAndOverlap };
					for(EMobilityAndOverlapType MobilityAndOverlapType : TargetMobilityAndOverlapType)
					{
						if(TempMobilityAndOverlapCount.Contains(MobilityAndOverlapType) && (TempMobilityAndOverlapCount[MobilityAndOverlapType] > 0))
						{
							FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
							ChartData.Label = FString::Printf(TEXT("%s (%s)"), *GetActorCategoryName(ActorCategory), *GetMobilityAndOverlapTypeName(MobilityAndOverlapType));
							ChartData.Value = TempMobilityAndOverlapCount[MobilityAndOverlapType];
							ChartData.TotalValue = SceneComponentCount[ActorCategory];
							ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *GetActorCategoryName(ActorCategory));
							StringArray.Emplace(FString::Printf(TEXT("%s (%s): %.1f%%(%dn/%dn)"), *GetActorCategoryName(ActorCategory), *GetMobilityAndOverlapTypeName(MobilityAndOverlapType), SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
							if(MobilityAndOverlapType == EMobilityAndOverlapType::StaticAndOverlap || MobilityAndOverlapType == EMobilityAndOverlapType::MovableAndOverlap)
							{
								TotalOverlapCount += TempMobilityAndOverlapCount[MobilityAndOverlapType];
							}
						}
					}
				}
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalOverlapCount, Settings.OverlapCountScoreSettings));
				HealthCheckerReport.Add(TEXT("Overlap_Distribution"), { MoveTemp(ChartDataArray), Score, GetOverlapCountScoreDescription(Score.Score, TotalOverlapCount), { GetOverlapCountScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Overlap_Distribution", "Overlap Distribution");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.NavMeshRatioScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetNavMeshRatioScoreDescription = [&Settings](EScore NavMeshRatioScore, int32 TotalNavMeshCount, int32 TotalPrimitiveComponentCount)
			{
				if(NavMeshRatioScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("NavMesh_Ratio_Description", "ナビメッシュが生成されているメッシュの数が{0}%以内 ({1}n / {2}n = {3}%) に収まっています。"), Settings.NavMeshRatioScoreSettings[NavMeshRatioScore], TotalNavMeshCount, TotalPrimitiveComponentCount, SafeDivideToPercentage<float>(TotalNavMeshCount, TotalPrimitiveComponentCount));
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("NavMesh_Ratio_Over_Description", "ナビメッシュが生成されているメッシュの数が{0}%をオーバー ({1}n / {2}n = {3}%) しています。"), Settings.NavMeshRatioScoreSettings[EScore::D], TotalNavMeshCount, TotalPrimitiveComponentCount, SafeDivideToPercentage<float>(TotalNavMeshCount, TotalPrimitiveComponentCount));
				}
			};
			auto GetNavMeshRatioScoreDetails = []()
			{
				return HC4UE_LOCTEXT("NavMesh_Ratio_Details", "移動可能な範囲のみナビメッシュを生成することで高速化できる可能性があります。");
			};

			for(const auto& It : NavMeshCount)
			{
				if(IsValidCategory(It.Key) && (It.Value > 0))
				{
					FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
					ChartData.Label = GetActorCategoryName(It.Key);
					ChartData.Value = It.Value;
					ChartData.TotalValue = PrimitiveComponentCount[It.Key];
					ChartData.TotalLabel = FString::Printf(TEXT("%s Category Ratio"), *ChartData.Label);
					StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
				}
			}
			if(StringArray.Num() > 0)
			{
				int32 TotalNavMeshCount = GetTotalCount(NavMeshCount);
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(SafeDivideToPercentage<float>(TotalNavMeshCount, TotalPrimitiveComponentCount), Settings.NavMeshRatioScoreSettings));
				HealthCheckerReport.Add(TEXT("NavMesh_Ratio"), { MoveTemp(ChartDataArray), Score, GetNavMeshRatioScoreDescription(Score.Score, TotalNavMeshCount, TotalPrimitiveComponentCount), { GetNavMeshRatioScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("NavMesh_Ratio", "NavMesh Ratio");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		ProgressReport();

		if(Settings.ErrorNavMeshPolygonsRatioScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetErrorNavMeshPolygonsRatioScoreDescription = [&Settings](EScore ErrorNavMeshPolygonsRatioScore, int32 NumErrorNavMeshPolygons, int32 TotalNavMeshPolygonsCount)
			{
				if(ErrorNavMeshPolygonsRatioScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Error_NavMesh_Polygons_Description", "埋もれているナビメッシュが{0}%以内 ({1}n / {2}n = {3}%) に収まっています。"), Settings.ErrorNavMeshPolygonsRatioScoreSettings[ErrorNavMeshPolygonsRatioScore], NumErrorNavMeshPolygons, TotalNavMeshPolygonsCount, SafeDivideToPercentage<float>(NumErrorNavMeshPolygons, TotalNavMeshPolygonsCount));
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Error_NavMesh_Polygons_Over_Description", "埋もれているナビメッシュが{0}%をオーバー ({1}n / {2}n = {3}%) しています。"), Settings.ErrorNavMeshPolygonsRatioScoreSettings[EScore::D], NumErrorNavMeshPolygons, TotalNavMeshPolygonsCount, SafeDivideToPercentage<float>(NumErrorNavMeshPolygons, TotalNavMeshPolygonsCount));
				}
			};
			auto GetErrorNavMeshPolygonsRatioScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Error_NavMesh_Polygons_Details", "ナビメッシュがオブジェクトに埋もれているため、パス検索の結果を正しく移動できない可能性があります。");
			};

			for(const FNavMeshPolygon& ErrorNavMeshPolygon : ErrorNavMeshPolygons)
			{
				const FVector PolygonCenter = ErrorNavMeshPolygon.GetCenter();
				StringArray.Emplace(
					FString::Printf(TEXT("%s: (X=%d, Y=%d, Z=%d)"),
					*GetComponentName(ErrorNavMeshPolygon.EdgeHitResult.GetComponent()),
					(int32)PolygonCenter.X, (int32)PolygonCenter.Y, (int32)PolygonCenter.Z)
				);
			}
			if(StringArray.Num() > 0)
			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = TEXT("Error NavMesh");
				ChartData.Value = ErrorNavMeshPolygons.Num();
				ChartData.TotalValue = TotalNavMeshPolygonsCount;
				ChartData.TotalLabel = TEXT("Total NavMesh Polygons Ratio");

				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(SafeDivideToPercentage<float>(ErrorNavMeshPolygons.Num(), TotalNavMeshPolygonsCount), Settings.ErrorNavMeshPolygonsRatioScoreSettings));
				HealthCheckerReport.Add(TEXT("Error_NavMesh_Polygons"), { MoveTemp(ChartDataArray), Score, GetErrorNavMeshPolygonsRatioScoreDescription(Score.Score, ErrorNavMeshPolygons.Num(), TotalNavMeshPolygonsCount), { GetErrorNavMeshPolygonsRatioScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Error_NavMesh_Polygons", "Error NavMesh Polygons");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %dn (e.g. %s)"), *GraphName.ToString(), ErrorNavMeshPolygons.Num(), *StringJoin(StringArray, TEXT(", "), Settings.MaxDisplayErrorNavMeshPolygons));
			}
		}

		ProgressReport();

		if(ErrorBrushPolygonsComponentNames.Num() > 0 && Settings.ErrorBrushPolygonsRatioScoreSettings.bAllowHealthCheck)
		{
			ChartDataArray.Reset();

			auto GetErrorBrushPolygonsRatioScoreDescription = [&Settings](EScore ErrorBrushPolygonsRatioScore, int32 NumErrorBrushPolygonsComponentNames, int32 TotalBrushComponentCount)
			{
				if(ErrorBrushPolygonsRatioScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Error_Brush_Polygons_Description", "穴の空いたブラシが{0}%以内 ({1}n / {2}n = {3}%) に収まっています。"), Settings.ErrorBrushPolygonsRatioScoreSettings[ErrorBrushPolygonsRatioScore], NumErrorBrushPolygonsComponentNames, TotalBrushComponentCount, SafeDivideToPercentage<float>(NumErrorBrushPolygonsComponentNames, TotalBrushComponentCount));
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Error_Brush_Polygons_Over_Description", "穴の空いたブラシが{0}%をオーバー ({1}n / {2}n = {3}%) しています。"), Settings.ErrorBrushPolygonsRatioScoreSettings[EScore::D], NumErrorBrushPolygonsComponentNames, TotalBrushComponentCount, SafeDivideToPercentage<float>(NumErrorBrushPolygonsComponentNames, TotalBrushComponentCount));
				}
			};
			auto GetErrorBrushPolygonsRatioScoreDetails = []()
			{
				return HC4UE_LOCTEXT("Error_Brush_Polygons_Details", "ブラシに穴が空いている可能性があります、ブラシの法線の確認をして下さい。");
			};

			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = TEXT("Error Brush");
				ChartData.Value = ErrorBrushPolygonsComponentNames.Num();
				ChartData.TotalValue = TotalBrushComponentCount;
				ChartData.TotalLabel = FString::Printf(TEXT("Total Error Brush Ratio"), *ChartData.Label);

				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(SafeDivideToPercentage<float>(ErrorBrushPolygonsComponentNames.Num(), TotalBrushComponentCount), Settings.ErrorBrushPolygonsRatioScoreSettings));
				HealthCheckerReport.Add(TEXT("Error_Brush_Polygons"), { MoveTemp(ChartDataArray), Score, GetErrorBrushPolygonsRatioScoreDescription(Score.Score, ErrorBrushPolygonsComponentNames.Num(), TotalBrushComponentCount), { GetErrorBrushPolygonsRatioScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("Error_Brush_Polygons", "Error Brush Polygons");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %dn (e.g. %s)"), *GraphName.ToString(), ErrorBrushPolygonsComponentNames.Num(), *StringJoin(ErrorBrushPolygonsComponentNames, TEXT(", "), Settings.MaxDisplayErrorBrushPolygons));
			}
		}

		ProgressReport();

		if(Settings.PostProcessPixelShaderInstructionsScoreSettings.bAllowHealthCheck)
		{
			StringArray.Reset();
			ChartDataArray.Reset();

			auto GetPostProcessPixelShaderInstructionsScoreDescription = [&Settings](EScore PostProcessPixelShaderInstructionsScore, int32 PostProcessPixelShaderInstructions)
			{
				if(PostProcessPixelShaderInstructionsScore <= EScore::D)
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("PostProcess_PixelShader_Instructions_Description", "ポストプロセスのピクセルシェーダー命令数の合計が{0}命令以内 ({1}n) に収まっています。"), Settings.PostProcessPixelShaderInstructionsScoreSettings[PostProcessPixelShaderInstructionsScore], PostProcessPixelShaderInstructions);
				}
				else
				{
					return HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("PostProcess_PixelShader_Instructions_Over_Description", "ポストプロセスのピクセルシェーダー命令数の合計が{0}命令をオーバー ({1}n) しています。"), Settings.PostProcessPixelShaderInstructionsScoreSettings[EScore::D], PostProcessPixelShaderInstructions);
				}
			};
			auto GetPostProcessPixelShaderInstructionsScoreDetails = []()
			{
				return HC4UE_LOCTEXT("PostProcess_PixelShader_Instructions_Details", "ポストプロセスのピクセルシェーダー命令数は一定のGPUコストが必要になるので、問題がないか確認をお願いします。");
			};

			PostProcessPixelShaderInstructions.ValueSort([](const int32& A, const int32& B){ return A >= B; });
			for(const auto& It : PostProcessPixelShaderInstructions)
			{
				FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
				ChartData.Label = FPaths::GetBaseFilename(It.Key.ToString());
				ChartData.Value = It.Value;
				ChartData.TotalValue = 0;
				ChartData.Unit = TEXT("inst");
				StringArray.Emplace(FString::Printf(TEXT("%s: %d%s"), *ChartData.Label, It.Value, *ChartData.Unit));
			}
			if(StringArray.Num() > 0)
			{
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalPostProcessPixelShaderInstructions, Settings.PostProcessPixelShaderInstructionsScoreSettings));
				HealthCheckerReport.Add(TEXT("PostProcess_PixelShader_Instructions"), { MoveTemp(ChartDataArray), Score, GetPostProcessPixelShaderInstructionsScoreDescription(Score.Score, TotalPostProcessPixelShaderInstructions), { GetPostProcessPixelShaderInstructionsScoreDetails() } });

				FText GraphName = HC4UE_LOCTEXT("PostProcess_PixelShader_Instructions", "PostProcess PixelShader Instructions");
				UE_LOG(LogHealthChecker, Log, TEXT("%s: %s"), *GraphName.ToString(), *StringJoin(StringArray, TEXT(", ")));
			}
		}

		if(FPlatformMisc::IsDebuggerPresent())
		{

		(void)HC4UE_LOCTEXT("Streaming_Compress_Texture_Description", "{0}サイズ以上のストリーミングする圧縮テクスチャが{1}個以内 ({2}n) に収まっています。");
		(void)HC4UE_LOCTEXT("Streaming_Uncompress_Texture_Description", "{0}サイズ以上のストリーミングする非圧縮テクスチャが{1}個以内 ({2}n) に収まっています。");
		(void)HC4UE_LOCTEXT("Streaming_Compress_Texture_Over_Description", "{0}サイズ以上のストリーミングする圧縮テクスチャが{1}個をオーバー ({2}n) しています。");
		(void)HC4UE_LOCTEXT("Streaming_Uncompress_Texture_Over_Description", "{0}サイズ以上のストリーミングする非圧縮テクスチャが{1}個をオーバー ({2}n) しています。");
		(void)HC4UE_LOCTEXT("Streaming_Compress_Texture_Details", "ストリーミングするテクスチャサイズが大きいとテクスチャストリーミングの待ち時間が増えるため注意して下さい。");
		(void)HC4UE_LOCTEXT("Streaming_Uncompress_Texture_Details", "ストリーミングするテクスチャサイズが大きいとテクスチャストリーミングの待ち時間が増えるため注意して下さい。");
		(void)HC4UE_LOCTEXT("Streaming_Texture", "Streaming Texture");

		(void)HC4UE_LOCTEXT("Non_Streaming_Compress_Texture_Description", "{0}サイズ以上の非ストリーミングの圧縮テクスチャが{1}個以内 ({2}n) に収まっています。");
		(void)HC4UE_LOCTEXT("Non_Streaming_Uncompress_Texture_Description", "{0}サイズ以上の非ストリーミングの非圧縮テクスチャが{1}個以内 ({2}n) に収まっています。");
		(void)HC4UE_LOCTEXT("Non_Streaming_Compress_Texture_Over_Description", "{0}サイズ以上の非ストリーミングの圧縮テクスチャが{1}個をオーバー ({2}n) しています。");
		(void)HC4UE_LOCTEXT("Non_Streaming_Uncompress_Texture_Over_Description", "{0}サイズ以上の非ストリーミングの非圧縮テクスチャが{1}個をオーバー ({2}n) しています。");
		(void)HC4UE_LOCTEXT("Non_Streaming_Compress_Texture_Details", "非ストリーミングのテクスチャサイズが大きいと初期ロードに時間がかかるため注意して下さい。");
		(void)HC4UE_LOCTEXT("Non_Streaming_Uncompress_Texture_Details", "非ストリーミングのテクスチャサイズが大きいと初期ロードに時間がかかるため注意して下さい。");
		(void)HC4UE_LOCTEXT("Non_Streaming_Texture", "Non Streaming Texture");

		}

		auto ReportStreamingTexture = [&StringArray, &StringArray2, &ChartDataArray, &ChartDataArray2, &AllScoreArray, &HealthCheckerReport](const TCHAR* TextureTypeName, const TMap<ETextureSize, TMap<bool/*Compressed*/, int32>>& TextureSizeMap, const TMap<bool/*Compressed*/, int32>& TextureCount, const FIntScoreSettings& TextureCountScoreSettings, ETextureSize CompressedTextureSizeThreshold, ETextureSize UncompressedTextureSizeThreshold)
		{
			if(!TextureCountScoreSettings.bAllowHealthCheck)
			{
				return;
			}

			StringArray.Reset();
			StringArray2.Reset();
			ChartDataArray.Reset();
			ChartDataArray2.Reset();

			FString TextureLogText = FString(TextureTypeName);
			FString TextureLocKey = TextureLogText.Replace(TEXT(" "), TEXT("_"));

			auto GetScoreDescription = [&TextureLocKey, &TextureCountScoreSettings, &CompressedTextureSizeThreshold, &UncompressedTextureSizeThreshold](EScore Score, bool bIsCompressed, int32 TextureCount)
			{
				if(Score <= EScore::D)
				{
					if(bIsCompressed)
					{
						return HC4UE_LOCTEXT_FORMAT(HC4UE_GET_LOCTEXT_FORMAT("%s_Compress_Texture_Description", *TextureLocKey), FText::FromString(GetTextureSizeName(CompressedTextureSizeThreshold)), TextureCountScoreSettings[Score], TextureCount);
					}
					else
					{
						return HC4UE_LOCTEXT_FORMAT(HC4UE_GET_LOCTEXT_FORMAT("%s_Uncompress_Texture_Description", *TextureLocKey), FText::FromString(GetTextureSizeName(UncompressedTextureSizeThreshold)), TextureCountScoreSettings[Score], TextureCount);
					}
				}
				else
				{
					if(bIsCompressed)
					{
						return HC4UE_LOCTEXT_FORMAT(HC4UE_GET_LOCTEXT_FORMAT("%s_Compress_Texture_Over_Description", *TextureLocKey), FText::FromString(GetTextureSizeName(CompressedTextureSizeThreshold)), TextureCountScoreSettings[EScore::D], TextureCount);
					}
					else
					{
						return HC4UE_LOCTEXT_FORMAT(HC4UE_GET_LOCTEXT_FORMAT("%s_Uncompress_Texture_Over_Description", *TextureLocKey), FText::FromString(GetTextureSizeName(UncompressedTextureSizeThreshold)), TextureCountScoreSettings[EScore::D], TextureCount);
					}
				}
			};
			auto GetScoreDetails = [&TextureLocKey](bool bIsCompressed)
			{
				if(bIsCompressed)
				{
					return HC4UE_GET_LOCTEXT_FORMAT("%s_Compress_Texture_Details", *TextureLocKey);
				}
				else
				{
					return HC4UE_GET_LOCTEXT_FORMAT("%s_Uncompress_Texture_Details", *TextureLocKey);
				}
			};
			auto GetTextureType = [](bool bIsCompressed)
			{
				return bIsCompressed ? TEXT("DXT/BC") : TEXT("RGB/RGBA");
			};

			int32 TotalCompressedTexture = 0;
			int32 TotalUncompressedTexture = 0;
			for(int32 i = 0; i < (int32)ETextureSize::MAX; ++i)
			{
				ETextureSize TextureSize = (ETextureSize)i;
				if(const auto* It = TextureSizeMap.Find(TextureSize))
				{
					for(const auto& It2 : *It)
					{
						if(It2.Value > 0)
						{
							if(It2.Key)
							{
								FHealthCheckerChartData& ChartData = ChartDataArray.AddDefaulted_GetRef();
								ChartData.Label = GetTextureSizeName(TextureSize);
								ChartData.Value = It2.Value;
								ChartData.TotalValue = TextureCount[It2.Key];
								ChartData.TotalLabel = FString::Printf(TEXT("Total %sTexture (%s) Ratio"), *TextureLogText, GetTextureType(true));
								StringArray.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
								if(TextureSize <= CompressedTextureSizeThreshold)
								{
									TotalCompressedTexture += It2.Value;
								}
							}
							else
							{
								FHealthCheckerChartData& ChartData = ChartDataArray2.AddDefaulted_GetRef();
								ChartData.Label = GetTextureSizeName(TextureSize);
								ChartData.Value = It2.Value;
								ChartData.TotalValue = TextureCount[It2.Key];
								ChartData.TotalLabel = FString::Printf(TEXT("Total %sTexture (%s) Ratio"), *TextureLogText, GetTextureType(false));
								StringArray2.Emplace(FString::Printf(TEXT("%s: %.1f%%(%dn/%dn)"), *ChartData.Label, SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue), ChartData.Value, ChartData.TotalValue));
								if(TextureSize <= UncompressedTextureSizeThreshold)
								{
									TotalUncompressedTexture += It2.Value;
								}
							}
						}
					}
				}
			}
			if(StringArray.Num() > 0)
			{
				constexpr bool bIsCompressed = true;
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalCompressedTexture, TextureCountScoreSettings));
				HealthCheckerReport.Add(*FString::Printf(TEXT("%s_Texture_(%s)"), *TextureLocKey, GetTextureType(bIsCompressed)), { MoveTemp(ChartDataArray), Score, GetScoreDescription(Score.Score, bIsCompressed, TotalCompressedTexture), { GetScoreDetails(bIsCompressed) } });

				FText GraphName = HC4UE_GET_LOCTEXT_FORMAT("%s_Texture", *TextureLocKey);
				UE_LOG(LogHealthChecker, Log, TEXT("%s (%s): %s"), *GraphName.ToString(), GetTextureType(bIsCompressed), *StringJoin(StringArray, TEXT(", ")));
			}
			if(StringArray2.Num() > 0)
			{
				constexpr bool bIsCompressed = false;
				const FScore& Score = AllScoreArray.Emplace_GetRef(GetScore(TotalUncompressedTexture, TextureCountScoreSettings));
				HealthCheckerReport.Add(*FString::Printf(TEXT("%s_Texture_(%s)"), *TextureLocKey, GetTextureType(bIsCompressed)), { MoveTemp(ChartDataArray2), Score, GetScoreDescription(Score.Score, bIsCompressed, TotalUncompressedTexture), { GetScoreDetails(bIsCompressed) } });

				FText GraphName = HC4UE_GET_LOCTEXT_FORMAT("%s_Texture", *TextureLocKey);
				UE_LOG(LogHealthChecker, Log, TEXT("%s (%s): %s"), *GraphName.ToString(), GetTextureType(bIsCompressed), *StringJoin(StringArray2, TEXT(", ")));
			}
		};

		if(StreamedInTextureCount.Num() > 0 && !bIsEditorMode)
		{
			ReportStreamingTexture(TEXT("Streamed In"), StreamedInTextureSizeMap, StreamedInTextureCount, Settings.StreamedInTextureCountScoreSettings, Settings.StreamingCompressedTextureSizeThreshold, Settings.StreamingUncompressedTextureSizeThreshold);
		}

		ProgressReport();

		if(StreamingTextureCount.Num() > 0)
		{
			ReportStreamingTexture(TEXT("Streaming"), StreamingTextureSizeMap, StreamingTextureCount, Settings.StreamingTextureCountScoreSettings, Settings.StreamingCompressedTextureSizeThreshold, Settings.StreamingUncompressedTextureSizeThreshold);
		}

		ProgressReport();

		if(NonStreamingTextureCount.Num() > 0)
		{
			ReportStreamingTexture(TEXT("Non Streaming"), NonStreamingTextureSizeMap, NonStreamingTextureCount, Settings.NonStreamingTextureCountScoreSettings, Settings.NonStreamingCompressedTextureSizeThreshold, Settings.NonStreamingUncompressedTextureSizeThreshold);
		}

		ProgressReport();

		ensure(CurrentReportCount == MaxReportCount);
	}

	UE_LOG(LogHealthChecker, Log, TEXT("Report: Finished"));

	return true;
}; // RunImpl

	bool bCheckResult = RunImpl();

	ensure(Progress.CompletedWork <= Progress.TotalAmountOfWork);
	ensure(Progress.TotalAmountOfWork == 100.f);
	UpdateProgressTo(Progress.TotalAmountOfWork); // 100%まで終了

	// 最終処理

	// レベルの表示を戻す
	if(Settings.bUnloadLevelsAfterCheck && bIsEditorMode)
	{
		UE_LOG(LogHealthChecker, Log, TEXT("Reset Level Visibility: Start"));

		// ワールドパーティションの場合

#if HC4UE_UE5_1 // WorldPartition
		if(EditorWorldPartition)
		{
			for(auto It : EditorLoaderAdapters)
			{
				It.Value->GetLoaderAdapter()->Unload();
				EditorWorldPartition->ReleaseEditorLoaderAdapter(It.Value);
			}
			EditorLoaderAdapters.Reset();
			EditorWorldPartition = nullptr;
		}
#endif

		// 通常のレベルの場合

		for(const auto& SubLevelVisibility : LevelVisibility.SubLevelVisibilities)
		{
			if(ULevelStreaming* StreamingLevel = EditorWorld->GetLevelStreamingForPackageName(SubLevelVisibility.Key))
			{
				StreamingLevel->SetShouldBeVisible(SubLevelVisibility.Value.bShouldBeVisible);
				StreamingLevel->SetShouldBeVisibleInEditor(SubLevelVisibility.Value.bShouldBeVisibleInEditor);
				StreamingLevel->SetShouldBeLoaded(SubLevelVisibility.Value.bShouldBeLoaded);
				if(ULevel* Level = StreamingLevel->GetLoadedLevel())
				{
#if HC4UE_UE5_4 // ForceCantReuseUnloadedButStillAround
					Level->SetForceCantReuseUnloadedButStillAround(SubLevelVisibility.Value.bForceCantReuseUnloadedButStillAround);
#endif
				}
			}
		}
		SetLevelsVisibility(EditorWorld->PersistentLevel, LevelVisibility.bPersistentLevelShouldBeVisibleInEditor);

		EditorWorld->FlushLevelStreaming();

		UE_LOG(LogHealthChecker, Log, TEXT("Reset Level Visibility: Finished"));
	}

	auto BuildReportView = [&WorldPackagePath, &WorldType, &HealthCheckerReport, &AllScoreArray, &Settings, &MessageLog]()
	{
		FHealthCheckerReportView View;
		View.bValid = true;
		View.Project = FApp::GetProjectName();
		View.Map = WorldPackagePath;
		View.Engine = FString::Printf(TEXT("UE%s - %s - %s"), *FEngineVersion::Current().ToString(EVersionComponent::Patch), GetWorldTypeString(WorldType), GetHealthCheckerEditorLanguage());
		View.GeneratedBy = Settings.bUseUserNameInReport
			? FString::Printf(TEXT("%s - %s"), FPlatformProcess::ComputerName(), FPlatformProcess::UserName())
			: FString(TEXT("HC4UE"));
		View.Version = UHealthCheckerSettings::GetVersion();
		View.LastUpdate = FDateTime::Now().ToString();

		auto CalcScoreAverage = [](const TArray<FScore>& ScoreArray)
		{
			float TotalScore = 0.f;
			for(const FScore& Score : ScoreArray)
			{
				if(!Score.bAllowHealthCheck || Score.ScoreWeight <= 0.f)
				{
					continue;
				}

				TotalScore += (float)Score.Score * Score.ScoreWeight;
			}
			return (EScore)(FMath::Min<int32>(FMath::DivideAndRoundNearest<float>(TotalScore, ScoreArray.Num()), (int32)EScore::MAX - 1));
		};
		const EScore OverallScore = CalcScoreAverage(AllScoreArray);
		View.OverallScore = GetScoreString(OverallScore);
		View.OverallDescription = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Overall_Score_Description", "総合評価は{0}です。詳細は各グラフの評価を確認してください。"), FText::FromString(View.OverallScore)).ToString();

		for(const auto& Report : HealthCheckerReport)
		{
			if(!Report.Value.Score.bAllowHealthCheck || Report.Value.Score.ScoreWeight <= 0.f)
			{
				continue;
			}

			FString KeyString = Report.Key.ToString();
			FString GraphName, CategoryString;
			if(!KeyString.Split(TEXT("_("), &GraphName, &CategoryString))
			{
				GraphName = MoveTemp(KeyString);
			}

			FText LocText;
#if HC4UE_UE5_5
			if(FText::FindTextInLiveTable_Advanced(UHealthCheckerSettings::GetHealthCheckerString(), GraphName, LocText))
#else
			if(FText::FindText(UHealthCheckerSettings::GetHealthCheckerString(), GraphName, LocText))
#endif
			{
				GraphName = LocText.ToString();
			}
			else
			{
				GraphName.ReplaceInline(TEXT("_"), TEXT(" "));
			}

			if(!CategoryString.IsEmpty())
			{
				GraphName += TEXT(" (") + CategoryString;
			}

			FHealthCheckerTableSection& Section = View.Sections.AddDefaulted_GetRef();
			Section.Title = GraphName;
			Section.Score = GetScoreString(Report.Value.Score.Score);

			FString Description = Report.Value.Description.ToString();
			for(const FText& DetailsText : Report.Value.DetailsArray)
			{
				const FString Details = DetailsText.ToString();
				if(!Details.IsEmpty())
				{
					Description += TEXT("\n\n");
					Description += Details;
				}
			}
			Section.Description = MoveTemp(Description);

			for(const FHealthCheckerChartData& ChartData : Report.Value.ChartData)
			{
				if(ChartData.Value == 0)
				{
					continue;
				}

				FHealthCheckerTableRow& Row = Section.Rows.AddDefaulted_GetRef();
				Row.Label = ChartData.Label;
				Row.Value = ChartData.Value;
				Row.TotalValue = ChartData.TotalValue;
				Row.Unit = ChartData.Unit;
				Row.TotalLabel = ChartData.TotalLabel;
				if(ChartData.TotalValue != 0)
				{
					Row.bHasRatio = true;
					Row.Ratio = SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue);
				}
			}
		}

		return View;
	};

	if(bCheckResult)
	{
		HealthCheckerReport::SetLast(BuildReportView());
		UE_CLOG(bSkipAutoOpenReport, LogHealthChecker, Log, TEXT("Health Checker report updated for the Slate window."));
	}

	GAssetRegistry = nullptr;

	UE_LOG(LogHealthChecker, Log, TEXT("HealthChecker: Finished"));

	if(Settings.bOpenMapCheckWhenFinished && !bSkipAutoOpenReport)
	{
		MessageLog.Open();
	}

	return true;
}

#undef HC4UE_GET_SCRIPT_CLASS

#ifdef NumScoreSettings
#undef NumScoreSettings
#endif

#undef HC4UE_LOCTEXT
#undef HC4UE_LOCTEXT_FORMAT

#undef HC4UE_GET_LOCTEXT
#undef HC4UE_GET_LOCTEXT_FORMAT
#undef HC4UE_GET_LOCTEXT_VAR

#undef HC4UE_CRLF

#undef LOCTEXT_NAMESPACE

#undef HC4UE_UE5
#undef HC4UE_UE5_0
#undef HC4UE_UE5_1
#undef HC4UE_UE5_2
#undef HC4UE_UE5_3
#undef HC4UE_UE5_4
#undef HC4UE_UE5_5
#undef HC4UE_UE5_6

#if HC4UE_DEBUG
PRAGMA_ENABLE_OPTIMIZATION
#endif
#undef HC4UE_DEBUG

//todo メニューにMapCheckを開くボタンを追加