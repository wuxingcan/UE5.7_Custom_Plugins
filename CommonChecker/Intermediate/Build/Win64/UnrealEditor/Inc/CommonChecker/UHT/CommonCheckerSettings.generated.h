// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CommonCheckerSettings.h"

#ifdef COMMONCHECKER_CommonCheckerSettings_generated_h
#error "CommonCheckerSettings.generated.h already included, missing '#pragma once' in CommonCheckerSettings.h"
#endif
#define COMMONCHECKER_CommonCheckerSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UCommonCheckerSettings ***************************************************
struct Z_Construct_UClass_UCommonCheckerSettings_Statics;
COMMONCHECKER_API UClass* Z_Construct_UClass_UCommonCheckerSettings_NoRegister();

#define FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCommonCheckerSettings(); \
	friend struct ::Z_Construct_UClass_UCommonCheckerSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend COMMONCHECKER_API UClass* ::Z_Construct_UClass_UCommonCheckerSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UCommonCheckerSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CommonChecker"), Z_Construct_UClass_UCommonCheckerSettings_NoRegister) \
	DECLARE_SERIALIZER(UCommonCheckerSettings) \
	static constexpr const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UCommonCheckerSettings(UCommonCheckerSettings&&) = delete; \
	UCommonCheckerSettings(const UCommonCheckerSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(COMMONCHECKER_API, UCommonCheckerSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCommonCheckerSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UCommonCheckerSettings) \
	COMMONCHECKER_API virtual ~UCommonCheckerSettings();


#define FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h_12_PROLOG
#define FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h_15_INCLASS_NO_PURE_DECLS \
	FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UCommonCheckerSettings;

// ********** End Class UCommonCheckerSettings *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
