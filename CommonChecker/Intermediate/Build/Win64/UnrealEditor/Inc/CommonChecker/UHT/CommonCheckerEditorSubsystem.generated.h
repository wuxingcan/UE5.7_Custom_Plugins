// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CommonCheckerEditorSubsystem.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class ECommonCheckerScope : uint8;
#ifdef COMMONCHECKER_CommonCheckerEditorSubsystem_generated_h
#error "CommonCheckerEditorSubsystem.generated.h already included, missing '#pragma once' in CommonCheckerEditorSubsystem.h"
#endif
#define COMMONCHECKER_CommonCheckerEditorSubsystem_generated_h

#define FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execRunCommonCheckerForFolders); \
	DECLARE_FUNCTION(execRunCommonChecker); \
	DECLARE_FUNCTION(execOpenCommonCheckerSettings);


#define FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCommonCheckerEditorSubsystem(); \
	friend struct Z_Construct_UClass_UCommonCheckerEditorSubsystem_Statics; \
public: \
	DECLARE_CLASS(UCommonCheckerEditorSubsystem, UEditorSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonChecker"), NO_API) \
	DECLARE_SERIALIZER(UCommonCheckerEditorSubsystem)


#define FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h_21_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCommonCheckerEditorSubsystem(); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UCommonCheckerEditorSubsystem(UCommonCheckerEditorSubsystem&&); \
	UCommonCheckerEditorSubsystem(const UCommonCheckerEditorSubsystem&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCommonCheckerEditorSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCommonCheckerEditorSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UCommonCheckerEditorSubsystem) \
	NO_API virtual ~UCommonCheckerEditorSubsystem();


#define FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h_18_PROLOG
#define FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h_21_INCLASS_NO_PURE_DECLS \
	FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COMMONCHECKER_API UClass* StaticClass<class UCommonCheckerEditorSubsystem>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_workspace_code_cpp_ue_5_5_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerEditorSubsystem_h


#define FOREACH_ENUM_ECOMMONCHECKERSCOPE(op) \
	op(ECommonCheckerScope::CurrentLevel) \
	op(ECommonCheckerScope::ContentFolder) 

enum class ECommonCheckerScope : uint8;
template<> struct TIsUEnumClass<ECommonCheckerScope> { enum { Value = true }; };
template<> COMMONCHECKER_API UEnum* StaticEnum<ECommonCheckerScope>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
