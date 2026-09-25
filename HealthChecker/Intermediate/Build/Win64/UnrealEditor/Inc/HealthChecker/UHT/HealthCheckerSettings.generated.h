// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HealthCheckerSettings.h"

#ifdef HEALTHCHECKER_HealthCheckerSettings_generated_h
#error "HealthCheckerSettings.generated.h already included, missing '#pragma once' in HealthCheckerSettings.h"
#endif
#define HEALTHCHECKER_HealthCheckerSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UHealthCheckerSettings ***************************************************
struct Z_Construct_UClass_UHealthCheckerSettings_Statics;
HEALTHCHECKER_API UClass* Z_Construct_UClass_UHealthCheckerSettings_NoRegister();

#define FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHealthCheckerSettings(); \
	friend struct ::Z_Construct_UClass_UHealthCheckerSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend HEALTHCHECKER_API UClass* ::Z_Construct_UClass_UHealthCheckerSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UHealthCheckerSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HealthChecker"), Z_Construct_UClass_UHealthCheckerSettings_NoRegister) \
	DECLARE_SERIALIZER(UHealthCheckerSettings) \
	static constexpr const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UHealthCheckerSettings(UHealthCheckerSettings&&) = delete; \
	UHealthCheckerSettings(const UHealthCheckerSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(HEALTHCHECKER_API, UHealthCheckerSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHealthCheckerSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UHealthCheckerSettings) \
	HEALTHCHECKER_API virtual ~UHealthCheckerSettings();


#define FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h_12_PROLOG
#define FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h_15_INCLASS_NO_PURE_DECLS \
	FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UHealthCheckerSettings;

// ********** End Class UHealthCheckerSettings *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
