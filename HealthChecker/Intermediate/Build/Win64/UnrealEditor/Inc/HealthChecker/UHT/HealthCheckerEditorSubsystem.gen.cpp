// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HealthCheckerEditorSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeHealthCheckerEditorSubsystem() {}

// ********** Begin Cross Module References ********************************************************
EDITORSUBSYSTEM_API UClass* Z_Construct_UClass_UEditorSubsystem();
HEALTHCHECKER_API UClass* Z_Construct_UClass_UHealthCheckerEditorSubsystem();
HEALTHCHECKER_API UClass* Z_Construct_UClass_UHealthCheckerEditorSubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_HealthChecker();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UHealthCheckerEditorSubsystem Function OpenHealthCheckerSettings *********
struct Z_Construct_UFunction_UHealthCheckerEditorSubsystem_OpenHealthCheckerSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Editor" },
		{ "ModuleRelativePath", "Public/HealthCheckerEditorSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OpenHealthCheckerSettings constinit property declarations *************
// ********** End Function OpenHealthCheckerSettings constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthCheckerEditorSubsystem_OpenHealthCheckerSettings_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHealthCheckerEditorSubsystem, nullptr, "OpenHealthCheckerSettings", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthCheckerEditorSubsystem_OpenHealthCheckerSettings_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthCheckerEditorSubsystem_OpenHealthCheckerSettings_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UHealthCheckerEditorSubsystem_OpenHealthCheckerSettings()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthCheckerEditorSubsystem_OpenHealthCheckerSettings_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHealthCheckerEditorSubsystem::execOpenHealthCheckerSettings)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	UHealthCheckerEditorSubsystem::OpenHealthCheckerSettings();
	P_NATIVE_END;
}
// ********** End Class UHealthCheckerEditorSubsystem Function OpenHealthCheckerSettings ***********

// ********** Begin Class UHealthCheckerEditorSubsystem Function RunHealthChecker ******************
struct Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics
{
	struct HealthCheckerEditorSubsystem_eventRunHealthChecker_Parms
	{
		bool bSkipAutoOpenReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Editor" },
		{ "CPP_Default_bSkipAutoOpenReport", "false" },
		{ "ModuleRelativePath", "Public/HealthCheckerEditorSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RunHealthChecker constinit property declarations **********************
	static void NewProp_bSkipAutoOpenReport_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkipAutoOpenReport;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RunHealthChecker constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RunHealthChecker Property Definitions *********************************
void Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::NewProp_bSkipAutoOpenReport_SetBit(void* Obj)
{
	((HealthCheckerEditorSubsystem_eventRunHealthChecker_Parms*)Obj)->bSkipAutoOpenReport = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::NewProp_bSkipAutoOpenReport = { "bSkipAutoOpenReport", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(HealthCheckerEditorSubsystem_eventRunHealthChecker_Parms), &Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::NewProp_bSkipAutoOpenReport_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((HealthCheckerEditorSubsystem_eventRunHealthChecker_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(HealthCheckerEditorSubsystem_eventRunHealthChecker_Parms), &Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::NewProp_bSkipAutoOpenReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::PropPointers) < 2048);
// ********** End Function RunHealthChecker Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHealthCheckerEditorSubsystem, nullptr, "RunHealthChecker", 	Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::HealthCheckerEditorSubsystem_eventRunHealthChecker_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::HealthCheckerEditorSubsystem_eventRunHealthChecker_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHealthCheckerEditorSubsystem::execRunHealthChecker)
{
	P_GET_UBOOL(Z_Param_bSkipAutoOpenReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UHealthCheckerEditorSubsystem::RunHealthChecker(Z_Param_bSkipAutoOpenReport);
	P_NATIVE_END;
}
// ********** End Class UHealthCheckerEditorSubsystem Function RunHealthChecker ********************

// ********** Begin Class UHealthCheckerEditorSubsystem ********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UHealthCheckerEditorSubsystem;
UClass* UHealthCheckerEditorSubsystem::GetPrivateStaticClass()
{
	using TClass = UHealthCheckerEditorSubsystem;
	if (!Z_Registration_Info_UClass_UHealthCheckerEditorSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("HealthCheckerEditorSubsystem"),
			Z_Registration_Info_UClass_UHealthCheckerEditorSubsystem.InnerSingleton,
			StaticRegisterNativesUHealthCheckerEditorSubsystem,
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
	return Z_Registration_Info_UClass_UHealthCheckerEditorSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UHealthCheckerEditorSubsystem_NoRegister()
{
	return UHealthCheckerEditorSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UHealthCheckerEditorSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "HealthCheckerEditorSubsystem.h" },
		{ "ModuleRelativePath", "Public/HealthCheckerEditorSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UHealthCheckerEditorSubsystem constinit property declarations ************
// ********** End Class UHealthCheckerEditorSubsystem constinit property declarations **************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OpenHealthCheckerSettings"), .Pointer = &UHealthCheckerEditorSubsystem::execOpenHealthCheckerSettings },
		{ .NameUTF8 = UTF8TEXT("RunHealthChecker"), .Pointer = &UHealthCheckerEditorSubsystem::execRunHealthChecker },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UHealthCheckerEditorSubsystem_OpenHealthCheckerSettings, "OpenHealthCheckerSettings" }, // 2233548466
		{ &Z_Construct_UFunction_UHealthCheckerEditorSubsystem_RunHealthChecker, "RunHealthChecker" }, // 3406082222
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHealthCheckerEditorSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UHealthCheckerEditorSubsystem_Statics
UObject* (*const Z_Construct_UClass_UHealthCheckerEditorSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UEditorSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_HealthChecker,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthCheckerEditorSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UHealthCheckerEditorSubsystem_Statics::ClassParams = {
	&UHealthCheckerEditorSubsystem::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthCheckerEditorSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UHealthCheckerEditorSubsystem_Statics::Class_MetaDataParams)
};
void UHealthCheckerEditorSubsystem::StaticRegisterNativesUHealthCheckerEditorSubsystem()
{
	UClass* Class = UHealthCheckerEditorSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UHealthCheckerEditorSubsystem_Statics::Funcs));
}
UClass* Z_Construct_UClass_UHealthCheckerEditorSubsystem()
{
	if (!Z_Registration_Info_UClass_UHealthCheckerEditorSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHealthCheckerEditorSubsystem.OuterSingleton, Z_Construct_UClass_UHealthCheckerEditorSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UHealthCheckerEditorSubsystem.OuterSingleton;
}
UHealthCheckerEditorSubsystem::UHealthCheckerEditorSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UHealthCheckerEditorSubsystem);
UHealthCheckerEditorSubsystem::~UHealthCheckerEditorSubsystem() {}
// ********** End Class UHealthCheckerEditorSubsystem **********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerEditorSubsystem_h__Script_HealthChecker_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UHealthCheckerEditorSubsystem, UHealthCheckerEditorSubsystem::StaticClass, TEXT("UHealthCheckerEditorSubsystem"), &Z_Registration_Info_UClass_UHealthCheckerEditorSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHealthCheckerEditorSubsystem), 1869069897U) },
	};
}; // Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerEditorSubsystem_h__Script_HealthChecker_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerEditorSubsystem_h__Script_HealthChecker_955727295{
	TEXT("/Script/HealthChecker"),
	Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerEditorSubsystem_h__Script_HealthChecker_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerEditorSubsystem_h__Script_HealthChecker_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
