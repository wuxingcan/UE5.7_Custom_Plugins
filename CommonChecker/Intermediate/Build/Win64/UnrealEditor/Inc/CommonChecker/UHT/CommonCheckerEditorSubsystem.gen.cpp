// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CommonCheckerEditorSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeCommonCheckerEditorSubsystem() {}

// ********** Begin Cross Module References ********************************************************
COMMONCHECKER_API UClass* Z_Construct_UClass_UCommonCheckerEditorSubsystem();
COMMONCHECKER_API UClass* Z_Construct_UClass_UCommonCheckerEditorSubsystem_NoRegister();
COMMONCHECKER_API UEnum* Z_Construct_UEnum_CommonChecker_ECommonCheckerScope();
EDITORSUBSYSTEM_API UClass* Z_Construct_UClass_UEditorSubsystem();
UPackage* Z_Construct_UPackage__Script_CommonChecker();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum ECommonCheckerScope *******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECommonCheckerScope;
static UEnum* ECommonCheckerScope_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ECommonCheckerScope.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ECommonCheckerScope.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CommonChecker_ECommonCheckerScope, (UObject*)Z_Construct_UPackage__Script_CommonChecker(), TEXT("ECommonCheckerScope"));
	}
	return Z_Registration_Info_UEnum_ECommonCheckerScope.OuterSingleton;
}
template<> COMMONCHECKER_NON_ATTRIBUTED_API UEnum* StaticEnum<ECommonCheckerScope>()
{
	return ECommonCheckerScope_StaticEnum();
}
struct Z_Construct_UEnum_CommonChecker_ECommonCheckerScope_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ContentFolder.DisplayName", "\xe5\x86\x85\xe5\xae\xb9\xe7\x9b\xae\xe5\xbd\x95" },
		{ "ContentFolder.Name", "ECommonCheckerScope::ContentFolder" },
		{ "CurrentLevel.DisplayName", "\xe5\xbd\x93\xe5\x89\x8d\xe5\x85\xb3\xe5\x8d\xa1" },
		{ "CurrentLevel.Name", "ECommonCheckerScope::CurrentLevel" },
		{ "ModuleRelativePath", "Public/CommonCheckerEditorSubsystem.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ECommonCheckerScope::CurrentLevel", (int64)ECommonCheckerScope::CurrentLevel },
		{ "ECommonCheckerScope::ContentFolder", (int64)ECommonCheckerScope::ContentFolder },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_CommonChecker_ECommonCheckerScope_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CommonChecker_ECommonCheckerScope_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_CommonChecker,
	nullptr,
	"ECommonCheckerScope",
	"ECommonCheckerScope",
	Z_Construct_UEnum_CommonChecker_ECommonCheckerScope_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_CommonChecker_ECommonCheckerScope_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_CommonChecker_ECommonCheckerScope_Statics::Enum_MetaDataParams), Z_Construct_UEnum_CommonChecker_ECommonCheckerScope_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_CommonChecker_ECommonCheckerScope()
{
	if (!Z_Registration_Info_UEnum_ECommonCheckerScope.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECommonCheckerScope.InnerSingleton, Z_Construct_UEnum_CommonChecker_ECommonCheckerScope_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ECommonCheckerScope.InnerSingleton;
}
// ********** End Enum ECommonCheckerScope *********************************************************

// ********** Begin Class UCommonCheckerEditorSubsystem Function OpenCommonCheckerSettings *********
struct Z_Construct_UFunction_UCommonCheckerEditorSubsystem_OpenCommonCheckerSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Editor" },
		{ "ModuleRelativePath", "Public/CommonCheckerEditorSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OpenCommonCheckerSettings constinit property declarations *************
// ********** End Function OpenCommonCheckerSettings constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_OpenCommonCheckerSettings_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCommonCheckerEditorSubsystem, nullptr, "OpenCommonCheckerSettings", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_OpenCommonCheckerSettings_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCommonCheckerEditorSubsystem_OpenCommonCheckerSettings_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UCommonCheckerEditorSubsystem_OpenCommonCheckerSettings()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonCheckerEditorSubsystem_OpenCommonCheckerSettings_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCommonCheckerEditorSubsystem::execOpenCommonCheckerSettings)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	UCommonCheckerEditorSubsystem::OpenCommonCheckerSettings();
	P_NATIVE_END;
}
// ********** End Class UCommonCheckerEditorSubsystem Function OpenCommonCheckerSettings ***********

// ********** Begin Class UCommonCheckerEditorSubsystem Function RunCommonChecker ******************
struct Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics
{
	struct CommonCheckerEditorSubsystem_eventRunCommonChecker_Parms
	{
		bool bSkipAutoOpenReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Editor" },
		{ "CPP_Default_bSkipAutoOpenReport", "false" },
		{ "ModuleRelativePath", "Public/CommonCheckerEditorSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RunCommonChecker constinit property declarations **********************
	static void NewProp_bSkipAutoOpenReport_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkipAutoOpenReport;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RunCommonChecker constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RunCommonChecker Property Definitions *********************************
void Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::NewProp_bSkipAutoOpenReport_SetBit(void* Obj)
{
	((CommonCheckerEditorSubsystem_eventRunCommonChecker_Parms*)Obj)->bSkipAutoOpenReport = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::NewProp_bSkipAutoOpenReport = { "bSkipAutoOpenReport", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CommonCheckerEditorSubsystem_eventRunCommonChecker_Parms), &Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::NewProp_bSkipAutoOpenReport_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((CommonCheckerEditorSubsystem_eventRunCommonChecker_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CommonCheckerEditorSubsystem_eventRunCommonChecker_Parms), &Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::NewProp_bSkipAutoOpenReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::PropPointers) < 2048);
// ********** End Function RunCommonChecker Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCommonCheckerEditorSubsystem, nullptr, "RunCommonChecker", 	Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::CommonCheckerEditorSubsystem_eventRunCommonChecker_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::CommonCheckerEditorSubsystem_eventRunCommonChecker_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCommonCheckerEditorSubsystem::execRunCommonChecker)
{
	P_GET_UBOOL(Z_Param_bSkipAutoOpenReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UCommonCheckerEditorSubsystem::RunCommonChecker(Z_Param_bSkipAutoOpenReport);
	P_NATIVE_END;
}
// ********** End Class UCommonCheckerEditorSubsystem Function RunCommonChecker ********************

// ********** Begin Class UCommonCheckerEditorSubsystem Function RunCommonCheckerForFolders ********
struct Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics
{
	struct CommonCheckerEditorSubsystem_eventRunCommonCheckerForFolders_Parms
	{
		TArray<FString> FolderPaths;
		bool bSkipAutoOpenReport;
		ECommonCheckerScope Scope;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Editor" },
		{ "CPP_Default_bSkipAutoOpenReport", "false" },
		{ "CPP_Default_Scope", "CurrentLevel" },
		{ "ModuleRelativePath", "Public/CommonCheckerEditorSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FolderPaths_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RunCommonCheckerForFolders constinit property declarations ************
	static const UECodeGen_Private::FStrPropertyParams NewProp_FolderPaths_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FolderPaths;
	static void NewProp_bSkipAutoOpenReport_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkipAutoOpenReport;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Scope_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Scope;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RunCommonCheckerForFolders constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RunCommonCheckerForFolders Property Definitions ***********************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_FolderPaths_Inner = { "FolderPaths", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_FolderPaths = { "FolderPaths", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CommonCheckerEditorSubsystem_eventRunCommonCheckerForFolders_Parms, FolderPaths), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FolderPaths_MetaData), NewProp_FolderPaths_MetaData) };
void Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_bSkipAutoOpenReport_SetBit(void* Obj)
{
	((CommonCheckerEditorSubsystem_eventRunCommonCheckerForFolders_Parms*)Obj)->bSkipAutoOpenReport = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_bSkipAutoOpenReport = { "bSkipAutoOpenReport", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CommonCheckerEditorSubsystem_eventRunCommonCheckerForFolders_Parms), &Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_bSkipAutoOpenReport_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_Scope_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_Scope = { "Scope", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CommonCheckerEditorSubsystem_eventRunCommonCheckerForFolders_Parms, Scope), Z_Construct_UEnum_CommonChecker_ECommonCheckerScope, METADATA_PARAMS(0, nullptr) }; // 557024008
void Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((CommonCheckerEditorSubsystem_eventRunCommonCheckerForFolders_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CommonCheckerEditorSubsystem_eventRunCommonCheckerForFolders_Parms), &Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_FolderPaths_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_FolderPaths,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_bSkipAutoOpenReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_Scope_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_Scope,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::PropPointers) < 2048);
// ********** End Function RunCommonCheckerForFolders Property Definitions *************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCommonCheckerEditorSubsystem, nullptr, "RunCommonCheckerForFolders", 	Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::CommonCheckerEditorSubsystem_eventRunCommonCheckerForFolders_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::CommonCheckerEditorSubsystem_eventRunCommonCheckerForFolders_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCommonCheckerEditorSubsystem::execRunCommonCheckerForFolders)
{
	P_GET_TARRAY_REF(FString,Z_Param_Out_FolderPaths);
	P_GET_UBOOL(Z_Param_bSkipAutoOpenReport);
	P_GET_ENUM(ECommonCheckerScope,Z_Param_Scope);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UCommonCheckerEditorSubsystem::RunCommonCheckerForFolders(Z_Param_Out_FolderPaths,Z_Param_bSkipAutoOpenReport,ECommonCheckerScope(Z_Param_Scope));
	P_NATIVE_END;
}
// ********** End Class UCommonCheckerEditorSubsystem Function RunCommonCheckerForFolders **********

// ********** Begin Class UCommonCheckerEditorSubsystem ********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UCommonCheckerEditorSubsystem;
UClass* UCommonCheckerEditorSubsystem::GetPrivateStaticClass()
{
	using TClass = UCommonCheckerEditorSubsystem;
	if (!Z_Registration_Info_UClass_UCommonCheckerEditorSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("CommonCheckerEditorSubsystem"),
			Z_Registration_Info_UClass_UCommonCheckerEditorSubsystem.InnerSingleton,
			StaticRegisterNativesUCommonCheckerEditorSubsystem,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UCommonCheckerEditorSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UCommonCheckerEditorSubsystem_NoRegister()
{
	return UCommonCheckerEditorSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCommonCheckerEditorSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "CommonCheckerEditorSubsystem.h" },
		{ "ModuleRelativePath", "Public/CommonCheckerEditorSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UCommonCheckerEditorSubsystem constinit property declarations ************
// ********** End Class UCommonCheckerEditorSubsystem constinit property declarations **************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OpenCommonCheckerSettings"), .Pointer = &UCommonCheckerEditorSubsystem::execOpenCommonCheckerSettings },
		{ .NameUTF8 = UTF8TEXT("RunCommonChecker"), .Pointer = &UCommonCheckerEditorSubsystem::execRunCommonChecker },
		{ .NameUTF8 = UTF8TEXT("RunCommonCheckerForFolders"), .Pointer = &UCommonCheckerEditorSubsystem::execRunCommonCheckerForFolders },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCommonCheckerEditorSubsystem_OpenCommonCheckerSettings, "OpenCommonCheckerSettings" }, // 3069247487
		{ &Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonChecker, "RunCommonChecker" }, // 2046194112
		{ &Z_Construct_UFunction_UCommonCheckerEditorSubsystem_RunCommonCheckerForFolders, "RunCommonCheckerForFolders" }, // 979040496
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCommonCheckerEditorSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UCommonCheckerEditorSubsystem_Statics
UObject* (*const Z_Construct_UClass_UCommonCheckerEditorSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UEditorSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_CommonChecker,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCheckerEditorSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCommonCheckerEditorSubsystem_Statics::ClassParams = {
	&UCommonCheckerEditorSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCheckerEditorSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UCommonCheckerEditorSubsystem_Statics::Class_MetaDataParams)
};
void UCommonCheckerEditorSubsystem::StaticRegisterNativesUCommonCheckerEditorSubsystem()
{
	UClass* Class = UCommonCheckerEditorSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UCommonCheckerEditorSubsystem_Statics::Funcs));
}
UClass* Z_Construct_UClass_UCommonCheckerEditorSubsystem()
{
	if (!Z_Registration_Info_UClass_UCommonCheckerEditorSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCommonCheckerEditorSubsystem.OuterSingleton, Z_Construct_UClass_UCommonCheckerEditorSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCommonCheckerEditorSubsystem.OuterSingleton;
}
UCommonCheckerEditorSubsystem::UCommonCheckerEditorSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UCommonCheckerEditorSubsystem);
UCommonCheckerEditorSubsystem::~UCommonCheckerEditorSubsystem() {}
// ********** End Class UCommonCheckerEditorSubsystem **********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h__Script_CommonChecker_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ECommonCheckerScope_StaticEnum, TEXT("ECommonCheckerScope"), &Z_Registration_Info_UEnum_ECommonCheckerScope, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 557024008U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCommonCheckerEditorSubsystem, UCommonCheckerEditorSubsystem::StaticClass, TEXT("UCommonCheckerEditorSubsystem"), &Z_Registration_Info_UClass_UCommonCheckerEditorSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonCheckerEditorSubsystem), 3629621490U) },
	};
}; // Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h__Script_CommonChecker_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h__Script_CommonChecker_2535573916{
	TEXT("/Script/CommonChecker"),
	Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h__Script_CommonChecker_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h__Script_CommonChecker_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h__Script_CommonChecker_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h__Script_CommonChecker_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
