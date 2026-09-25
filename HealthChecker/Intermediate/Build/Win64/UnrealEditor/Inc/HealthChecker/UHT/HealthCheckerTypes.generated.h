// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HealthCheckerTypes.h"

#ifdef HEALTHCHECKER_HealthCheckerTypes_generated_h
#error "HealthCheckerTypes.generated.h already included, missing '#pragma once' in HealthCheckerTypes.h"
#endif
#define HEALTHCHECKER_HealthCheckerTypes_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FIntScoreSettings *************************************************
struct Z_Construct_UScriptStruct_FIntScoreSettings_Statics;
#define FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerTypes_h_49_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FIntScoreSettings_Statics; \
	HEALTHCHECKER_API static class UScriptStruct* StaticStruct();


struct FIntScoreSettings;
// ********** End ScriptStruct FIntScoreSettings ***************************************************

// ********** Begin ScriptStruct FFloatScoreSettings ***********************************************
struct Z_Construct_UScriptStruct_FFloatScoreSettings_Statics;
#define FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerTypes_h_87_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FFloatScoreSettings_Statics; \
	HEALTHCHECKER_API static class UScriptStruct* StaticStruct();


struct FFloatScoreSettings;
// ********** End ScriptStruct FFloatScoreSettings *************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerTypes_h

// ********** Begin Enum EBitActorCategory *********************************************************
#define FOREACH_ENUM_EBITACTORCATEGORY(op) \
	op(EBitActorCategory::SkeletalMesh) \
	op(EBitActorCategory::StaticMesh) \
	op(EBitActorCategory::Particle) \
	op(EBitActorCategory::Audio) \
	op(EBitActorCategory::Rendering) \
	op(EBitActorCategory::Volume) \
	op(EBitActorCategory::Geometry) \
	op(EBitActorCategory::Gameplay) \
	op(EBitActorCategory::Other) 

enum class EBitActorCategory : int32;
template<> struct TIsUEnumClass<EBitActorCategory> { enum { Value = true }; };
template<> HEALTHCHECKER_NON_ATTRIBUTED_API UEnum* StaticEnum<EBitActorCategory>();
// ********** End Enum EBitActorCategory ***********************************************************

// ********** Begin Enum ETextureSize **************************************************************
#define FOREACH_ENUM_ETEXTURESIZE(op) \
	op(ETextureSize::SizeOver8192) \
	op(ETextureSize::Size4096) \
	op(ETextureSize::Size2048) \
	op(ETextureSize::Size1024) \
	op(ETextureSize::Size512) \
	op(ETextureSize::Size256) \
	op(ETextureSize::Size128) \
	op(ETextureSize::Size64) \
	op(ETextureSize::SizeBelow64) 

enum class ETextureSize;
template<> struct TIsUEnumClass<ETextureSize> { enum { Value = true }; };
template<> HEALTHCHECKER_NON_ATTRIBUTED_API UEnum* StaticEnum<ETextureSize>();
// ********** End Enum ETextureSize ****************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
