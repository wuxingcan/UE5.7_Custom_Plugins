// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CommonCheckerSettings.h"
#include "CommonCheckerTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeCommonCheckerSettings() {}

// ********** Begin Cross Module References ********************************************************
COMMONCHECKER_API UClass* Z_Construct_UClass_UCommonCheckerSettings();
COMMONCHECKER_API UClass* Z_Construct_UClass_UCommonCheckerSettings_NoRegister();
COMMONCHECKER_API UEnum* Z_Construct_UEnum_CommonChecker_ETextureSize();
COMMONCHECKER_API UScriptStruct* Z_Construct_UScriptStruct_FFloatScoreSettings();
COMMONCHECKER_API UScriptStruct* Z_Construct_UScriptStruct_FIntScoreSettings();
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
UPackage* Z_Construct_UPackage__Script_CommonChecker();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UCommonCheckerSettings ***************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UCommonCheckerSettings;
UClass* UCommonCheckerSettings::GetPrivateStaticClass()
{
	using TClass = UCommonCheckerSettings;
	if (!Z_Registration_Info_UClass_UCommonCheckerSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("CommonCheckerSettings"),
			Z_Registration_Info_UClass_UCommonCheckerSettings.InnerSingleton,
			StaticRegisterNativesUCommonCheckerSettings,
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
	return Z_Registration_Info_UClass_UCommonCheckerSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UCommonCheckerSettings_NoRegister()
{
	return UCommonCheckerSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCommonCheckerSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Settings for Common Checker\n */" },
#endif
		{ "DisplayName", "Common Checker" },
		{ "IncludePath", "CommonCheckerSettings.h" },
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Settings for Common Checker" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUnloadLevelsAfterCheck_MetaData[] = {
		{ "Category", "Common Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe8\xbf\x90\xe8\xa1\x8c CommonChecker \xe5\x90\x8e\xe5\x8d\xb8\xe8\xbd\xbd\xe5\x85\xb3\xe5\x8d\xa1\xe5\x92\x8c WorldPartition \xe5\x8d\x95\xe5\x85\x83\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xbf\x90\xe8\xa1\x8c CommonChecker \xe5\x90\x8e\xe5\x8d\xb8\xe8\xbd\xbd\xe5\x85\xb3\xe5\x8d\xa1\xe5\x92\x8c WorldPartition \xe5\x8d\x95\xe5\x85\x83" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIgnoreEditorOnlyActorsAndComponents_MetaData[] = {
		{ "Category", "Common Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\xbf\xbd\xe7\x95\xa5 EditorOnly \xe7\x9a\x84 Actor \xe5\x92\x8c Component\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbf\xbd\xe7\x95\xa5 EditorOnly \xe7\x9a\x84 Actor \xe5\x92\x8c Component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPostToMapCheck_MetaData[] = {
		{ "Category", "Common Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\xb0\x86\xe8\xad\xa6\xe5\x91\x8a\xe5\x8f\x91\xe9\x80\x81\xe5\x88\xb0 MapCheck \xe7\xaa\x97\xe5\x8f\xa3\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb0\x86\xe8\xad\xa6\xe5\x91\x8a\xe5\x8f\x91\xe9\x80\x81\xe5\x88\xb0 MapCheck \xe7\xaa\x97\xe5\x8f\xa3" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPostToLog_MetaData[] = {
		{ "Category", "Common Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\xb0\x86\xe8\xad\xa6\xe5\x91\x8a\xe5\x8f\x91\xe9\x80\x81\xe5\x88\xb0\xe8\xbe\x93\xe5\x87\xba\xe6\x97\xa5\xe5\xbf\x97\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb0\x86\xe8\xad\xa6\xe5\x91\x8a\xe5\x8f\x91\xe9\x80\x81\xe5\x88\xb0\xe8\xbe\x93\xe5\x87\xba\xe6\x97\xa5\xe5\xbf\x97" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOpenReportWhenFinished_MetaData[] = {
		{ "Category", "Common Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\xae\x8c\xe6\x88\x90\xe5\x90\x8e\xe6\x89\x93\xe5\xbc\x80\xe6\x8a\xa5\xe5\x91\x8a\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xae\x8c\xe6\x88\x90\xe5\x90\x8e\xe6\x89\x93\xe5\xbc\x80\xe6\x8a\xa5\xe5\x91\x8a" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOpenMapCheckWhenFinished_MetaData[] = {
		{ "Category", "Common Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\xae\x8c\xe6\x88\x90\xe5\x90\x8e\xe6\x89\x93\xe5\xbc\x80 MapCheck \xe7\xaa\x97\xe5\x8f\xa3\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xae\x8c\xe6\x88\x90\xe5\x90\x8e\xe6\x89\x93\xe5\xbc\x80 MapCheck \xe7\xaa\x97\xe5\x8f\xa3" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseUserNameInReport_MetaData[] = {
		{ "Category", "Common Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x9c\xa8\xe6\x8a\xa5\xe5\x91\x8a\xe4\xb8\xad\xe5\x8c\x85\xe5\x90\xab\xe7\x94\xa8\xe6\x88\xb7\xe5\x90\x8d\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9c\xa8\xe6\x8a\xa5\xe5\x91\x8a\xe4\xb8\xad\xe5\x8c\x85\xe5\x90\xab\xe7\x94\xa8\xe6\x88\xb7\xe5\x90\x8d" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAddEngineVersionToSearchHints_MetaData[] = {
		{ "Category", "Common Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x9c\xa8\xe6\x90\x9c\xe7\xb4\xa2\xe6\x8f\x90\xe7\xa4\xba\xe4\xb8\xad\xe9\x99\x84\xe5\x8a\xa0\xe5\xbc\x95\xe6\x93\x8e\xe7\x89\x88\xe6\x9c\xac\xe4\xbf\xa1\xe6\x81\xaf\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9c\xa8\xe6\x90\x9c\xe7\xb4\xa2\xe6\x8f\x90\xe7\xa4\xba\xe4\xb8\xad\xe9\x99\x84\xe5\x8a\xa0\xe5\xbc\x95\xe6\x93\x8e\xe7\x89\x88\xe6\x9c\xac\xe4\xbf\xa1\xe6\x81\xaf" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReportActorCategories_MetaData[] = {
		{ "Bitmask", "" },
		{ "BitmaskEnum", "/Script/CommonChecker.EBitActorCategory" },
		{ "Category", "Common Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x8a\xa5\xe5\x91\x8a\xe4\xb8\xad\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 Actor \xe7\xb1\xbb\xe5\x88\xab\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x8a\xa5\xe5\x91\x8a\xe4\xb8\xad\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 Actor \xe7\xb1\xbb\xe5\x88\xab" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayMapLoadTimeRanking_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x9c\xb0\xe5\x9b\xbe\xe5\x8a\xa0\xe8\xbd\xbd\xe6\x97\xb6\xe9\x97\xb4\xe6\x8e\x92\xe8\xa1\x8c\xe4\xb8\xad\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe6\x9d\xa1\xe7\x9b\xae\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9c\xb0\xe5\x9b\xbe\xe5\x8a\xa0\xe8\xbd\xbd\xe6\x97\xb6\xe9\x97\xb4\xe6\x8e\x92\xe8\xa1\x8c\xe4\xb8\xad\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe6\x9d\xa1\xe7\x9b\xae\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningAttachParentBoundsScale_MetaData[] = {
		{ "Category", "MapCheck|Component" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba AttachParentBounds \xe8\xad\xa6\xe5\x91\x8a\xe6\x97\xb6\xe4\xbd\xbf\xe7\x94\xa8\xe7\x9a\x84\xe5\x8c\x85\xe5\x9b\xb4\xe7\x9b\x92\xe7\xbc\xa9\xe6\x94\xbe\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba AttachParentBounds \xe8\xad\xa6\xe5\x91\x8a\xe6\x97\xb6\xe4\xbd\xbf\xe7\x94\xa8\xe7\x9a\x84\xe5\x8c\x85\xe5\x9b\xb4\xe7\x9b\x92\xe7\xbc\xa9\xe6\x94\xbe" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayNeedsAttachParentBounds_MetaData[] = {
		{ "Category", "Log|Component" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 AttachParentBounds \xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 AttachParentBounds \xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayNeedsAutoManageAttachment_MetaData[] = {
		{ "Category", "Log|Audio / Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 AutoManageAttachment \xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 AutoManageAttachment \xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayNeedsAudioPlayMode_MetaData[] = {
		{ "Category", "Log|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 AudioPlayMode \xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 AudioPlayMode \xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayStaticMeshActorSameMesh_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe5\x85\xb1\xe4\xba\xab\xe7\x9b\xb8\xe5\x90\x8c StaticMesh \xe7\x9a\x84 StaticMeshActor \xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe5\x85\xb1\xe4\xba\xab\xe7\x9b\xb8\xe5\x90\x8c StaticMesh \xe7\x9a\x84 StaticMeshActor \xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\xbc\x80\xe5\x90\xaf\xe5\x8a\xa8\xe6\x80\x81\xe5\xae\x9e\xe4\xbe\x8b\xe5\x8c\x96\xe6\x97\xb6\xef\xbc\x8c\xe5\xbf\xbd\xe7\x95\xa5\xe5\x85\xb1\xe4\xba\xab\xe7\x9b\xb8\xe5\x90\x8c StaticMesh \xe7\x9a\x84 StaticMeshActor \xe8\xad\xa6\xe5\x91\x8a\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbc\x80\xe5\x90\xaf\xe5\x8a\xa8\xe6\x80\x81\xe5\xae\x9e\xe4\xbe\x8b\xe5\x8c\x96\xe6\x97\xb6\xef\xbc\x8c\xe5\xbf\xbd\xe7\x95\xa5\xe5\x85\xb1\xe4\xba\xab\xe7\x9b\xb8\xe5\x90\x8c StaticMesh \xe7\x9a\x84 StaticMeshActor \xe8\xad\xa6\xe5\x91\x8a" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplaySameMaterialsInMaterialSlots_MetaData[] = {
		{ "Category", "Log|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe6\x9d\x90\xe8\xb4\xa8\xe6\xa7\xbd\xe4\xbd\x8d\xe9\x87\x8d\xe5\xa4\x8d\xe6\x9d\x90\xe8\xb4\xa8\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe6\x9d\x90\xe8\xb4\xa8\xe6\xa7\xbd\xe4\xbd\x8d\xe9\x87\x8d\xe5\xa4\x8d\xe6\x9d\x90\xe8\xb4\xa8\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayMismatchNumOverrideMaterial_MetaData[] = {
		{ "Category", "Log|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe8\xa6\x86\xe7\x9b\x96\xe6\x9d\x90\xe8\xb4\xa8\xe6\x95\xb0\xe9\x87\x8f\xe4\xb8\x8d\xe5\x8c\xb9\xe9\x85\x8d\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe8\xa6\x86\xe7\x9b\x96\xe6\x9d\x90\xe8\xb4\xa8\xe6\x95\xb0\xe9\x87\x8f\xe4\xb8\x8d\xe5\x8c\xb9\xe9\x85\x8d\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayMissingMaterials_MetaData[] = {
		{ "Category", "Log|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe7\xbc\xba\xe5\xa4\xb1\xe6\x9d\x90\xe8\xb4\xa8\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe7\xbc\xba\xe5\xa4\xb1\xe6\x9d\x90\xe8\xb4\xa8\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayMissingMeshes_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe7\xbc\xba\xe5\xa4\xb1\xe7\xbd\x91\xe6\xa0\xbc\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe7\xbc\xba\xe5\xa4\xb1\xe7\xbd\x91\xe6\xa0\xbc\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayNoLodsMeshes_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe7\xbc\xba\xe5\xa4\xb1 LOD \xe7\xbd\x91\xe6\xa0\xbc\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe7\xbc\xba\xe5\xa4\xb1 LOD \xe7\xbd\x91\xe6\xa0\xbc\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayMissingComponents_MetaData[] = {
		{ "Category", "Log|Component" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe7\xbc\xba\xe5\xa4\xb1\xe7\xbb\x84\xe4\xbb\xb6\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe7\xbc\xba\xe5\xa4\xb1\xe7\xbb\x84\xe4\xbb\xb6\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayVertexRanking_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe7\xbd\x91\xe6\xa0\xbc\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe6\x9d\xa1\xe7\x9b\xae\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe7\xbd\x91\xe6\xa0\xbc\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe6\x9d\xa1\xe7\x9b\xae\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayBoneCountRanking_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 SkeletalMesh \xe9\xaa\xa8\xe9\xaa\xbc\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe6\x9d\xa1\xe7\x9b\xae\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 SkeletalMesh \xe9\xaa\xa8\xe9\xaa\xbc\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe6\x9d\xa1\xe7\x9b\xae\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayBoneReductionRateRanking_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 SkeletalMesh \xe9\xaa\xa8\xe9\xaa\xbc LOD \xe6\xaf\x94\xe4\xbe\x8b\xe6\x8e\x92\xe8\xa1\x8c\xe6\x9d\xa1\xe7\x9b\xae\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 SkeletalMesh \xe9\xaa\xa8\xe9\xaa\xbc LOD \xe6\xaf\x94\xe4\xbe\x8b\xe6\x8e\x92\xe8\xa1\x8c\xe6\x9d\xa1\xe7\x9b\xae\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayErrorNavMeshPolygons_MetaData[] = {
		{ "Category", "Log|Navigation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe5\xb5\x8c\xe5\x85\xa5\xe7\x89\xa9\xe4\xbd\x93 NavMesh \xe5\xa4\x9a\xe8\xbe\xb9\xe5\xbd\xa2\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe5\xb5\x8c\xe5\x85\xa5\xe7\x89\xa9\xe4\xbd\x93 NavMesh \xe5\xa4\x9a\xe8\xbe\xb9\xe5\xbd\xa2\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DrawNavMeshPolygonTimer_MetaData[] = {
		{ "Category", "MapCheck|Navigation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe7\xbb\x98\xe5\x88\xb6\xe5\xb5\x8c\xe5\x85\xa5\xe7\x89\xa9\xe4\xbd\x93 NavMesh \xe5\xa4\x9a\xe8\xbe\xb9\xe5\xbd\xa2\xe7\x9a\x84\xe6\x97\xb6\xe9\x97\xb4\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbb\x98\xe5\x88\xb6\xe5\xb5\x8c\xe5\x85\xa5\xe7\x89\xa9\xe4\xbd\x93 NavMesh \xe5\xa4\x9a\xe8\xbe\xb9\xe5\xbd\xa2\xe7\x9a\x84\xe6\x97\xb6\xe9\x97\xb4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayErrorBrushPolygons_MetaData[] = {
		{ "Category", "Log|Brush" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe5\xb8\xa6\xe5\xad\x94 Brush \xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84\xe5\xb8\xa6\xe5\xad\x94 Brush \xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningNiagaraWarmupTime_MetaData[] = {
		{ "Category", "Log|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * NiagaraSystem WarmupTime \xe8\xad\xa6\xe5\x91\x8a\xe9\x98\x88\xe5\x80\xbc\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "NiagaraSystem WarmupTime \xe8\xad\xa6\xe5\x91\x8a\xe9\x98\x88\xe5\x80\xbc\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningNiagaraRendererCount_MetaData[] = {
		{ "Category", "Log|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 NiagaraSystem \xe6\xb8\xb2\xe6\x9f\x93\xe5\x99\xa8\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe7\xa4\xba\xe7\x9a\x84 NiagaraSystem \xe6\xb8\xb2\xe6\x9f\x93\xe5\x99\xa8\xe8\xad\xa6\xe5\x91\x8a\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningNiagaraVolumeTextureSize_MetaData[] = {
		{ "Category", "Log|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Mesh Renderer \xe4\xb8\xad\xe4\xbd\xbf\xe7\x94\xa8\xe7\x9a\x84 VolumeTexture \xe8\xad\xa6\xe5\x91\x8a\xe5\xb0\xba\xe5\xaf\xb8\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mesh Renderer \xe4\xb8\xad\xe4\xbd\xbf\xe7\x94\xa8\xe7\x9a\x84 VolumeTexture \xe8\xad\xa6\xe5\x91\x8a\xe5\xb0\xba\xe5\xaf\xb8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningPostProcessPixelShaderInstructions_MetaData[] = {
		{ "Category", "MapCheck|Post Process" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x90\x8e\xe5\xa4\x84\xe7\x90\x86\xe8\xad\xa6\xe5\x91\x8a\xe7\x9a\x84\xe5\x83\x8f\xe7\xb4\xa0\xe7\x9d\x80\xe8\x89\xb2\xe5\x99\xa8\xe6\x8c\x87\xe4\xbb\xa4\xe6\x95\xb0\xe9\x98\x88\xe5\x80\xbc\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x8e\xe5\xa4\x84\xe7\x90\x86\xe8\xad\xa6\xe5\x91\x8a\xe7\x9a\x84\xe5\x83\x8f\xe7\xb4\xa0\xe7\x9d\x80\xe8\x89\xb2\xe5\x99\xa8\xe6\x8c\x87\xe4\xbb\xa4\xe6\x95\xb0\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningCompressedTextureSize_MetaData[] = {
		{ "Category", "MapCheck|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe8\xad\xa6\xe5\x91\x8a\xe7\x9a\x84\xe5\xb0\xba\xe5\xaf\xb8\xe9\x98\x88\xe5\x80\xbc\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe8\xad\xa6\xe5\x91\x8a\xe7\x9a\x84\xe5\xb0\xba\xe5\xaf\xb8\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningUncompressedTextureSize_MetaData[] = {
		{ "Category", "MapCheck|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x9c\xaa\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe8\xad\xa6\xe5\x91\x8a\xe7\x9a\x84\xe5\xb0\xba\xe5\xaf\xb8\xe9\x98\x88\xe5\x80\xbc\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9c\xaa\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe8\xad\xa6\xe5\x91\x8a\xe7\x9a\x84\xe5\xb0\xba\xe5\xaf\xb8\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LevelCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Level" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x85\xb3\xe5\x8d\xa1\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x85\xb3\xe5\x8d\xa1\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapLoadTimeScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Level" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x9c\xb0\xe5\x9b\xbe\xe5\x8a\xa0\xe8\xbd\xbd\xe6\x97\xb6\xe9\x97\xb4\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9c\xb0\xe5\x9b\xbe\xe5\x8a\xa0\xe8\xbd\xbd\xe6\x97\xb6\xe9\x97\xb4\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Actor \xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor \xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentMaxCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe7\xbb\x84\xe4\xbb\xb6\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbb\x84\xe4\xbb\xb6\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentAverageCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe7\xbb\x84\xe4\xbb\xb6\xe5\xb9\xb3\xe5\x9d\x87\xe6\x95\xb0\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbb\x84\xe4\xbb\xb6\xe5\xb9\xb3\xe5\x9d\x87\xe6\x95\xb0\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorTickRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Actor Tick \xe6\x95\xb0\xe9\x87\x8f\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor Tick \xe6\x95\xb0\xe9\x87\x8f\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlueprintRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe8\x93\x9d\xe5\x9b\xbe\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\x93\x9d\xe5\x9b\xbe\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshActorSameMeshCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x85\xb1\xe4\xba\xab\xe7\x9b\xb8\xe5\x90\x8c StaticMesh \xe7\x9a\x84 StaticMeshActor \xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x85\xb1\xe4\xba\xab\xe7\x9b\xb8\xe5\x90\x8c StaticMesh \xe7\x9a\x84 StaticMeshActor \xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeedsAttachParentBoundsCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Component" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe9\x9c\x80\xe8\xa6\x81 AttachParentBounds \xe7\x9a\x84\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x9c\x80\xe8\xa6\x81 AttachParentBounds \xe7\x9a\x84\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeedsAutoManageAttachmentCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Audio / Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe9\x9c\x80\xe8\xa6\x81 AutoManageAttachment \xe7\x9a\x84\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x9c\x80\xe8\xa6\x81 AutoManageAttachment \xe7\x9a\x84\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeedsMultipleAudioPlayModeCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe9\x9c\x80\xe8\xa6\x81 Multiple AudioPlayMode \xe7\x9a\x84\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x9c\x80\xe8\xa6\x81 Multiple AudioPlayMode \xe7\x9a\x84\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SameMaterialsInMaterialSlotsCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x9d\x90\xe8\xb4\xa8\xe6\xa7\xbd\xe4\xbd\x8d\xe9\x87\x8d\xe5\xa4\x8d\xe6\x9d\x90\xe8\xb4\xa8\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9d\x90\xe8\xb4\xa8\xe6\xa7\xbd\xe4\xbd\x8d\xe9\x87\x8d\xe5\xa4\x8d\xe6\x9d\x90\xe8\xb4\xa8\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MismatchNumOverrideMaterialCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe8\xa6\x86\xe7\x9b\x96\xe6\x9d\x90\xe8\xb4\xa8\xe6\x95\xb0\xe9\x87\x8f\xe4\xb8\x8d\xe5\x8c\xb9\xe9\x85\x8d\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa6\x86\xe7\x9b\x96\xe6\x9d\x90\xe8\xb4\xa8\xe6\x95\xb0\xe9\x87\x8f\xe4\xb8\x8d\xe5\x8c\xb9\xe9\x85\x8d\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MissingMaterialsCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe7\xbc\xba\xe5\xa4\xb1\xe6\x9d\x90\xe8\xb4\xa8\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbc\xba\xe5\xa4\xb1\xe6\x9d\x90\xe8\xb4\xa8\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MissingMeshesCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe7\xbc\xba\xe5\xa4\xb1\xe7\xbd\x91\xe6\xa0\xbc\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbc\xba\xe5\xa4\xb1\xe7\xbd\x91\xe6\xa0\xbc\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoLodsMeshCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\x97\xa0 LOD \xe7\xbd\x91\xe6\xa0\xbc\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x97\xa0 LOD \xe7\xbd\x91\xe6\xa0\xbc\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MissingComponentsCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Component" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe7\xbc\xba\xe5\xa4\xb1\xe7\xbb\x84\xe4\xbb\xb6\xe7\x9a\x84 Actor \xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbc\xba\xe5\xa4\xb1\xe7\xbb\x84\xe4\xbb\xb6\xe7\x9a\x84 Actor \xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * StaticMesh \xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StaticMesh \xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * StaticMesh \xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StaticMesh \xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshNaniteCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Nanite StaticMesh \xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Nanite StaticMesh \xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Nanite StaticMesh \xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Nanite StaticMesh \xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * SkeletalMesh \xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SkeletalMesh \xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * SkeletalMesh \xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SkeletalMesh \xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshNaniteCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Nanite SkeletalMesh \xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Nanite SkeletalMesh \xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Nanite SkeletalMesh \xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Nanite SkeletalMesh \xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMeshCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe7\xb2\x92\xe5\xad\x90\xe4\xbd\xbf\xe7\x94\xa8\xe7\xbd\x91\xe6\xa0\xbc\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xb2\x92\xe5\xad\x90\xe4\xbd\xbf\xe7\x94\xa8\xe7\xbd\x91\xe6\xa0\xbc\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMeshHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe7\xb2\x92\xe5\xad\x90\xe4\xbd\xbf\xe7\x94\xa8\xe7\xbd\x91\xe6\xa0\xbc\xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xb2\x92\xe5\xad\x90\xe4\xbd\xbf\xe7\x94\xa8\xe7\xbd\x91\xe6\xa0\xbc\xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * SkeletalMesh \xe9\xaa\xa8\xe9\xaa\xbc\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SkeletalMesh \xe9\xaa\xa8\xe9\xaa\xbc\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IgnoreBoneReductionRateBoneCountThreshold_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\xa3\x80\xe6\x9f\xa5 SkeletalMesh \xe9\xaa\xa8\xe9\xaa\xbc LOD \xe6\x97\xb6\xe5\xbf\xbd\xe7\x95\xa5\xe7\x9a\x84\xe9\xaa\xa8\xe9\xaa\xbc\xe6\x95\xb0\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xa3\x80\xe6\x9f\xa5 SkeletalMesh \xe9\xaa\xa8\xe9\xaa\xbc LOD \xe6\x97\xb6\xe5\xbf\xbd\xe7\x95\xa5\xe7\x9a\x84\xe9\xaa\xa8\xe9\xaa\xbc\xe6\x95\xb0\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneReductionRateScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * SkeletalMesh \xe9\xaa\xa8\xe9\xaa\xbc LOD \xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SkeletalMesh \xe9\xaa\xa8\xe9\xaa\xbc LOD \xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMeshNaniteCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe7\xb2\x92\xe5\xad\x90\xe4\xbd\xbf\xe7\x94\xa8 Nanite \xe7\xbd\x91\xe6\xa0\xbc\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xb2\x92\xe5\xad\x90\xe4\xbd\xbf\xe7\x94\xa8 Nanite \xe7\xbd\x91\xe6\xa0\xbc\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe7\xb2\x92\xe5\xad\x90\xe4\xbd\xbf\xe7\x94\xa8 Nanite \xe7\xbd\x91\xe6\xa0\xbc\xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xb2\x92\xe5\xad\x90\xe4\xbd\xbf\xe7\x94\xa8 Nanite \xe7\xbd\x91\xe6\xa0\xbc\xe7\xa1\xac\xe8\xbe\xb9\xe9\xa1\xb6\xe7\x82\xb9\xe6\x95\xb0\xe6\x8e\x92\xe8\xa1\x8c\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe9\xa1\xb6\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NiagaraStatefulEmitterRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Niagara Stateful \xe5\x8f\x91\xe5\xb0\x84\xe5\x99\xa8\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Niagara Stateful \xe5\x8f\x91\xe5\xb0\x84\xe5\x99\xa8\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NiagaraEmitterOptimizationHintsScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Niagara \xe5\x8f\x91\xe5\xb0\x84\xe5\x99\xa8\xe5\x8f\xaf\xe4\xbc\x98\xe5\x8c\x96\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Niagara \xe5\x8f\x91\xe5\xb0\x84\xe5\x99\xa8\xe5\x8f\xaf\xe4\xbc\x98\xe5\x8c\x96\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NiagaraSystemOptimizationHintsScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * NiagaraSystem \xe5\x8f\xaf\xe4\xbc\x98\xe5\x8c\x96\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "NiagaraSystem \xe5\x8f\xaf\xe4\xbc\x98\xe5\x8c\x96\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TranslucentMaterialRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x8d\x8a\xe9\x80\x8f\xe6\x98\x8e\xe6\x9d\x90\xe8\xb4\xa8\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8d\x8a\xe9\x80\x8f\xe6\x98\x8e\xe6\x9d\x90\xe8\xb4\xa8\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CastDynamicShadowRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Lighting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x8a\xa8\xe6\x80\x81\xe9\x98\xb4\xe5\xbd\xb1\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8a\xa8\xe6\x80\x81\xe9\x98\xb4\xe5\xbd\xb1\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovableLightCastDynamicShadowCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Lighting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Movable \xe5\x85\x89\xe6\xba\x90\xe6\x8a\x95\xe5\xb0\x84\xe5\x8a\xa8\xe6\x80\x81\xe9\x98\xb4\xe5\xbd\xb1\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Movable \xe5\x85\x89\xe6\xba\x90\xe6\x8a\x95\xe5\xb0\x84\xe5\x8a\xa8\xe6\x80\x81\xe9\x98\xb4\xe5\xbd\xb1\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovableSceneLightCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Lighting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Movable \xe5\x85\x89\xe6\xba\x90\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Movable \xe5\x85\x89\xe6\xba\x90\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverlapCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe9\x87\x8d\xe5\x8f\xa0\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x87\x8d\xe5\x8f\xa0\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe4\xb8\xaa\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NavMeshRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Navigation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * NavMesh \xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "NavMesh \xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ErrorNavMeshPolygonsRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Navigation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe9\x94\x99\xe8\xaf\xaf NavMesh \xe5\xa4\x9a\xe8\xbe\xb9\xe5\xbd\xa2\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x94\x99\xe8\xaf\xaf NavMesh \xe5\xa4\x9a\xe8\xbe\xb9\xe5\xbd\xa2\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ErrorBrushPolygonsRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Brush" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe9\x94\x99\xe8\xaf\xaf Brush \xe5\xa4\x9a\xe8\xbe\xb9\xe5\xbd\xa2\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x94\x99\xe8\xaf\xaf Brush \xe5\xa4\x9a\xe8\xbe\xb9\xe5\xbd\xa2\xe6\xaf\x94\xe4\xbe\x8b\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88%\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PostProcessPixelShaderInstructionsScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|PostProcess" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x90\x8e\xe5\xa4\x84\xe7\x90\x86\xe5\x83\x8f\xe7\xb4\xa0\xe7\x9d\x80\xe8\x89\xb2\xe5\x99\xa8\xe6\x8c\x87\xe4\xbb\xa4\xe6\x95\xb0\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe6\x8c\x87\xe4\xbb\xa4\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x8e\xe5\xa4\x84\xe7\x90\x86\xe5\x83\x8f\xe7\xb4\xa0\xe7\x9d\x80\xe8\x89\xb2\xe5\x99\xa8\xe6\x8c\x87\xe4\xbb\xa4\xe6\x95\xb0\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe6\x8c\x87\xe4\xbb\xa4\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StreamingCompressedTextureSizeThreshold_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\xb5\x81\xe9\x80\x81\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe5\xb0\xba\xe5\xaf\xb8\xe8\xaf\x84\xe4\xbc\xb0\xe9\x98\x88\xe5\x80\xbc\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xb5\x81\xe9\x80\x81\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe5\xb0\xba\xe5\xaf\xb8\xe8\xaf\x84\xe4\xbc\xb0\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StreamingUncompressedTextureSizeThreshold_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe6\xb5\x81\xe9\x80\x81\xe6\x9c\xaa\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe5\xb0\xba\xe5\xaf\xb8\xe8\xaf\x84\xe4\xbc\xb0\xe9\x98\x88\xe5\x80\xbc\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xb5\x81\xe9\x80\x81\xe6\x9c\xaa\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe5\xb0\xba\xe5\xaf\xb8\xe8\xaf\x84\xe4\xbc\xb0\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StreamingTextureCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe8\xb6\x85\xe8\xbf\x87\xe9\x98\x88\xe5\x80\xbc\xe7\x9a\x84\xe6\xb5\x81\xe9\x80\x81\xe7\xba\xb9\xe7\x90\x86\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe5\xbc\xa0\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb6\x85\xe8\xbf\x87\xe9\x98\x88\xe5\x80\xbc\xe7\x9a\x84\xe6\xb5\x81\xe9\x80\x81\xe7\xba\xb9\xe7\x90\x86\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe5\xbc\xa0\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NonStreamingCompressedTextureSizeThreshold_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe9\x9d\x9e\xe6\xb5\x81\xe9\x80\x81\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe5\xb0\xba\xe5\xaf\xb8\xe8\xaf\x84\xe4\xbc\xb0\xe9\x98\x88\xe5\x80\xbc\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x9d\x9e\xe6\xb5\x81\xe9\x80\x81\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe5\xb0\xba\xe5\xaf\xb8\xe8\xaf\x84\xe4\xbc\xb0\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NonStreamingUncompressedTextureSizeThreshold_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe9\x9d\x9e\xe6\xb5\x81\xe9\x80\x81\xe6\x9c\xaa\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe5\xb0\xba\xe5\xaf\xb8\xe8\xaf\x84\xe4\xbc\xb0\xe9\x98\x88\xe5\x80\xbc\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x9d\x9e\xe6\xb5\x81\xe9\x80\x81\xe6\x9c\xaa\xe5\x8e\x8b\xe7\xbc\xa9\xe7\xba\xb9\xe7\x90\x86\xe5\xb0\xba\xe5\xaf\xb8\xe8\xaf\x84\xe4\xbc\xb0\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NonStreamingTextureCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe8\xb6\x85\xe8\xbf\x87\xe9\x98\x88\xe5\x80\xbc\xe7\x9a\x84\xe9\x9d\x9e\xe6\xb5\x81\xe9\x80\x81\xe7\xba\xb9\xe7\x90\x86\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe5\xbc\xa0\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb6\x85\xe8\xbf\x87\xe9\x98\x88\xe5\x80\xbc\xe7\x9a\x84\xe9\x9d\x9e\xe6\xb5\x81\xe9\x80\x81\xe7\xba\xb9\xe7\x90\x86\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe5\xbc\xa0\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StreamedInTextureCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe8\xb6\x85\xe8\xbf\x87\xe9\x98\x88\xe5\x80\xbc\xe7\x9a\x84\xe5\xbd\x93\xe5\x89\x8d\xe6\xb5\x81\xe9\x80\x81\xe4\xb8\xad\xe7\xba\xb9\xe7\x90\x86\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe5\xbc\xa0\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/CommonCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb6\x85\xe8\xbf\x87\xe9\x98\x88\xe5\x80\xbc\xe7\x9a\x84\xe5\xbd\x93\xe5\x89\x8d\xe6\xb5\x81\xe9\x80\x81\xe4\xb8\xad\xe7\xba\xb9\xe7\x90\x86\xe6\x95\xb0\xe9\x87\x8f\xe8\xaf\x84\xe5\x88\x86\xe8\xae\xbe\xe7\xbd\xae\xef\xbc\x88\xe5\xbc\xa0\xef\xbc\x89" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UCommonCheckerSettings constinit property declarations *******************
	static void NewProp_bUnloadLevelsAfterCheck_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUnloadLevelsAfterCheck;
	static void NewProp_bIgnoreEditorOnlyActorsAndComponents_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIgnoreEditorOnlyActorsAndComponents;
	static void NewProp_bPostToMapCheck_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPostToMapCheck;
	static void NewProp_bPostToLog_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPostToLog;
	static void NewProp_bOpenReportWhenFinished_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOpenReportWhenFinished;
	static void NewProp_bOpenMapCheckWhenFinished_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOpenMapCheckWhenFinished;
	static void NewProp_bUseUserNameInReport_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseUserNameInReport;
	static void NewProp_bAddEngineVersionToSearchHints_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAddEngineVersionToSearchHints;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReportActorCategories;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayMapLoadTimeRanking;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WarningAttachParentBoundsScale;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayNeedsAttachParentBounds;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayNeedsAutoManageAttachment;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayNeedsAudioPlayMode;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayStaticMeshActorSameMesh;
	static void NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplaySameMaterialsInMaterialSlots;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayMismatchNumOverrideMaterial;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayMissingMaterials;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayMissingMeshes;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayNoLodsMeshes;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayMissingComponents;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayVertexRanking;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayBoneCountRanking;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayBoneReductionRateRanking;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayErrorNavMeshPolygons;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DrawNavMeshPolygonTimer;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxDisplayErrorBrushPolygons;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WarningNiagaraWarmupTime;
	static const UECodeGen_Private::FIntPropertyParams NewProp_WarningNiagaraRendererCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_WarningNiagaraVolumeTextureSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_WarningPostProcessPixelShaderInstructions;
	static const UECodeGen_Private::FIntPropertyParams NewProp_WarningCompressedTextureSize_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_WarningCompressedTextureSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_WarningUncompressedTextureSize_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_WarningUncompressedTextureSize;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LevelCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MapLoadTimeScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ActorCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ComponentMaxCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ComponentAverageCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ActorTickRatioScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BlueprintRatioScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_StaticMeshActorSameMeshCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NeedsAttachParentBoundsCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NeedsAutoManageAttachmentCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NeedsMultipleAudioPlayModeCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SameMaterialsInMaterialSlotsCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MismatchNumOverrideMaterialCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MissingMaterialsCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MissingMeshesCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NoLodsMeshCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MissingComponentsCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_StaticMeshCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_StaticMeshHardEdgeVertexCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_StaticMeshNaniteCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkeletalMeshCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkeletalMeshNaniteCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ParticleMeshCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ParticleMeshHardEdgeVertexCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoneCountScoreSettings;
	static const UECodeGen_Private::FIntPropertyParams NewProp_IgnoreBoneReductionRateBoneCountThreshold;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoneReductionRateScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ParticleMeshNaniteCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NiagaraStatefulEmitterRatioScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NiagaraEmitterOptimizationHintsScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NiagaraSystemOptimizationHintsScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TranslucentMaterialRatioScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CastDynamicShadowRatioScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MovableLightCastDynamicShadowCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MovableSceneLightCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OverlapCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NavMeshRatioScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ErrorNavMeshPolygonsRatioScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ErrorBrushPolygonsRatioScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PostProcessPixelShaderInstructionsScoreSettings;
	static const UECodeGen_Private::FIntPropertyParams NewProp_StreamingCompressedTextureSizeThreshold_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_StreamingCompressedTextureSizeThreshold;
	static const UECodeGen_Private::FIntPropertyParams NewProp_StreamingUncompressedTextureSizeThreshold_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_StreamingUncompressedTextureSizeThreshold;
	static const UECodeGen_Private::FStructPropertyParams NewProp_StreamingTextureCountScoreSettings;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NonStreamingCompressedTextureSizeThreshold_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NonStreamingCompressedTextureSizeThreshold;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NonStreamingUncompressedTextureSizeThreshold_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NonStreamingUncompressedTextureSizeThreshold;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NonStreamingTextureCountScoreSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_StreamedInTextureCountScoreSettings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UCommonCheckerSettings constinit property declarations *********************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCommonCheckerSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UCommonCheckerSettings_Statics

// ********** Begin Class UCommonCheckerSettings Property Definitions ******************************
void Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bUnloadLevelsAfterCheck_SetBit(void* Obj)
{
	((UCommonCheckerSettings*)Obj)->bUnloadLevelsAfterCheck = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bUnloadLevelsAfterCheck = { "bUnloadLevelsAfterCheck", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCommonCheckerSettings), &Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bUnloadLevelsAfterCheck_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUnloadLevelsAfterCheck_MetaData), NewProp_bUnloadLevelsAfterCheck_MetaData) };
void Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bIgnoreEditorOnlyActorsAndComponents_SetBit(void* Obj)
{
	((UCommonCheckerSettings*)Obj)->bIgnoreEditorOnlyActorsAndComponents = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bIgnoreEditorOnlyActorsAndComponents = { "bIgnoreEditorOnlyActorsAndComponents", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCommonCheckerSettings), &Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bIgnoreEditorOnlyActorsAndComponents_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIgnoreEditorOnlyActorsAndComponents_MetaData), NewProp_bIgnoreEditorOnlyActorsAndComponents_MetaData) };
void Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bPostToMapCheck_SetBit(void* Obj)
{
	((UCommonCheckerSettings*)Obj)->bPostToMapCheck = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bPostToMapCheck = { "bPostToMapCheck", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCommonCheckerSettings), &Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bPostToMapCheck_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPostToMapCheck_MetaData), NewProp_bPostToMapCheck_MetaData) };
void Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bPostToLog_SetBit(void* Obj)
{
	((UCommonCheckerSettings*)Obj)->bPostToLog = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bPostToLog = { "bPostToLog", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCommonCheckerSettings), &Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bPostToLog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPostToLog_MetaData), NewProp_bPostToLog_MetaData) };
void Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bOpenReportWhenFinished_SetBit(void* Obj)
{
	((UCommonCheckerSettings*)Obj)->bOpenReportWhenFinished = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bOpenReportWhenFinished = { "bOpenReportWhenFinished", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCommonCheckerSettings), &Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bOpenReportWhenFinished_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOpenReportWhenFinished_MetaData), NewProp_bOpenReportWhenFinished_MetaData) };
void Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bOpenMapCheckWhenFinished_SetBit(void* Obj)
{
	((UCommonCheckerSettings*)Obj)->bOpenMapCheckWhenFinished = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bOpenMapCheckWhenFinished = { "bOpenMapCheckWhenFinished", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCommonCheckerSettings), &Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bOpenMapCheckWhenFinished_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOpenMapCheckWhenFinished_MetaData), NewProp_bOpenMapCheckWhenFinished_MetaData) };
void Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bUseUserNameInReport_SetBit(void* Obj)
{
	((UCommonCheckerSettings*)Obj)->bUseUserNameInReport = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bUseUserNameInReport = { "bUseUserNameInReport", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCommonCheckerSettings), &Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bUseUserNameInReport_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseUserNameInReport_MetaData), NewProp_bUseUserNameInReport_MetaData) };
void Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bAddEngineVersionToSearchHints_SetBit(void* Obj)
{
	((UCommonCheckerSettings*)Obj)->bAddEngineVersionToSearchHints = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bAddEngineVersionToSearchHints = { "bAddEngineVersionToSearchHints", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCommonCheckerSettings), &Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bAddEngineVersionToSearchHints_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAddEngineVersionToSearchHints_MetaData), NewProp_bAddEngineVersionToSearchHints_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ReportActorCategories = { "ReportActorCategories", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ReportActorCategories), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReportActorCategories_MetaData), NewProp_ReportActorCategories_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayMapLoadTimeRanking = { "MaxDisplayMapLoadTimeRanking", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayMapLoadTimeRanking), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayMapLoadTimeRanking_MetaData), NewProp_MaxDisplayMapLoadTimeRanking_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningAttachParentBoundsScale = { "WarningAttachParentBoundsScale", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, WarningAttachParentBoundsScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningAttachParentBoundsScale_MetaData), NewProp_WarningAttachParentBoundsScale_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayNeedsAttachParentBounds = { "MaxDisplayNeedsAttachParentBounds", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayNeedsAttachParentBounds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayNeedsAttachParentBounds_MetaData), NewProp_MaxDisplayNeedsAttachParentBounds_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayNeedsAutoManageAttachment = { "MaxDisplayNeedsAutoManageAttachment", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayNeedsAutoManageAttachment), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayNeedsAutoManageAttachment_MetaData), NewProp_MaxDisplayNeedsAutoManageAttachment_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayNeedsAudioPlayMode = { "MaxDisplayNeedsAudioPlayMode", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayNeedsAudioPlayMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayNeedsAudioPlayMode_MetaData), NewProp_MaxDisplayNeedsAudioPlayMode_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayStaticMeshActorSameMesh = { "MaxDisplayStaticMeshActorSameMesh", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayStaticMeshActorSameMesh), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayStaticMeshActorSameMesh_MetaData), NewProp_MaxDisplayStaticMeshActorSameMesh_MetaData) };
void Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_SetBit(void* Obj)
{
	((UCommonCheckerSettings*)Obj)->bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled = { "bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCommonCheckerSettings), &Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_MetaData), NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplaySameMaterialsInMaterialSlots = { "MaxDisplaySameMaterialsInMaterialSlots", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplaySameMaterialsInMaterialSlots), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplaySameMaterialsInMaterialSlots_MetaData), NewProp_MaxDisplaySameMaterialsInMaterialSlots_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayMismatchNumOverrideMaterial = { "MaxDisplayMismatchNumOverrideMaterial", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayMismatchNumOverrideMaterial), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayMismatchNumOverrideMaterial_MetaData), NewProp_MaxDisplayMismatchNumOverrideMaterial_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayMissingMaterials = { "MaxDisplayMissingMaterials", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayMissingMaterials), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayMissingMaterials_MetaData), NewProp_MaxDisplayMissingMaterials_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayMissingMeshes = { "MaxDisplayMissingMeshes", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayMissingMeshes), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayMissingMeshes_MetaData), NewProp_MaxDisplayMissingMeshes_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayNoLodsMeshes = { "MaxDisplayNoLodsMeshes", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayNoLodsMeshes), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayNoLodsMeshes_MetaData), NewProp_MaxDisplayNoLodsMeshes_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayMissingComponents = { "MaxDisplayMissingComponents", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayMissingComponents), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayMissingComponents_MetaData), NewProp_MaxDisplayMissingComponents_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayVertexRanking = { "MaxDisplayVertexRanking", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayVertexRanking), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayVertexRanking_MetaData), NewProp_MaxDisplayVertexRanking_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayBoneCountRanking = { "MaxDisplayBoneCountRanking", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayBoneCountRanking), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayBoneCountRanking_MetaData), NewProp_MaxDisplayBoneCountRanking_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayBoneReductionRateRanking = { "MaxDisplayBoneReductionRateRanking", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayBoneReductionRateRanking), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayBoneReductionRateRanking_MetaData), NewProp_MaxDisplayBoneReductionRateRanking_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayErrorNavMeshPolygons = { "MaxDisplayErrorNavMeshPolygons", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayErrorNavMeshPolygons), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayErrorNavMeshPolygons_MetaData), NewProp_MaxDisplayErrorNavMeshPolygons_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_DrawNavMeshPolygonTimer = { "DrawNavMeshPolygonTimer", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, DrawNavMeshPolygonTimer), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DrawNavMeshPolygonTimer_MetaData), NewProp_DrawNavMeshPolygonTimer_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayErrorBrushPolygons = { "MaxDisplayErrorBrushPolygons", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MaxDisplayErrorBrushPolygons), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayErrorBrushPolygons_MetaData), NewProp_MaxDisplayErrorBrushPolygons_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningNiagaraWarmupTime = { "WarningNiagaraWarmupTime", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, WarningNiagaraWarmupTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningNiagaraWarmupTime_MetaData), NewProp_WarningNiagaraWarmupTime_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningNiagaraRendererCount = { "WarningNiagaraRendererCount", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, WarningNiagaraRendererCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningNiagaraRendererCount_MetaData), NewProp_WarningNiagaraRendererCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningNiagaraVolumeTextureSize = { "WarningNiagaraVolumeTextureSize", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, WarningNiagaraVolumeTextureSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningNiagaraVolumeTextureSize_MetaData), NewProp_WarningNiagaraVolumeTextureSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningPostProcessPixelShaderInstructions = { "WarningPostProcessPixelShaderInstructions", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, WarningPostProcessPixelShaderInstructions), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningPostProcessPixelShaderInstructions_MetaData), NewProp_WarningPostProcessPixelShaderInstructions_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningCompressedTextureSize_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningCompressedTextureSize = { "WarningCompressedTextureSize", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, WarningCompressedTextureSize), Z_Construct_UEnum_CommonChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningCompressedTextureSize_MetaData), NewProp_WarningCompressedTextureSize_MetaData) }; // 2753888519
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningUncompressedTextureSize_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningUncompressedTextureSize = { "WarningUncompressedTextureSize", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, WarningUncompressedTextureSize), Z_Construct_UEnum_CommonChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningUncompressedTextureSize_MetaData), NewProp_WarningUncompressedTextureSize_MetaData) }; // 2753888519
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_LevelCountScoreSettings = { "LevelCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, LevelCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LevelCountScoreSettings_MetaData), NewProp_LevelCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MapLoadTimeScoreSettings = { "MapLoadTimeScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MapLoadTimeScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapLoadTimeScoreSettings_MetaData), NewProp_MapLoadTimeScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ActorCountScoreSettings = { "ActorCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ActorCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorCountScoreSettings_MetaData), NewProp_ActorCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ComponentMaxCountScoreSettings = { "ComponentMaxCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ComponentMaxCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentMaxCountScoreSettings_MetaData), NewProp_ComponentMaxCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ComponentAverageCountScoreSettings = { "ComponentAverageCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ComponentAverageCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentAverageCountScoreSettings_MetaData), NewProp_ComponentAverageCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ActorTickRatioScoreSettings = { "ActorTickRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ActorTickRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorTickRatioScoreSettings_MetaData), NewProp_ActorTickRatioScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_BlueprintRatioScoreSettings = { "BlueprintRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, BlueprintRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlueprintRatioScoreSettings_MetaData), NewProp_BlueprintRatioScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StaticMeshActorSameMeshCountScoreSettings = { "StaticMeshActorSameMeshCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, StaticMeshActorSameMeshCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshActorSameMeshCountScoreSettings_MetaData), NewProp_StaticMeshActorSameMeshCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NeedsAttachParentBoundsCountScoreSettings = { "NeedsAttachParentBoundsCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NeedsAttachParentBoundsCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeedsAttachParentBoundsCountScoreSettings_MetaData), NewProp_NeedsAttachParentBoundsCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NeedsAutoManageAttachmentCountScoreSettings = { "NeedsAutoManageAttachmentCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NeedsAutoManageAttachmentCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeedsAutoManageAttachmentCountScoreSettings_MetaData), NewProp_NeedsAutoManageAttachmentCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NeedsMultipleAudioPlayModeCountScoreSettings = { "NeedsMultipleAudioPlayModeCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NeedsMultipleAudioPlayModeCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeedsMultipleAudioPlayModeCountScoreSettings_MetaData), NewProp_NeedsMultipleAudioPlayModeCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_SameMaterialsInMaterialSlotsCountScoreSettings = { "SameMaterialsInMaterialSlotsCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, SameMaterialsInMaterialSlotsCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SameMaterialsInMaterialSlotsCountScoreSettings_MetaData), NewProp_SameMaterialsInMaterialSlotsCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MismatchNumOverrideMaterialCountScoreSettings = { "MismatchNumOverrideMaterialCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MismatchNumOverrideMaterialCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MismatchNumOverrideMaterialCountScoreSettings_MetaData), NewProp_MismatchNumOverrideMaterialCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MissingMaterialsCountScoreSettings = { "MissingMaterialsCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MissingMaterialsCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MissingMaterialsCountScoreSettings_MetaData), NewProp_MissingMaterialsCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MissingMeshesCountScoreSettings = { "MissingMeshesCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MissingMeshesCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MissingMeshesCountScoreSettings_MetaData), NewProp_MissingMeshesCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NoLodsMeshCountScoreSettings = { "NoLodsMeshCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NoLodsMeshCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoLodsMeshCountScoreSettings_MetaData), NewProp_NoLodsMeshCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MissingComponentsCountScoreSettings = { "MissingComponentsCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MissingComponentsCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MissingComponentsCountScoreSettings_MetaData), NewProp_MissingComponentsCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StaticMeshCountScoreSettings = { "StaticMeshCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, StaticMeshCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshCountScoreSettings_MetaData), NewProp_StaticMeshCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StaticMeshHardEdgeVertexCountScoreSettings = { "StaticMeshHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, StaticMeshHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshHardEdgeVertexCountScoreSettings_MetaData), NewProp_StaticMeshHardEdgeVertexCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StaticMeshNaniteCountScoreSettings = { "StaticMeshNaniteCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, StaticMeshNaniteCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshNaniteCountScoreSettings_MetaData), NewProp_StaticMeshNaniteCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings = { "StaticMeshNaniteHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, StaticMeshNaniteHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings_MetaData), NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_SkeletalMeshCountScoreSettings = { "SkeletalMeshCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, SkeletalMeshCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshCountScoreSettings_MetaData), NewProp_SkeletalMeshCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings = { "SkeletalMeshHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, SkeletalMeshHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings_MetaData), NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_SkeletalMeshNaniteCountScoreSettings = { "SkeletalMeshNaniteCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, SkeletalMeshNaniteCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshNaniteCountScoreSettings_MetaData), NewProp_SkeletalMeshNaniteCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings = { "SkeletalMeshNaniteHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, SkeletalMeshNaniteHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings_MetaData), NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ParticleMeshCountScoreSettings = { "ParticleMeshCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ParticleMeshCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMeshCountScoreSettings_MetaData), NewProp_ParticleMeshCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ParticleMeshHardEdgeVertexCountScoreSettings = { "ParticleMeshHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ParticleMeshHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMeshHardEdgeVertexCountScoreSettings_MetaData), NewProp_ParticleMeshHardEdgeVertexCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_BoneCountScoreSettings = { "BoneCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, BoneCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneCountScoreSettings_MetaData), NewProp_BoneCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_IgnoreBoneReductionRateBoneCountThreshold = { "IgnoreBoneReductionRateBoneCountThreshold", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, IgnoreBoneReductionRateBoneCountThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IgnoreBoneReductionRateBoneCountThreshold_MetaData), NewProp_IgnoreBoneReductionRateBoneCountThreshold_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_BoneReductionRateScoreSettings = { "BoneReductionRateScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, BoneReductionRateScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneReductionRateScoreSettings_MetaData), NewProp_BoneReductionRateScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ParticleMeshNaniteCountScoreSettings = { "ParticleMeshNaniteCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ParticleMeshNaniteCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMeshNaniteCountScoreSettings_MetaData), NewProp_ParticleMeshNaniteCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings = { "ParticleMeshNaniteHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ParticleMeshNaniteHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings_MetaData), NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NiagaraStatefulEmitterRatioScoreSettings = { "NiagaraStatefulEmitterRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NiagaraStatefulEmitterRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NiagaraStatefulEmitterRatioScoreSettings_MetaData), NewProp_NiagaraStatefulEmitterRatioScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NiagaraEmitterOptimizationHintsScoreSettings = { "NiagaraEmitterOptimizationHintsScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NiagaraEmitterOptimizationHintsScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NiagaraEmitterOptimizationHintsScoreSettings_MetaData), NewProp_NiagaraEmitterOptimizationHintsScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NiagaraSystemOptimizationHintsScoreSettings = { "NiagaraSystemOptimizationHintsScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NiagaraSystemOptimizationHintsScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NiagaraSystemOptimizationHintsScoreSettings_MetaData), NewProp_NiagaraSystemOptimizationHintsScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_TranslucentMaterialRatioScoreSettings = { "TranslucentMaterialRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, TranslucentMaterialRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TranslucentMaterialRatioScoreSettings_MetaData), NewProp_TranslucentMaterialRatioScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_CastDynamicShadowRatioScoreSettings = { "CastDynamicShadowRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, CastDynamicShadowRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CastDynamicShadowRatioScoreSettings_MetaData), NewProp_CastDynamicShadowRatioScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MovableLightCastDynamicShadowCountScoreSettings = { "MovableLightCastDynamicShadowCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MovableLightCastDynamicShadowCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovableLightCastDynamicShadowCountScoreSettings_MetaData), NewProp_MovableLightCastDynamicShadowCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MovableSceneLightCountScoreSettings = { "MovableSceneLightCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, MovableSceneLightCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovableSceneLightCountScoreSettings_MetaData), NewProp_MovableSceneLightCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_OverlapCountScoreSettings = { "OverlapCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, OverlapCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverlapCountScoreSettings_MetaData), NewProp_OverlapCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NavMeshRatioScoreSettings = { "NavMeshRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NavMeshRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NavMeshRatioScoreSettings_MetaData), NewProp_NavMeshRatioScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ErrorNavMeshPolygonsRatioScoreSettings = { "ErrorNavMeshPolygonsRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ErrorNavMeshPolygonsRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ErrorNavMeshPolygonsRatioScoreSettings_MetaData), NewProp_ErrorNavMeshPolygonsRatioScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ErrorBrushPolygonsRatioScoreSettings = { "ErrorBrushPolygonsRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, ErrorBrushPolygonsRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ErrorBrushPolygonsRatioScoreSettings_MetaData), NewProp_ErrorBrushPolygonsRatioScoreSettings_MetaData) }; // 59817150
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_PostProcessPixelShaderInstructionsScoreSettings = { "PostProcessPixelShaderInstructionsScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, PostProcessPixelShaderInstructionsScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PostProcessPixelShaderInstructionsScoreSettings_MetaData), NewProp_PostProcessPixelShaderInstructionsScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamingCompressedTextureSizeThreshold_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamingCompressedTextureSizeThreshold = { "StreamingCompressedTextureSizeThreshold", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, StreamingCompressedTextureSizeThreshold), Z_Construct_UEnum_CommonChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StreamingCompressedTextureSizeThreshold_MetaData), NewProp_StreamingCompressedTextureSizeThreshold_MetaData) }; // 2753888519
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamingUncompressedTextureSizeThreshold_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamingUncompressedTextureSizeThreshold = { "StreamingUncompressedTextureSizeThreshold", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, StreamingUncompressedTextureSizeThreshold), Z_Construct_UEnum_CommonChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StreamingUncompressedTextureSizeThreshold_MetaData), NewProp_StreamingUncompressedTextureSizeThreshold_MetaData) }; // 2753888519
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamingTextureCountScoreSettings = { "StreamingTextureCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, StreamingTextureCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StreamingTextureCountScoreSettings_MetaData), NewProp_StreamingTextureCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NonStreamingCompressedTextureSizeThreshold_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NonStreamingCompressedTextureSizeThreshold = { "NonStreamingCompressedTextureSizeThreshold", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NonStreamingCompressedTextureSizeThreshold), Z_Construct_UEnum_CommonChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NonStreamingCompressedTextureSizeThreshold_MetaData), NewProp_NonStreamingCompressedTextureSizeThreshold_MetaData) }; // 2753888519
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NonStreamingUncompressedTextureSizeThreshold_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NonStreamingUncompressedTextureSizeThreshold = { "NonStreamingUncompressedTextureSizeThreshold", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NonStreamingUncompressedTextureSizeThreshold), Z_Construct_UEnum_CommonChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NonStreamingUncompressedTextureSizeThreshold_MetaData), NewProp_NonStreamingUncompressedTextureSizeThreshold_MetaData) }; // 2753888519
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NonStreamingTextureCountScoreSettings = { "NonStreamingTextureCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, NonStreamingTextureCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NonStreamingTextureCountScoreSettings_MetaData), NewProp_NonStreamingTextureCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamedInTextureCountScoreSettings = { "StreamedInTextureCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCheckerSettings, StreamedInTextureCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StreamedInTextureCountScoreSettings_MetaData), NewProp_StreamedInTextureCountScoreSettings_MetaData) }; // 3174090410
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCommonCheckerSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bUnloadLevelsAfterCheck,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bIgnoreEditorOnlyActorsAndComponents,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bPostToMapCheck,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bPostToLog,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bOpenReportWhenFinished,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bOpenMapCheckWhenFinished,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bUseUserNameInReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bAddEngineVersionToSearchHints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ReportActorCategories,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayMapLoadTimeRanking,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningAttachParentBoundsScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayNeedsAttachParentBounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayNeedsAutoManageAttachment,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayNeedsAudioPlayMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayStaticMeshActorSameMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplaySameMaterialsInMaterialSlots,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayMismatchNumOverrideMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayMissingMaterials,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayMissingMeshes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayNoLodsMeshes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayMissingComponents,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayVertexRanking,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayBoneCountRanking,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayBoneReductionRateRanking,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayErrorNavMeshPolygons,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_DrawNavMeshPolygonTimer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MaxDisplayErrorBrushPolygons,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningNiagaraWarmupTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningNiagaraRendererCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningNiagaraVolumeTextureSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningPostProcessPixelShaderInstructions,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningCompressedTextureSize_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningCompressedTextureSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningUncompressedTextureSize_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_WarningUncompressedTextureSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_LevelCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MapLoadTimeScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ActorCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ComponentMaxCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ComponentAverageCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ActorTickRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_BlueprintRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StaticMeshActorSameMeshCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NeedsAttachParentBoundsCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NeedsAutoManageAttachmentCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NeedsMultipleAudioPlayModeCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_SameMaterialsInMaterialSlotsCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MismatchNumOverrideMaterialCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MissingMaterialsCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MissingMeshesCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NoLodsMeshCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MissingComponentsCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StaticMeshCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StaticMeshHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StaticMeshNaniteCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_SkeletalMeshCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_SkeletalMeshNaniteCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ParticleMeshCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ParticleMeshHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_BoneCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_IgnoreBoneReductionRateBoneCountThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_BoneReductionRateScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ParticleMeshNaniteCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NiagaraStatefulEmitterRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NiagaraEmitterOptimizationHintsScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NiagaraSystemOptimizationHintsScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_TranslucentMaterialRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_CastDynamicShadowRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MovableLightCastDynamicShadowCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_MovableSceneLightCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_OverlapCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NavMeshRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ErrorNavMeshPolygonsRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_ErrorBrushPolygonsRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_PostProcessPixelShaderInstructionsScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamingCompressedTextureSizeThreshold_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamingCompressedTextureSizeThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamingUncompressedTextureSizeThreshold_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamingUncompressedTextureSizeThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamingTextureCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NonStreamingCompressedTextureSizeThreshold_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NonStreamingCompressedTextureSizeThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NonStreamingUncompressedTextureSizeThreshold_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NonStreamingUncompressedTextureSizeThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_NonStreamingTextureCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCheckerSettings_Statics::NewProp_StreamedInTextureCountScoreSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCheckerSettings_Statics::PropPointers) < 2048);
// ********** End Class UCommonCheckerSettings Property Definitions ********************************
UObject* (*const Z_Construct_UClass_UCommonCheckerSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_CommonChecker,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCheckerSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCommonCheckerSettings_Statics::ClassParams = {
	&UCommonCheckerSettings::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UCommonCheckerSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCheckerSettings_Statics::PropPointers),
	0,
	0x000800A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCheckerSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UCommonCheckerSettings_Statics::Class_MetaDataParams)
};
void UCommonCheckerSettings::StaticRegisterNativesUCommonCheckerSettings()
{
}
UClass* Z_Construct_UClass_UCommonCheckerSettings()
{
	if (!Z_Registration_Info_UClass_UCommonCheckerSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCommonCheckerSettings.OuterSingleton, Z_Construct_UClass_UCommonCheckerSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCommonCheckerSettings.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UCommonCheckerSettings);
UCommonCheckerSettings::~UCommonCheckerSettings() {}
// ********** End Class UCommonCheckerSettings *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h__Script_CommonChecker_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCommonCheckerSettings, UCommonCheckerSettings::StaticClass, TEXT("UCommonCheckerSettings"), &Z_Registration_Info_UClass_UCommonCheckerSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonCheckerSettings), 1288075049U) },
	};
}; // Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h__Script_CommonChecker_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h__Script_CommonChecker_717588775{
	TEXT("/Script/CommonChecker"),
	Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h__Script_CommonChecker_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_CommonChecker_Source_CommonChecker_Public_CommonCheckerSettings_h__Script_CommonChecker_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
