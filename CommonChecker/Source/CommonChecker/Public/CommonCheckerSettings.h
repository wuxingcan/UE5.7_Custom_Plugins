// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "CommonCheckerTypes.h"
#include "CommonCheckerSettings.generated.h"

/**
 * Settings for Health Checker
 */
UCLASS(MinimalAPI, config=Game, DisplayName="Health Checker")
class UCommonCheckerSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	UCommonCheckerSettings()
	{
		CategoryName = TEXT("Plugins");
		SectionName = GetCommonCheckerDisplayName();
	}

public:

	static const TCHAR* GetVersion()
	{
		static const TCHAR* Char = TEXT("1.11");
		return Char;
	}

	static const FString& GetCommonCheckerString()
	{
		static const FString String = TEXT("CommonChecker");
		return String;
	}

	static const FName& GetCommonCheckerName()
	{
		static const FName Name = *GetCommonCheckerString();
		return Name;
	}

	static const FString& GetCommonCheckerDisplayString()
	{
		static const FString String = TEXT("Health Checker");
		return String;
	}

	static const FName& GetCommonCheckerDisplayName()
	{
		static const FName Name = *GetCommonCheckerDisplayString();
		return Name;
	}

	static FText GetCommonCheckerDisplayText()
	{
		return NSLOCTEXT("CommonChecker", "CommonChecker", "Health Checker");
	}

public:

	/**
	 * 运行 CommonChecker 后卸载关卡和 WorldPartition 单元
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bUnloadLevelsAfterCheck = true;

	/**
	 * 忽略 EditorOnly 的 Actor 和 Component
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bIgnoreEditorOnlyActorsAndComponents = true;

	/**
	 * 将警告发送到 MapCheck 窗口
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bPostToMapCheck = true;

	/**
	 * 将警告发送到输出日志
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bPostToLog = true;

	/**
	 * 完成后打开报告
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bOpenReportWhenFinished = true;

	/**
	 * 完成后打开 MapCheck 窗口
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bOpenMapCheckWhenFinished = true;

	/**
	 * 在报告中包含用户名
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bUseUserNameInReport = false;

	/**
	 * 在搜索提示中附加引擎版本信息
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings")
	bool bAddEngineVersionToSearchHints = true;

	/**
	 * 报告中显示的 Actor 类别
	 */
	UPROPERTY(config, EditAnywhere, Category="Health Checker Settings", meta=(Bitmask, BitmaskEnum="/Script/CommonChecker.EBitActorCategory"))
	int32 ReportActorCategories = INT_MAX;

public:

	/**
	 * 地图加载时间排行中显示的条目数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayMapLoadTimeRanking = 5;

	/**
	 * 显示 AttachParentBounds 警告时使用的包围盒缩放
	 */
	UPROPERTY(config, EditAnywhere, Category="MapCheck|Component")
	float WarningAttachParentBoundsScale = 2.f;

	/**
	 * 显示的 AttachParentBounds 警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Component")
	int32 MaxDisplayNeedsAttachParentBounds = 5;

	/**
	 * 显示的 AutoManageAttachment 警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Audio / Particle")
	int32 MaxDisplayNeedsAutoManageAttachment = 5;

	/**
	 * 显示的 AudioPlayMode 警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Audio")
	int32 MaxDisplayNeedsAudioPlayMode = 5;

	/**
	 * 显示的共享相同 StaticMesh 的 StaticMeshActor 最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayStaticMeshActorSameMesh = 5;

	/**
	 * 开启动态实例化时，忽略共享相同 StaticMesh 的 StaticMeshActor 警告
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	bool bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled = false;

	/**
	 * 显示的材质槽位重复材质警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Material")
	int32 MaxDisplaySameMaterialsInMaterialSlots = 5;

	/**
	 * 显示的覆盖材质数量不匹配警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Material")
	int32 MaxDisplayMismatchNumOverrideMaterial = 5;

	/**
	 * 显示的缺失材质警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Material")
	int32 MaxDisplayMissingMaterials = 5;

	/**
	 * 显示的缺失网格警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayMissingMeshes = 5;

	/**
	 * 显示的缺失 LOD 网格警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayNoLodsMeshes = 5;

	/**
	 * 显示的缺失组件警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Component")
	int32 MaxDisplayMissingComponents = 5;

	/**
	 * 显示的网格顶点数排行条目数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayVertexRanking = 5;

	/**
	 * 显示的 SkeletalMesh 骨骼数排行条目数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayBoneCountRanking = 5;

	/**
	 * 显示的 SkeletalMesh 骨骼 LOD 比例排行条目数
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 MaxDisplayBoneReductionRateRanking = 5;

	/**
	 * 显示的嵌入物体 NavMesh 多边形警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Navigation")
	int32 MaxDisplayErrorNavMeshPolygons = 5;

	/**
	 * 绘制嵌入物体 NavMesh 多边形的时间
	 */
	UPROPERTY(config, EditAnywhere, Category="MapCheck|Navigation")
	float DrawNavMeshPolygonTimer = 10.f;

	/**
	 * 显示的带孔 Brush 警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Brush")
	int32 MaxDisplayErrorBrushPolygons = 5;

	/**
	 * NiagaraSystem WarmupTime 警告阈值（秒）
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Particle")
	float WarningNiagaraWarmupTime = 1.f;

	/**
	 * 显示的 NiagaraSystem 渲染器警告最大数量
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Particle")
	int32 WarningNiagaraRendererCount = 10;

	/**
	 * Mesh Renderer 中使用的 VolumeTexture 警告尺寸
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Particle")
	int32 WarningNiagaraVolumeTextureSize = 64;

	/**
	 * 后处理警告的像素着色器指令数阈值
	 */
	UPROPERTY(config, EditAnywhere, Category="MapCheck|Post Process")
	int32 WarningPostProcessPixelShaderInstructions = 200;

	/**
	 * 压缩纹理警告的尺寸阈值
	 */
	UPROPERTY(config, EditAnywhere, Category="MapCheck|Texture")
	ETextureSize WarningCompressedTextureSize = ETextureSize::Size4096;

	/**
	 * 未压缩纹理警告的尺寸阈值
	 */
	UPROPERTY(config, EditAnywhere, Category="MapCheck|Texture")
	ETextureSize WarningUncompressedTextureSize = ETextureSize::Size4096;

public:

	/**
	 * 关卡数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Level")
	FIntScoreSettings LevelCountScoreSettings =
	{//	A,		B,		C,		D,		E
		200,	500,	1000,	2000
	};

	/**
	 * 地图加载时间评分设置（秒）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Level")
	FFloatScoreSettings MapLoadTimeScoreSettings =
	{//	A,		B,		C,		D,		E
		0.05f,	0.1f,	0.5f,	1
	};

	/**
	 * Actor 数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Actor")
	FIntScoreSettings ActorCountScoreSettings =
	{//	A,		B,		C,		D,		E
		2000,	3000,	5000,	10000
	};

	/**
	 * 组件最大数评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Actor")
	FIntScoreSettings ComponentMaxCountScoreSettings =
	{//	A,		B,		C,		D,		E
		30,		50,		100,	200
	};

	/**
	 * 组件平均数评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Actor")
	FIntScoreSettings ComponentAverageCountScoreSettings =
	{//	A,		B,		C,		D,		E
		20,		50,		75,		100
	};

	/**
	 * Actor Tick 数量比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Actor")
	FFloatScoreSettings ActorTickRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * 蓝图比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Actor")
	FFloatScoreSettings BlueprintRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * 共享相同 StaticMesh 的 StaticMeshActor 数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings StaticMeshActorSameMeshCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * 需要 AttachParentBounds 的数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Component")
	FIntScoreSettings NeedsAttachParentBoundsCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * 需要 AutoManageAttachment 的数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Audio / Particle")
	FIntScoreSettings NeedsAutoManageAttachmentCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * 需要 Multiple AudioPlayMode 的数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Audio")
	FIntScoreSettings NeedsMultipleAudioPlayModeCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * 材质槽位重复材质数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Material")
	FIntScoreSettings SameMaterialsInMaterialSlotsCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * 覆盖材质数量不匹配评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Material")
	FIntScoreSettings MismatchNumOverrideMaterialCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * 缺失材质数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Material")
	FIntScoreSettings MissingMaterialsCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * 缺失网格数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings MissingMeshesCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * 无 LOD 网格数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings NoLodsMeshCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * 缺失组件的 Actor 数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Component")
	FIntScoreSettings MissingComponentsCountScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * StaticMesh 顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings StaticMeshCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * StaticMesh 硬边顶点数排行评分设置
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings StaticMeshHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * Nanite StaticMesh 顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings StaticMeshNaniteCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * Nanite StaticMesh 硬边顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings StaticMeshNaniteHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * SkeletalMesh 顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings SkeletalMeshCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * SkeletalMesh 硬边顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings SkeletalMeshHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * Nanite SkeletalMesh 顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings SkeletalMeshNaniteCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * Nanite SkeletalMesh 硬边顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings SkeletalMeshNaniteHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * 粒子使用网格顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FIntScoreSettings ParticleMeshCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * 粒子使用网格硬边顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FIntScoreSettings ParticleMeshHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		5000,	10000,	20000,	50000
	};

	/**
	 * SkeletalMesh 骨骼数排行评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FIntScoreSettings BoneCountScoreSettings =
	{//	A,		B,		C,		D,		E
		75,		256,	512,	1024
	};

	/**
	 * 检查 SkeletalMesh 骨骼 LOD 时忽略的骨骼数（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Log|Mesh")
	int32 IgnoreBoneReductionRateBoneCountThreshold = 30;

	/**
	 * SkeletalMesh 骨骼 LOD 比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Mesh")
	FFloatScoreSettings BoneReductionRateScoreSettings =
	{//	A,		B,		C,		D,		E
		50,		70,		80,		90
	};

	/**
	 * 粒子使用 Nanite 网格顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FIntScoreSettings ParticleMeshNaniteCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * 粒子使用 Nanite 网格硬边顶点数排行评分设置（顶点）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FIntScoreSettings ParticleMeshNaniteHardEdgeVertexCountScoreSettings =
	{//	A,		B,		C,		D,		E
		500000,	1000000,2000000,5000000
	};

	/**
	 * Niagara Stateful 发射器比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FFloatScoreSettings NiagaraStatefulEmitterRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * Niagara 发射器可优化比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FFloatScoreSettings NiagaraEmitterOptimizationHintsScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * NiagaraSystem 可优化比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Particle")
	FFloatScoreSettings NiagaraSystemOptimizationHintsScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * 半透明材质比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Material")
	FFloatScoreSettings TranslucentMaterialRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * 动态阴影比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Lighting")
	FFloatScoreSettings CastDynamicShadowRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		5,		10,		20,		50
	};

	/**
	 * Movable 光源投射动态阴影数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Lighting")
	FIntScoreSettings MovableLightCastDynamicShadowCountScoreSettings =
	{//	A,		B,		C,		D,		E
		2,		5,		10,		20
	};

	/**
	 * Movable 光源数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Lighting")
	FIntScoreSettings MovableSceneLightCountScoreSettings =
	{//	A,		B,		C,		D,		E
		2,		5,		10,		20
	};

	/**
	 * 重叠数量评分设置（个）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Collision")
	FIntScoreSettings OverlapCountScoreSettings =
	{//	A,		B,		C,		D,		E
		200,	500,	1000,	2000
	};

	/**
	 * NavMesh 比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Navigation")
	FFloatScoreSettings NavMeshRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		50,		60,		70,		80
	};

	/**
	 * 错误 NavMesh 多边形比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Navigation")
	FFloatScoreSettings ErrorNavMeshPolygonsRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		1,		3,		5
	};

	/**
	 * 错误 Brush 多边形比例评分设置（%）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Brush")
	FFloatScoreSettings ErrorBrushPolygonsRatioScoreSettings =
	{//	A,		B,		C,		D,		E
		0,		0,		1,		3
	};

	/**
	 * 后处理像素着色器指令数评分设置（指令）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|PostProcess")
	FIntScoreSettings PostProcessPixelShaderInstructionsScoreSettings =
	{//	A,		B,		C,		D,		E
		100,	200,	300,	500
	};

	/**
	 * 流送压缩纹理尺寸评估阈值
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	ETextureSize StreamingCompressedTextureSizeThreshold = ETextureSize::Size4096;

	/**
	 * 流送未压缩纹理尺寸评估阈值
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	ETextureSize StreamingUncompressedTextureSizeThreshold = ETextureSize::Size2048;

	/**
	 * 超过阈值的流送纹理数量评分设置（张）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	FIntScoreSettings StreamingTextureCountScoreSettings =
	{//	A,		B,		C,		D,		E
		10,		20,		30,		50
	};

	/**
	 * 非流送压缩纹理尺寸评估阈值
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	ETextureSize NonStreamingCompressedTextureSizeThreshold = ETextureSize::Size4096;

	/**
	 * 非流送未压缩纹理尺寸评估阈值
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	ETextureSize NonStreamingUncompressedTextureSizeThreshold = ETextureSize::Size2048;

	/**
	 * 超过阈值的非流送纹理数量评分设置（张）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	FIntScoreSettings NonStreamingTextureCountScoreSettings =
	{//	A,		B,		C,		D,		E
		10,		20,		30,		50
	};

	/**
	 * 超过阈值的当前流送中纹理数量评分设置（张）
	 */
	UPROPERTY(config, EditAnywhere, Category="Score Settings|Texture")
	FIntScoreSettings StreamedInTextureCountScoreSettings =
	{//	A,		B,		C,		D,		E
		10,		20,		30,		50
	};
};
