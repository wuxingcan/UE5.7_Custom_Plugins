// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "HealthCheckerTypes.h"
#include "HealthCheckerSettings.generated.h"

/**
 * Settings for Health Checker
 */
UCLASS(MinimalAPI, config=Game, DisplayName="Health Checker")
class UHealthCheckerSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	UHealthCheckerSettings()
	{
		CategoryName = TEXT("Plugins");
		SectionName = GetHealthCheckerDisplayName();
	}

public:

	static const TCHAR* GetVersion()
	{
		static const TCHAR* Char = TEXT("1.11");
		return Char;
	}

	static const FString& GetHealthCheckerString()
	{
		static const FString String = TEXT("HealthChecker");
		return String;
	}

	static const FName& GetHealthCheckerName()
	{
		static const FName Name = *GetHealthCheckerString();
		return Name;
	}

	static const FString& GetHealthCheckerDisplayString()
	{
		static const FString String = TEXT("Health Checker");
		return String;
	}

	static const FName& GetHealthCheckerDisplayName()
	{
		static const FName Name = *GetHealthCheckerDisplayString();
		return Name;
	}

	static FText GetHealthCheckerDisplayText()
	{
		return NSLOCTEXT("HealthChecker", "HealthChecker", "Health Checker");
	}

public:

	/**
	 * Unload levels and WorldPartition cells after running HealthChecker
	 * HealthChecker実行後にレベルやワールドパーテーションのセルをアンロードする
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bUnloadLevelsAfterCheck = true;

	/**
	 * Ignore EditorOnly Actors and Components
	 * EditorOnlyのアクターとコンポーネントを無視する
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bIgnoreEditorOnlyActorsAndComponents = true;

	/**
	 * Post warnings to MapCheck window
	 * MapCheckに警告をポストする
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bPostToMapCheck = true;

	/**
	 * Post warnings to the Output Log
	 * ログに警告をポストする
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bPostToLog = true;

	/**
	 * Open the report when finished
	 * 最後にレポートを開く
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bOpenReportWhenFinished = true;

	/**
	 * Open the MapCheck window when finished
	 * 最後にマップチェックウインドウを開く
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bOpenMapCheckWhenFinished = true;

	/**
	 * Include the username in the report
	 * レポートにユーザー名を使用する
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bUseUserNameInReport = false;

	/**
	 * Append engine version to search hints
	 * 検索のヒントにエンジンバージョン情報を付与する
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bAddEngineVersionToSearchHints = true;

	/**
	 * Actor categories to display in the report
	 * レポートに表示するアクターカテゴリ
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings", meta=(Bitmask, BitmaskEnum="/Script/HealthChecker.EBitActorCategory"))
	int32 ReportActorCategories = INT_MAX;

public:

	/**
	 * Number of map load time entries to display in the ranking
	 * マップのロード時間のランキングを表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayMapLoadTimeRanking = 5;

	/**
	 * Bounds scale used for displaying AttachParentBounds warnings
	 * AttachParentBoundsの警告を表示するバウンスのスケール
	 */
	UPROPERTY(config, EditAnywhere, Category="MapCheck|Component")
	float WarningAttachParentBoundsScale = 2.f;

	/**
	 * Max number of AttachParentBounds warnings to display
	 * AttachParentBoundsの警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Component")
	int32 MaxDisplayNeedsAttachParentBounds = 5;

	/**
	 * Max number of AutoManageAttachment warnings to display
	 * AutoManageAttachmentの警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Audio / Particle")
	int32 MaxDisplayNeedsAutoManageAttachment = 5;

	/**
	 * Max number of AudioPlayMode warnings to display
	 * AudioPlayModeの警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Audio")
	int32 MaxDisplayNeedsAudioPlayMode = 5;

	/**
	 * Max number of StaticMeshActors with the same StaticMesh to display
	 * 同じStaticMeshを持つStaticMeshActorを表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayStaticMeshActorSameMesh = 5;

	/**
	 * Ignore warnings for StaticMeshActors with the same StaticMesh when dynamic instancing is enabled
	 * 自動インスタンス化している場合は同じStaticMeshを持つStaticMeshActorの警告を無視する
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	bool bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled = false;

	/**
	 * Max number of warnings for duplicate materials in material slots
	 * マテリアルスロットに同じマテリアルが存在する警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Material")
	int32 MaxDisplaySameMaterialsInMaterialSlots = 5;

	/**
	 * Max number of warnings for mismatched override material counts
	 * オーバーライドマテリアルの数が元のメッシュのマテリアルの数と違う場合に警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Material")
	int32 MaxDisplayMismatchNumOverrideMaterial = 5;

	/**
	 * Max number of warnings for missing materials
	 * マテリアルがアサインされていないコンポーネントの警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Material")
	int32 MaxDisplayMissingMaterials = 5;

	/**
	 * Max number of warnings for missing meshes
	 * メッシュがアサインされていないコンポーネントの警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayMissingMeshes = 5;

	/**
	 * Max number of warnings for meshes without LODs
	 * LODが存在しないメッシュの警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayNoLodsMeshes = 5;

	/**
	 * Max number of warnings for missing components
	 * コンポーネントが存在しないアクターの警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Component")
	int32 MaxDisplayMissingComponents = 5;

	/**
	 * Number of mesh vertex count rankings to display
	 * メッシュの頂点数ランキングを表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayVertexRanking = 5;

	/**
	 * Number of SkeletalMesh bone count rankings to display
	 * スケルタルメッシュのボーン数ランキングを表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayBoneCountRanking = 5;

	/**
	 * Number of SkeletalMesh bone LOD ratio rankings to display
	 * スケルタルメッシュのボーンLODの割合のランキングを表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayBoneReductionRateRanking = 5;

	/**
	 * Max number of warnings for buried NavMesh polygons
	 * NavMeshが埋もれているポリゴンの警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Navigation")
	int32 MaxDisplayErrorNavMeshPolygons = 5;

	/**
	 * Duration for drawing buried NavMesh polygons
	 * NavMeshの埋もれているポリゴンを描画する時間
	 */
	UPROPERTY(config, EditAnywhere, Category="MapCheck|Navigation")
	float DrawNavMeshPolygonTimer = 10.f;

	/**
	 * Max number of warnings for brushes with holes
	 * Brushに穴が空いているコンポーネントの警告を表示する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Brush")
	int32 MaxDisplayErrorBrushPolygons = 5;

	/**
	 * Warning threshold for NiagaraSystem WarmupTime (sec)
	 * NiagaraSystemのWarmupTimeの警告する時間（秒）
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Particle")
	float WarningNiagaraWarmupTime = 1.f;

	/**
	 * Max number of warnings for NiagaraSystem Renderers
	 * NiagaraSystemのRendererの警告する数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Particle")
	int32 WarningNiagaraRendererCount = 10;

	/**
	 * Warning size for VolumeTextures used in Mesh Renderers
	 * Mesh Rendererで使用されているVolumeTextureの警告するサイズ
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Particle")
	int32 WarningNiagaraVolumeTextureSize = 64;

	/**
	 * Pixel shader instruction count threshold for PostProcess warnings
	 * 警告を表示するポストプロセスのピクセルシェーダー命令数
	 */
	UPROPERTY(config, EditAnywhere, Category="MapCheck|Post Process")
	int32 WarningPostProcessPixelShaderInstructions = 200;

	/**
	 * Texture size threshold for compressed texture warnings
	 * 圧縮テクスチャサイズの警告を表示するサイズ
	 */
	UPROPERTY(config, EditAnywhere, Category="MapCheck|Texture")
	ETextureSize WarningCompressedTextureSize = ETextureSize::Size4096;

	/**
	 * Texture size threshold for uncompressed texture warnings
	 * 非圧縮テクスチャサイズの警告を表示するサイズ
	 */
	UPROPERTY(config, EditAnywhere, Category="MapCheck|Texture")
	ETextureSize WarningUncompressedTextureSize = ETextureSize::Size4096;

public:

	/**
	 * Level count score settings (n)
	 * レベル数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Level")
	FIntScoreSettings LevelCountScoreSettings =
	{//	A,		B,		C,		D,		E
		200,	500,	1000,	2000
	};

	/**
	 * Map load time score settings (sec)
	 * マップロード時間のスコア設定 （秒）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Level")
	FFloatScoreSettings MapLoadTimeScoreSettings =
	{//	A,		B,		C,		D,		E
		0.05f,	0.1f,	0.5f,	1
	};

	/**
	 * Actor count score settings (n)
	 * アクター数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Actor")
	FIntScoreSettings ActorCountScoreSettings =
	{//	A,		B,		C,		D,		E
		2000,	3000,	5000,	10000
	};

	/**
	 * Max component count score settings (n)
	 * コンポーネント最大数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Actor")
	FIntScoreSettings ComponentMaxCountScoreSettings =
	{//	A,		B,		C,		D,		E
		30,		50,		100,	200
	};

	/**
	 * Average component count score settings (n)
	 * コンポーネント平均数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Actor")
	FIntScoreSettings ComponentAverageCountScoreSettings =
	{//	A,		B,		C,		D,		E
		20,		50,		75,		100
	};

	/**
	 * Tick ratio score settings (%)
	 * アクターのTick数の割合のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Actor")
	FFloatScoreSettings ActorTickRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * Blueprint ratio score settings (%)
	 * ブループリント数の割合のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Actor")
	FFloatScoreSettings BlueprintRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * StaticMeshActor with same StaticMesh score settings (n)
	 * 同じスタティックメッシュがアサインされているStaticMeshActorの数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings StaticMeshActorSameMeshCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * Needs AttachParentBounds count score settings (n)
	 * AttachParentBoundsが必要な数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Component")
	FIntScoreSettings NeedsAttachParentBoundsCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * Needs AutoManageAttachment count score settings (n)
	 * AutoManageAttachmentが必要な数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Audio / Particle")
	FIntScoreSettings NeedsAutoManageAttachmentCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * Needs multiple AudioPlayMode count score settings (n)
	 * AudioPlayModeCountが必要な数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Audio")
	FIntScoreSettings NeedsMultipleAudioPlayModeCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * Same materials in slots count score settings (n)
	 * マテリアルスロットに同じマテリアルが存在する数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Material")
	FIntScoreSettings SameMaterialsInMaterialSlotsCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * Override material mismatch count score settings (n)
	 * オーバーライドマテリアルの数が元のメッシュのマテリアルの数と違う数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Material")
	FIntScoreSettings MismatchNumOverrideMaterialCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * Missing materials count score settings (n)
	 * マテリアルがアサインされていないコンポーネントの数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Material")
	FIntScoreSettings MissingMaterialsCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * Missing meshes count score settings (n)
	 * メッシュがアサインされていないコンポーネントの数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings MissingMeshesCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * No LODs mesh count score settings (n)
	 * LODが存在しないメッシュの数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings NoLodsMeshCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * Missing components count score settings (n)
	 * コンポーネントが存在しないアクターの数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Component")
	FIntScoreSettings MissingComponentsCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * StaticMesh vertex count ranking score settings (vtx)
	 * スタティックメッシュの頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings StaticMeshCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * StaticMesh hard-edge vertex count ranking score settings
	 * スタティックメッシュのハードエッジ頂点数ランキングのスコア設定
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings StaticMeshHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * Nanite StaticMesh vertex count ranking score settings (vtx)
	 * Naniteスタティックメッシュの頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings StaticMeshNaniteCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * Nanite StaticMesh hard-edge vertex count ranking score settings (vtx)
	 * Naniteスタティックメッシュのハードエッジ頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings StaticMeshNaniteHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * SkeletalMesh vertex count ranking score settings (vtx)
	 * スケルタルメッシュの頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings SkeletalMeshCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * SkeletalMesh hard-edge vertex count ranking score settings (vtx)
	 * スケルタルメッシュのハードエッジ頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings SkeletalMeshHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * Nanite SkeletalMesh vertex count ranking score settings (vtx)
	 * Naniteスケルタルメッシュの頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings SkeletalMeshNaniteCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * Nanite SkeletalMesh hard-edge vertex count ranking score settings (vtx)
	 * スケルタルメッシュのハードエッジ頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings SkeletalMeshNaniteHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * Particle mesh vertex count ranking score settings (vtx)
	 * パーティクルで使用されているメッシュの頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FIntScoreSettings ParticleMeshCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * Particle mesh hard-edge vertex count ranking score settings (vtx)
	 * パーティクルで使用されているメッシュのハードエッジ頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FIntScoreSettings ParticleMeshHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * SkeletalMesh bone count ranking score settings (n)
	 * スケルタルメッシュのボーン数ランキングのスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings BoneCountScoreSettings =
	{//	A,		B,		C,		D,		E
		75,		256,	512,	1024
	};

	/**
	 * Ignore bones when checking SkeletalMesh bone LODs (n)
	 * スケルタルメッシュのボーンLODチェックを無視する骨の数（本）
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 IgnoreBoneReductionRateBoneCountThreshold = 30;

	/**
	 * SkeletalMesh bone LOD ratio score settings (%)
	 * スケルタルメッシュのボーンLODの割合のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FFloatScoreSettings BoneReductionRateScoreSettings =
	{//	A,		B,		C,		D,		E
		50,		70,		80,		90
	};

	/**
	 * Particle Nanite mesh vertex count ranking score settings (vtx)
	 * パーティクルで使用されているNaniteメッシュの頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FIntScoreSettings ParticleMeshNaniteCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * Particle Nanite mesh hard-edge vertex count ranking score settings (vtx)
	 * パーティクルで使用されているNaniteメッシュのハードエッジ頂点数ランキングのスコア設定（頂点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FIntScoreSettings ParticleMeshNaniteHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * Niagara stateful emitter ratio score settings (%)
	 * NiagaraのStatefulエミッターの割合のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FFloatScoreSettings NiagaraStatefulEmitterRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * Niagara optimization-ready emitter ratio score settings (%)
	 * Niagaraエミッターの最適化の余地のある個数のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FFloatScoreSettings NiagaraEmitterOptimizationHintsScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * Niagara optimization-ready system ratio score settings (%)
	 * NiagaraSystemの最適化の余地のある個数のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FFloatScoreSettings NiagaraSystemOptimizationHintsScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * Translucent material ratio score settings (%)
	 * 半透明マテリアルの割合のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Material")
	FFloatScoreSettings TranslucentMaterialRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * Dynamic shadow ratio score settings (%)
	 * ダイナミックシャドウの割合のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Lighting")
	FFloatScoreSettings CastDynamicShadowRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * Movable light casting dynamic shadows count score settings (n)
	 * 移動オブジェクトがMovableのライトからダイナミックシャドウを投影する数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Lighting")
	FIntScoreSettings MovableLightCastDynamicShadowCountScoreSettings =
	{//	A,		B,		C,		D,		E
		2,		5,		10,		20
	};

	/**
	 * Movable light count score settings (n)
	 * Movableのライトの数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Lighting")
	FIntScoreSettings MovableSceneLightCountScoreSettings =
	{//	A,		B,		C,		D,		E
		2,		5,		10,		20
	};

	/**
	 * Overlap count score settings (n)
	 * オーバーラップの数のスコア設定（個）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Collision")
	FIntScoreSettings OverlapCountScoreSettings =
	{//	A,		B,		C,		D,		E
		200,	500,	1000,	2000
	};

	/**
	 * NavMesh ratio score settings (%)
	 * NavMeshが生成されている割合のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Navigation")
	FFloatScoreSettings NavMeshRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		50,		60,		70,		80
	};

	/**
	 * Error NavMesh polygons ratio score settings (%)
	 * NavMeshが埋もれているポリゴンがある割合のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Navigation")
	FFloatScoreSettings ErrorNavMeshPolygonsRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		1,		3,		5
	};

	/**
	 * Error brush polygons ratio score settings (%)
	 * Brushに穴が空いているコンポーネントの割合のスコア設定（％）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Brush")
	FFloatScoreSettings ErrorBrushPolygonsRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * PostProcess pixel shader instructions score settings (inst)
	 * ポストプロセスのピクセルシェーダー命令数のスコア設定（命令）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|PostProcess")
	FIntScoreSettings PostProcessPixelShaderInstructionsScoreSettings =
	{//	A,		B,		C,		D,		E
		100,	200,	300,	500
	};

	/**
	 * Streaming compressed texture size threshold
	 * ストリーミングする圧縮テクスチャサイズの評価しきい値
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	ETextureSize StreamingCompressedTextureSizeThreshold = ETextureSize::Size4096;

	/**
	 * Streaming uncompressed texture size threshold
	 * ストリーミングする非圧縮テクスチャサイズの評価しきい値
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	ETextureSize StreamingUncompressedTextureSizeThreshold = ETextureSize::Size2048;

	/**
	 * Streaming textures with counts exceeding the threshold (n)
	 * ストリーミングするテクスチャでしきい値以上の数のスコア設定（枚）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	FIntScoreSettings StreamingTextureCountScoreSettings =
	{//	A,		B,		C,		D,		E
		10,		20,		30,		50
	};

	/**
	 * Non-Streaming compressed texture size threshold
	 * 非ストリーミングの圧縮テクスチャサイズの評価しきい値
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	ETextureSize NonStreamingCompressedTextureSizeThreshold = ETextureSize::Size4096;

	/**
	 * Non-Streaming uncompressed texture size threshold
	 * 非ストリーミングの非圧縮テクスチャサイズの評価しきい値
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	ETextureSize NonStreamingUncompressedTextureSizeThreshold = ETextureSize::Size2048;

	/**
	 * Non-Streaming textures with counts exceeding the threshold (n)
	 * 非ストリーミングのテクスチャでしきい値以上の数のスコア設定（枚）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	FIntScoreSettings NonStreamingTextureCountScoreSettings =
	{//	A,		B,		C,		D,		E
		10,		20,		30,		50
	};

	/**
	 * Currently streamed-in textures with counts exceeding the threshold (n)
	 * 使用中のテクスチャでしきい値以上の数のスコア設定（枚）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	FIntScoreSettings StreamedInTextureCountScoreSettings =
	{//	A,		B,		C,		D,		E
		10,		20,		30,		50
	};
};
