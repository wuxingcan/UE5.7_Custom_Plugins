// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HealthCheckerTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeHealthCheckerTypes() {}

// ********** Begin Cross Module References ********************************************************
HEALTHCHECKER_API UEnum* Z_Construct_UEnum_HealthChecker_EBitActorCategory();
HEALTHCHECKER_API UEnum* Z_Construct_UEnum_HealthChecker_ETextureSize();
HEALTHCHECKER_API UScriptStruct* Z_Construct_UScriptStruct_FFloatScoreSettings();
HEALTHCHECKER_API UScriptStruct* Z_Construct_UScriptStruct_FIntScoreSettings();
UPackage* Z_Construct_UPackage__Script_HealthChecker();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EBitActorCategory *********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBitActorCategory;
static UEnum* EBitActorCategory_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBitActorCategory.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBitActorCategory.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_HealthChecker_EBitActorCategory, (UObject*)Z_Construct_UPackage__Script_HealthChecker(), TEXT("EBitActorCategory"));
	}
	return Z_Registration_Info_UEnum_EBitActorCategory.OuterSingleton;
}
template<> HEALTHCHECKER_NON_ATTRIBUTED_API UEnum* StaticEnum<EBitActorCategory>()
{
	return EBitActorCategory_StaticEnum();
}
struct Z_Construct_UEnum_HealthChecker_EBitActorCategory_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Audio.DisplayName", "Audio" },
		{ "Audio.Name", "EBitActorCategory::Audio" },
		{ "Bitflags", "" },
		{ "Gameplay.DisplayName", "Gameplay" },
		{ "Gameplay.Name", "EBitActorCategory::Gameplay" },
		{ "Geometry.DisplayName", "Geometry" },
		{ "Geometry.Name", "EBitActorCategory::Geometry" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
		{ "Other.DisplayName", "Other" },
		{ "Other.Name", "EBitActorCategory::Other" },
		{ "Particle.DisplayName", "Particle" },
		{ "Particle.Name", "EBitActorCategory::Particle" },
		{ "Rendering.DisplayName", "Rendering" },
		{ "Rendering.Name", "EBitActorCategory::Rendering" },
		{ "SkeletalMesh.DisplayName", "Skeletal Mesh" },
		{ "SkeletalMesh.Name", "EBitActorCategory::SkeletalMesh" },
		{ "StaticMesh.DisplayName", "Static Mesh" },
		{ "StaticMesh.Name", "EBitActorCategory::StaticMesh" },
		{ "UseEnumValuesAsMaskValuesInEditor", "true" },
		{ "Volume.DisplayName", "Volume" },
		{ "Volume.Name", "EBitActorCategory::Volume" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBitActorCategory::SkeletalMesh", (int64)EBitActorCategory::SkeletalMesh },
		{ "EBitActorCategory::StaticMesh", (int64)EBitActorCategory::StaticMesh },
		{ "EBitActorCategory::Particle", (int64)EBitActorCategory::Particle },
		{ "EBitActorCategory::Audio", (int64)EBitActorCategory::Audio },
		{ "EBitActorCategory::Rendering", (int64)EBitActorCategory::Rendering },
		{ "EBitActorCategory::Volume", (int64)EBitActorCategory::Volume },
		{ "EBitActorCategory::Geometry", (int64)EBitActorCategory::Geometry },
		{ "EBitActorCategory::Gameplay", (int64)EBitActorCategory::Gameplay },
		{ "EBitActorCategory::Other", (int64)EBitActorCategory::Other },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_HealthChecker_EBitActorCategory_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_HealthChecker_EBitActorCategory_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_HealthChecker,
	nullptr,
	"EBitActorCategory",
	"EBitActorCategory",
	Z_Construct_UEnum_HealthChecker_EBitActorCategory_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_HealthChecker_EBitActorCategory_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_HealthChecker_EBitActorCategory_Statics::Enum_MetaDataParams), Z_Construct_UEnum_HealthChecker_EBitActorCategory_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_HealthChecker_EBitActorCategory()
{
	if (!Z_Registration_Info_UEnum_EBitActorCategory.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBitActorCategory.InnerSingleton, Z_Construct_UEnum_HealthChecker_EBitActorCategory_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBitActorCategory.InnerSingleton;
}
// ********** End Enum EBitActorCategory ***********************************************************

// ********** Begin Enum ETextureSize **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ETextureSize;
static UEnum* ETextureSize_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ETextureSize.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ETextureSize.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_HealthChecker_ETextureSize, (UObject*)Z_Construct_UPackage__Script_HealthChecker(), TEXT("ETextureSize"));
	}
	return Z_Registration_Info_UEnum_ETextureSize.OuterSingleton;
}
template<> HEALTHCHECKER_NON_ATTRIBUTED_API UEnum* StaticEnum<ETextureSize>()
{
	return ETextureSize_StaticEnum();
}
struct Z_Construct_UEnum_HealthChecker_ETextureSize_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "MAX.Hidden", "" },
		{ "MAX.Name", "ETextureSize::MAX" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
		{ "Size1024.DisplayName", "Size 1K" },
		{ "Size1024.Name", "ETextureSize::Size1024" },
		{ "Size128.DisplayName", "Size 128x128" },
		{ "Size128.Name", "ETextureSize::Size128" },
		{ "Size2048.DisplayName", "Size 2K" },
		{ "Size2048.Name", "ETextureSize::Size2048" },
		{ "Size256.DisplayName", "Size 256x256" },
		{ "Size256.Name", "ETextureSize::Size256" },
		{ "Size4096.DisplayName", "Size 4K" },
		{ "Size4096.Name", "ETextureSize::Size4096" },
		{ "Size512.DisplayName", "Size 512x512" },
		{ "Size512.Name", "ETextureSize::Size512" },
		{ "Size64.DisplayName", "Size 64x64" },
		{ "Size64.Name", "ETextureSize::Size64" },
		{ "SizeBelow64.DisplayName", "Size below 64x64" },
		{ "SizeBelow64.Name", "ETextureSize::SizeBelow64" },
		{ "SizeOver8192.DisplayName", "Size over 8K" },
		{ "SizeOver8192.Name", "ETextureSize::SizeOver8192" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ETextureSize::SizeOver8192", (int64)ETextureSize::SizeOver8192 },
		{ "ETextureSize::Size4096", (int64)ETextureSize::Size4096 },
		{ "ETextureSize::Size2048", (int64)ETextureSize::Size2048 },
		{ "ETextureSize::Size1024", (int64)ETextureSize::Size1024 },
		{ "ETextureSize::Size512", (int64)ETextureSize::Size512 },
		{ "ETextureSize::Size256", (int64)ETextureSize::Size256 },
		{ "ETextureSize::Size128", (int64)ETextureSize::Size128 },
		{ "ETextureSize::Size64", (int64)ETextureSize::Size64 },
		{ "ETextureSize::SizeBelow64", (int64)ETextureSize::SizeBelow64 },
		{ "ETextureSize::MAX", (int64)ETextureSize::MAX },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_HealthChecker_ETextureSize_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_HealthChecker_ETextureSize_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_HealthChecker,
	nullptr,
	"ETextureSize",
	"ETextureSize",
	Z_Construct_UEnum_HealthChecker_ETextureSize_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_HealthChecker_ETextureSize_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_HealthChecker_ETextureSize_Statics::Enum_MetaDataParams), Z_Construct_UEnum_HealthChecker_ETextureSize_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_HealthChecker_ETextureSize()
{
	if (!Z_Registration_Info_UEnum_ETextureSize.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ETextureSize.InnerSingleton, Z_Construct_UEnum_HealthChecker_ETextureSize_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ETextureSize.InnerSingleton;
}
// ********** End Enum ETextureSize ****************************************************************

// ********** Begin ScriptStruct FIntScoreSettings *************************************************
struct Z_Construct_UScriptStruct_FIntScoreSettings_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FIntScoreSettings); }
	static inline consteval int16 GetStructAlignment() { return alignof(FIntScoreSettings); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "EditCondition", "bAllowHealthCheck" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "EditCondition", "bAllowHealthCheck" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_C_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "EditCondition", "bAllowHealthCheck" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_D_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "EditCondition", "bAllowHealthCheck" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScoreWeight_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "EditCondition", "bAllowHealthCheck" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAllowHealthCheck_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FIntScoreSettings constinit property declarations *****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_A;
	static const UECodeGen_Private::FIntPropertyParams NewProp_B;
	static const UECodeGen_Private::FIntPropertyParams NewProp_C;
	static const UECodeGen_Private::FIntPropertyParams NewProp_D;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScoreWeight;
	static void NewProp_bAllowHealthCheck_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAllowHealthCheck;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FIntScoreSettings constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FIntScoreSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FIntScoreSettings_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FIntScoreSettings;
class UScriptStruct* FIntScoreSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FIntScoreSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FIntScoreSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FIntScoreSettings, (UObject*)Z_Construct_UPackage__Script_HealthChecker(), TEXT("IntScoreSettings"));
	}
	return Z_Registration_Info_UScriptStruct_FIntScoreSettings.OuterSingleton;
	}

// ********** Begin ScriptStruct FIntScoreSettings Property Definitions ****************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FIntScoreSettings, A), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_A_MetaData), NewProp_A_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FIntScoreSettings, B), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_B_MetaData), NewProp_B_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_C = { "C", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FIntScoreSettings, C), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_C_MetaData), NewProp_C_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_D = { "D", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FIntScoreSettings, D), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_D_MetaData), NewProp_D_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_ScoreWeight = { "ScoreWeight", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FIntScoreSettings, ScoreWeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScoreWeight_MetaData), NewProp_ScoreWeight_MetaData) };
void Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_bAllowHealthCheck_SetBit(void* Obj)
{
	((FIntScoreSettings*)Obj)->bAllowHealthCheck = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_bAllowHealthCheck = { "bAllowHealthCheck", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FIntScoreSettings), &Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_bAllowHealthCheck_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAllowHealthCheck_MetaData), NewProp_bAllowHealthCheck_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FIntScoreSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_A,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_B,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_C,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_D,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_ScoreWeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewProp_bAllowHealthCheck,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FIntScoreSettings_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FIntScoreSettings Property Definitions ******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FIntScoreSettings_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_HealthChecker,
	nullptr,
	&NewStructOps,
	"IntScoreSettings",
	Z_Construct_UScriptStruct_FIntScoreSettings_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FIntScoreSettings_Statics::PropPointers),
	sizeof(FIntScoreSettings),
	alignof(FIntScoreSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FIntScoreSettings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FIntScoreSettings_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FIntScoreSettings()
{
	if (!Z_Registration_Info_UScriptStruct_FIntScoreSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FIntScoreSettings.InnerSingleton, Z_Construct_UScriptStruct_FIntScoreSettings_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FIntScoreSettings.InnerSingleton);
}
// ********** End ScriptStruct FIntScoreSettings ***************************************************

// ********** Begin ScriptStruct FFloatScoreSettings ***********************************************
struct Z_Construct_UScriptStruct_FFloatScoreSettings_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FFloatScoreSettings); }
	static inline consteval int16 GetStructAlignment() { return alignof(FFloatScoreSettings); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "EditCondition", "bAllowHealthCheck" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "EditCondition", "bAllowHealthCheck" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_C_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "EditCondition", "bAllowHealthCheck" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_D_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "EditCondition", "bAllowHealthCheck" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScoreWeight_MetaData[] = {
		{ "Category", "Score Settings" },
		{ "EditCondition", "bAllowHealthCheck" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAllowHealthCheck_MetaData[] = {
		{ "Category", "Enabled" },
		{ "ModuleRelativePath", "Public/HealthCheckerTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FFloatScoreSettings constinit property declarations ***************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_A;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_B;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_C;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_D;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScoreWeight;
	static void NewProp_bAllowHealthCheck_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAllowHealthCheck;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FFloatScoreSettings constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFloatScoreSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FFloatScoreSettings_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FFloatScoreSettings;
class UScriptStruct* FFloatScoreSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FFloatScoreSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FFloatScoreSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFloatScoreSettings, (UObject*)Z_Construct_UPackage__Script_HealthChecker(), TEXT("FloatScoreSettings"));
	}
	return Z_Registration_Info_UScriptStruct_FFloatScoreSettings.OuterSingleton;
	}

// ********** Begin ScriptStruct FFloatScoreSettings Property Definitions **************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFloatScoreSettings, A), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_A_MetaData), NewProp_A_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFloatScoreSettings, B), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_B_MetaData), NewProp_B_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_C = { "C", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFloatScoreSettings, C), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_C_MetaData), NewProp_C_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_D = { "D", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFloatScoreSettings, D), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_D_MetaData), NewProp_D_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_ScoreWeight = { "ScoreWeight", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFloatScoreSettings, ScoreWeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScoreWeight_MetaData), NewProp_ScoreWeight_MetaData) };
void Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_bAllowHealthCheck_SetBit(void* Obj)
{
	((FFloatScoreSettings*)Obj)->bAllowHealthCheck = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_bAllowHealthCheck = { "bAllowHealthCheck", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FFloatScoreSettings), &Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_bAllowHealthCheck_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAllowHealthCheck_MetaData), NewProp_bAllowHealthCheck_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_A,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_B,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_C,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_D,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_ScoreWeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewProp_bAllowHealthCheck,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FFloatScoreSettings Property Definitions ****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_HealthChecker,
	nullptr,
	&NewStructOps,
	"FloatScoreSettings",
	Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::PropPointers),
	sizeof(FFloatScoreSettings),
	alignof(FFloatScoreSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FFloatScoreSettings()
{
	if (!Z_Registration_Info_UScriptStruct_FFloatScoreSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FFloatScoreSettings.InnerSingleton, Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FFloatScoreSettings.InnerSingleton);
}
// ********** End ScriptStruct FFloatScoreSettings *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerTypes_h__Script_HealthChecker_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EBitActorCategory_StaticEnum, TEXT("EBitActorCategory"), &Z_Registration_Info_UEnum_EBitActorCategory, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1218939238U) },
		{ ETextureSize_StaticEnum, TEXT("ETextureSize"), &Z_Registration_Info_UEnum_ETextureSize, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2879030143U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FIntScoreSettings::StaticStruct, Z_Construct_UScriptStruct_FIntScoreSettings_Statics::NewStructOps, TEXT("IntScoreSettings"),&Z_Registration_Info_UScriptStruct_FIntScoreSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FIntScoreSettings), 4132731704U) },
		{ FFloatScoreSettings::StaticStruct, Z_Construct_UScriptStruct_FFloatScoreSettings_Statics::NewStructOps, TEXT("FloatScoreSettings"),&Z_Registration_Info_UScriptStruct_FFloatScoreSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFloatScoreSettings), 3227664396U) },
	};
}; // Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerTypes_h__Script_HealthChecker_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerTypes_h__Script_HealthChecker_665206624{
	TEXT("/Script/HealthChecker"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerTypes_h__Script_HealthChecker_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerTypes_h__Script_HealthChecker_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerTypes_h__Script_HealthChecker_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerTypes_h__Script_HealthChecker_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
