// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CommonCheckerTypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef COMMONCHECKER_CommonCheckerTypes_generated_h
#error "CommonCheckerTypes.generated.h already included, missing '#pragma once' in CommonCheckerTypes.h"
#endif
#define COMMONCHECKER_CommonCheckerTypes_generated_h

#define FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerTypes_h_49_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FIntScoreSettings_Statics; \
	COMMONCHECKER_API static class UScriptStruct* StaticStruct();


template<> COMMONCHECKER_API UScriptStruct* StaticStruct<struct FIntScoreSettings>();

#define FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerTypes_h_87_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFloatScoreSettings_Statics; \
	COMMONCHECKER_API static class UScriptStruct* StaticStruct();


template<> COMMONCHECKER_API UScriptStruct* StaticStruct<struct FFloatScoreSettings>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerTypes_h


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
template<> COMMONCHECKER_API UEnum* StaticEnum<EBitActorCategory>();

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
template<> COMMONCHECKER_API UEnum* StaticEnum<ETextureSize>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
