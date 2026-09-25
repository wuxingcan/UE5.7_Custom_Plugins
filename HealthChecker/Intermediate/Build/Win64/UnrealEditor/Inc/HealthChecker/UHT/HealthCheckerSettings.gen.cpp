// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HealthCheckerSettings.h"
#include "HealthCheckerTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeHealthCheckerSettings() {}

// ********** Begin Cross Module References ********************************************************
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
HEALTHCHECKER_API UClass* Z_Construct_UClass_UHealthCheckerSettings();
HEALTHCHECKER_API UClass* Z_Construct_UClass_UHealthCheckerSettings_NoRegister();
HEALTHCHECKER_API UEnum* Z_Construct_UEnum_HealthChecker_ETextureSize();
HEALTHCHECKER_API UScriptStruct* Z_Construct_UScriptStruct_FFloatScoreSettings();
HEALTHCHECKER_API UScriptStruct* Z_Construct_UScriptStruct_FIntScoreSettings();
UPackage* Z_Construct_UPackage__Script_HealthChecker();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UHealthCheckerSettings ***************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UHealthCheckerSettings;
UClass* UHealthCheckerSettings::GetPrivateStaticClass()
{
	using TClass = UHealthCheckerSettings;
	if (!Z_Registration_Info_UClass_UHealthCheckerSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("HealthCheckerSettings"),
			Z_Registration_Info_UClass_UHealthCheckerSettings.InnerSingleton,
			StaticRegisterNativesUHealthCheckerSettings,
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
	return Z_Registration_Info_UClass_UHealthCheckerSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UHealthCheckerSettings_NoRegister()
{
	return UHealthCheckerSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UHealthCheckerSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Settings for Health Checker\n */" },
#endif
		{ "DisplayName", "Health Checker" },
		{ "IncludePath", "HealthCheckerSettings.h" },
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Settings for Health Checker" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUnloadLevelsAfterCheck_MetaData[] = {
		{ "Category", "Health Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Unload levels and WorldPartition cells after running HealthChecker\n\x09 * HealthChecker\xe5\xae\x9f\xe8\xa1\x8c\xe5\xbe\x8c\xe3\x81\xab\xe3\x83\xac\xe3\x83\x99\xe3\x83\xab\xe3\x82\x84\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe3\x83\x91\xe3\x83\xbc\xe3\x83\x86\xe3\x83\xbc\xe3\x82\xb7\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x82\xbb\xe3\x83\xab\xe3\x82\x92\xe3\x82\xa2\xe3\x83\xb3\xe3\x83\xad\xe3\x83\xbc\xe3\x83\x89\xe3\x81\x99\xe3\x82\x8b\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Unload levels and WorldPartition cells after running HealthChecker\nHealthChecker\xe5\xae\x9f\xe8\xa1\x8c\xe5\xbe\x8c\xe3\x81\xab\xe3\x83\xac\xe3\x83\x99\xe3\x83\xab\xe3\x82\x84\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe3\x83\x91\xe3\x83\xbc\xe3\x83\x86\xe3\x83\xbc\xe3\x82\xb7\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x82\xbb\xe3\x83\xab\xe3\x82\x92\xe3\x82\xa2\xe3\x83\xb3\xe3\x83\xad\xe3\x83\xbc\xe3\x83\x89\xe3\x81\x99\xe3\x82\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIgnoreEditorOnlyActorsAndComponents_MetaData[] = {
		{ "Category", "Health Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Ignore EditorOnly Actors and Components\n\x09 * EditorOnly\xe3\x81\xae\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xa8\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Ignore EditorOnly Actors and Components\nEditorOnly\xe3\x81\xae\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xa8\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPostToMapCheck_MetaData[] = {
		{ "Category", "Health Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Post warnings to MapCheck window\n\x09 * MapCheck\xe3\x81\xab\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe3\x83\x9d\xe3\x82\xb9\xe3\x83\x88\xe3\x81\x99\xe3\x82\x8b\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Post warnings to MapCheck window\nMapCheck\xe3\x81\xab\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe3\x83\x9d\xe3\x82\xb9\xe3\x83\x88\xe3\x81\x99\xe3\x82\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPostToLog_MetaData[] = {
		{ "Category", "Health Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Post warnings to the Output Log\n\x09 * \xe3\x83\xad\xe3\x82\xb0\xe3\x81\xab\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe3\x83\x9d\xe3\x82\xb9\xe3\x83\x88\xe3\x81\x99\xe3\x82\x8b\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Post warnings to the Output Log\n\xe3\x83\xad\xe3\x82\xb0\xe3\x81\xab\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe3\x83\x9d\xe3\x82\xb9\xe3\x83\x88\xe3\x81\x99\xe3\x82\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOpenReportWhenFinished_MetaData[] = {
		{ "Category", "Health Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Open the report when finished\n\x09 * \xe6\x9c\x80\xe5\xbe\x8c\xe3\x81\xab\xe3\x83\xac\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x88\xe3\x82\x92\xe9\x96\x8b\xe3\x81\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Open the report when finished\n\xe6\x9c\x80\xe5\xbe\x8c\xe3\x81\xab\xe3\x83\xac\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x88\xe3\x82\x92\xe9\x96\x8b\xe3\x81\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOpenMapCheckWhenFinished_MetaData[] = {
		{ "Category", "Health Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Open the MapCheck window when finished\n\x09 * \xe6\x9c\x80\xe5\xbe\x8c\xe3\x81\xab\xe3\x83\x9e\xe3\x83\x83\xe3\x83\x97\xe3\x83\x81\xe3\x82\xa7\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xa6\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x89\xe3\x82\xa6\xe3\x82\x92\xe9\x96\x8b\xe3\x81\x8f\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Open the MapCheck window when finished\n\xe6\x9c\x80\xe5\xbe\x8c\xe3\x81\xab\xe3\x83\x9e\xe3\x83\x83\xe3\x83\x97\xe3\x83\x81\xe3\x82\xa7\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xa6\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x89\xe3\x82\xa6\xe3\x82\x92\xe9\x96\x8b\xe3\x81\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseUserNameInReport_MetaData[] = {
		{ "Category", "Health Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Include the username in the report\n\x09 * \xe3\x83\xac\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x88\xe3\x81\xab\xe3\x83\xa6\xe3\x83\xbc\xe3\x82\xb6\xe3\x83\xbc\xe5\x90\x8d\xe3\x82\x92\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Include the username in the report\n\xe3\x83\xac\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x88\xe3\x81\xab\xe3\x83\xa6\xe3\x83\xbc\xe3\x82\xb6\xe3\x83\xbc\xe5\x90\x8d\xe3\x82\x92\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAddEngineVersionToSearchHints_MetaData[] = {
		{ "Category", "Health Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Append engine version to search hints\n\x09 * \xe6\xa4\x9c\xe7\xb4\xa2\xe3\x81\xae\xe3\x83\x92\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xab\xe3\x82\xa8\xe3\x83\xb3\xe3\x82\xb8\xe3\x83\xb3\xe3\x83\x90\xe3\x83\xbc\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe6\x83\x85\xe5\xa0\xb1\xe3\x82\x92\xe4\xbb\x98\xe4\xb8\x8e\xe3\x81\x99\xe3\x82\x8b\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Append engine version to search hints\n\xe6\xa4\x9c\xe7\xb4\xa2\xe3\x81\xae\xe3\x83\x92\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xab\xe3\x82\xa8\xe3\x83\xb3\xe3\x82\xb8\xe3\x83\xb3\xe3\x83\x90\xe3\x83\xbc\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe6\x83\x85\xe5\xa0\xb1\xe3\x82\x92\xe4\xbb\x98\xe4\xb8\x8e\xe3\x81\x99\xe3\x82\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReportActorCategories_MetaData[] = {
		{ "Bitmask", "" },
		{ "BitmaskEnum", "/Script/HealthChecker.EBitActorCategory" },
		{ "Category", "Health Checker Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Actor categories to display in the report\n\x09 * \xe3\x83\xac\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x88\xe3\x81\xab\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x82\xab\xe3\x83\x86\xe3\x82\xb4\xe3\x83\xaa\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor categories to display in the report\n\xe3\x83\xac\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x88\xe3\x81\xab\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x82\xab\xe3\x83\x86\xe3\x82\xb4\xe3\x83\xaa" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayMapLoadTimeRanking_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Number of map load time entries to display in the ranking\n\x09 * \xe3\x83\x9e\xe3\x83\x83\xe3\x83\x97\xe3\x81\xae\xe3\x83\xad\xe3\x83\xbc\xe3\x83\x89\xe6\x99\x82\xe9\x96\x93\xe3\x81\xae\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of map load time entries to display in the ranking\n\xe3\x83\x9e\xe3\x83\x83\xe3\x83\x97\xe3\x81\xae\xe3\x83\xad\xe3\x83\xbc\xe3\x83\x89\xe6\x99\x82\xe9\x96\x93\xe3\x81\xae\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningAttachParentBoundsScale_MetaData[] = {
		{ "Category", "MapCheck|Component" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Bounds scale used for displaying AttachParentBounds warnings\n\x09 * AttachParentBounds\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x90\xe3\x82\xa6\xe3\x83\xb3\xe3\x82\xb9\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xbc\xe3\x83\xab\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Bounds scale used for displaying AttachParentBounds warnings\nAttachParentBounds\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x90\xe3\x82\xa6\xe3\x83\xb3\xe3\x82\xb9\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xbc\xe3\x83\xab" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayNeedsAttachParentBounds_MetaData[] = {
		{ "Category", "Log|Component" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of AttachParentBounds warnings to display\n\x09 * AttachParentBounds\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of AttachParentBounds warnings to display\nAttachParentBounds\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayNeedsAutoManageAttachment_MetaData[] = {
		{ "Category", "Log|Audio / Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of AutoManageAttachment warnings to display\n\x09 * AutoManageAttachment\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of AutoManageAttachment warnings to display\nAutoManageAttachment\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayNeedsAudioPlayMode_MetaData[] = {
		{ "Category", "Log|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of AudioPlayMode warnings to display\n\x09 * AudioPlayMode\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of AudioPlayMode warnings to display\nAudioPlayMode\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayStaticMeshActorSameMesh_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of StaticMeshActors with the same StaticMesh to display\n\x09 * \xe5\x90\x8c\xe3\x81\x98StaticMesh\xe3\x82\x92\xe6\x8c\x81\xe3\x81\xa4StaticMeshActor\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of StaticMeshActors with the same StaticMesh to display\n\xe5\x90\x8c\xe3\x81\x98StaticMesh\xe3\x82\x92\xe6\x8c\x81\xe3\x81\xa4StaticMeshActor\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Ignore warnings for StaticMeshActors with the same StaticMesh when dynamic instancing is enabled\n\x09 * \xe8\x87\xaa\xe5\x8b\x95\xe3\x82\xa4\xe3\x83\xb3\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\xb3\xe3\x82\xb9\xe5\x8c\x96\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe5\x90\x8c\xe3\x81\x98StaticMesh\xe3\x82\x92\xe6\x8c\x81\xe3\x81\xa4StaticMeshActor\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Ignore warnings for StaticMeshActors with the same StaticMesh when dynamic instancing is enabled\n\xe8\x87\xaa\xe5\x8b\x95\xe3\x82\xa4\xe3\x83\xb3\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\xb3\xe3\x82\xb9\xe5\x8c\x96\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe5\x90\x8c\xe3\x81\x98StaticMesh\xe3\x82\x92\xe6\x8c\x81\xe3\x81\xa4StaticMeshActor\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplaySameMaterialsInMaterialSlots_MetaData[] = {
		{ "Category", "Log|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of warnings for duplicate materials in material slots\n\x09 * \xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x82\xb9\xe3\x83\xad\xe3\x83\x83\xe3\x83\x88\xe3\x81\xab\xe5\x90\x8c\xe3\x81\x98\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x99\xe3\x82\x8b\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of warnings for duplicate materials in material slots\n\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x82\xb9\xe3\x83\xad\xe3\x83\x83\xe3\x83\x88\xe3\x81\xab\xe5\x90\x8c\xe3\x81\x98\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x99\xe3\x82\x8b\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayMismatchNumOverrideMaterial_MetaData[] = {
		{ "Category", "Log|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of warnings for mismatched override material counts\n\x09 * \xe3\x82\xaa\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x89\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\xae\xe6\x95\xb0\xe3\x81\x8c\xe5\x85\x83\xe3\x81\xae\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xa8\xe9\x81\x95\xe3\x81\x86\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xab\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of warnings for mismatched override material counts\n\xe3\x82\xaa\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x89\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\xae\xe6\x95\xb0\xe3\x81\x8c\xe5\x85\x83\xe3\x81\xae\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xa8\xe9\x81\x95\xe3\x81\x86\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xab\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayMissingMaterials_MetaData[] = {
		{ "Category", "Log|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of warnings for missing materials\n\x09 * \xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\x8c\xe3\x82\xa2\xe3\x82\xb5\xe3\x82\xa4\xe3\x83\xb3\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of warnings for missing materials\n\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\x8c\xe3\x82\xa2\xe3\x82\xb5\xe3\x82\xa4\xe3\x83\xb3\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayMissingMeshes_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of warnings for missing meshes\n\x09 * \xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\x8c\xe3\x82\xa2\xe3\x82\xb5\xe3\x82\xa4\xe3\x83\xb3\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of warnings for missing meshes\n\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\x8c\xe3\x82\xa2\xe3\x82\xb5\xe3\x82\xa4\xe3\x83\xb3\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayNoLodsMeshes_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of warnings for meshes without LODs\n\x09 * LOD\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of warnings for meshes without LODs\nLOD\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayMissingComponents_MetaData[] = {
		{ "Category", "Log|Component" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of warnings for missing components\n\x09 * \xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of warnings for missing components\n\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayVertexRanking_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Number of mesh vertex count rankings to display\n\x09 * \xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of mesh vertex count rankings to display\n\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayBoneCountRanking_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Number of SkeletalMesh bone count rankings to display\n\x09 * \xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of SkeletalMesh bone count rankings to display\n\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayBoneReductionRateRanking_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Number of SkeletalMesh bone LOD ratio rankings to display\n\x09 * \xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3LOD\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of SkeletalMesh bone LOD ratio rankings to display\n\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3LOD\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayErrorNavMeshPolygons_MetaData[] = {
		{ "Category", "Log|Navigation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of warnings for buried NavMesh polygons\n\x09 * NavMesh\xe3\x81\x8c\xe5\x9f\x8b\xe3\x82\x82\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x83\x9d\xe3\x83\xaa\xe3\x82\xb4\xe3\x83\xb3\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of warnings for buried NavMesh polygons\nNavMesh\xe3\x81\x8c\xe5\x9f\x8b\xe3\x82\x82\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x83\x9d\xe3\x83\xaa\xe3\x82\xb4\xe3\x83\xb3\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DrawNavMeshPolygonTimer_MetaData[] = {
		{ "Category", "MapCheck|Navigation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Duration for drawing buried NavMesh polygons\n\x09 * NavMesh\xe3\x81\xae\xe5\x9f\x8b\xe3\x82\x82\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x83\x9d\xe3\x83\xaa\xe3\x82\xb4\xe3\x83\xb3\xe3\x82\x92\xe6\x8f\x8f\xe7\x94\xbb\xe3\x81\x99\xe3\x82\x8b\xe6\x99\x82\xe9\x96\x93\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Duration for drawing buried NavMesh polygons\nNavMesh\xe3\x81\xae\xe5\x9f\x8b\xe3\x82\x82\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x83\x9d\xe3\x83\xaa\xe3\x82\xb4\xe3\x83\xb3\xe3\x82\x92\xe6\x8f\x8f\xe7\x94\xbb\xe3\x81\x99\xe3\x82\x8b\xe6\x99\x82\xe9\x96\x93" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDisplayErrorBrushPolygons_MetaData[] = {
		{ "Category", "Log|Brush" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of warnings for brushes with holes\n\x09 * Brush\xe3\x81\xab\xe7\xa9\xb4\xe3\x81\x8c\xe7\xa9\xba\xe3\x81\x84\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of warnings for brushes with holes\nBrush\xe3\x81\xab\xe7\xa9\xb4\xe3\x81\x8c\xe7\xa9\xba\xe3\x81\x84\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningNiagaraWarmupTime_MetaData[] = {
		{ "Category", "Log|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Warning threshold for NiagaraSystem WarmupTime (sec)\n\x09 * NiagaraSystem\xe3\x81\xaeWarmupTime\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x81\x99\xe3\x82\x8b\xe6\x99\x82\xe9\x96\x93\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Warning threshold for NiagaraSystem WarmupTime (sec)\nNiagaraSystem\xe3\x81\xaeWarmupTime\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x81\x99\xe3\x82\x8b\xe6\x99\x82\xe9\x96\x93\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningNiagaraRendererCount_MetaData[] = {
		{ "Category", "Log|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max number of warnings for NiagaraSystem Renderers\n\x09 * NiagaraSystem\xe3\x81\xaeRenderer\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of warnings for NiagaraSystem Renderers\nNiagaraSystem\xe3\x81\xaeRenderer\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningNiagaraVolumeTextureSize_MetaData[] = {
		{ "Category", "Log|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Warning size for VolumeTextures used in Mesh Renderers\n\x09 * Mesh Renderer\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8bVolumeTexture\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Warning size for VolumeTextures used in Mesh Renderers\nMesh Renderer\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8bVolumeTexture\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningPostProcessPixelShaderInstructions_MetaData[] = {
		{ "Category", "MapCheck|Post Process" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Pixel shader instruction count threshold for PostProcess warnings\n\x09 * \xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x9d\xe3\x82\xb9\xe3\x83\x88\xe3\x83\x97\xe3\x83\xad\xe3\x82\xbb\xe3\x82\xb9\xe3\x81\xae\xe3\x83\x94\xe3\x82\xaf\xe3\x82\xbb\xe3\x83\xab\xe3\x82\xb7\xe3\x82\xa7\xe3\x83\xbc\xe3\x83\x80\xe3\x83\xbc\xe5\x91\xbd\xe4\xbb\xa4\xe6\x95\xb0\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pixel shader instruction count threshold for PostProcess warnings\n\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x9d\xe3\x82\xb9\xe3\x83\x88\xe3\x83\x97\xe3\x83\xad\xe3\x82\xbb\xe3\x82\xb9\xe3\x81\xae\xe3\x83\x94\xe3\x82\xaf\xe3\x82\xbb\xe3\x83\xab\xe3\x82\xb7\xe3\x82\xa7\xe3\x83\xbc\xe3\x83\x80\xe3\x83\xbc\xe5\x91\xbd\xe4\xbb\xa4\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningCompressedTextureSize_MetaData[] = {
		{ "Category", "MapCheck|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Texture size threshold for compressed texture warnings\n\x09 * \xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Texture size threshold for compressed texture warnings\n\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningUncompressedTextureSize_MetaData[] = {
		{ "Category", "MapCheck|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Texture size threshold for uncompressed texture warnings\n\x09 * \xe9\x9d\x9e\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Texture size threshold for uncompressed texture warnings\n\xe9\x9d\x9e\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LevelCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Level" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Level count score settings (n)\n\x09 * \xe3\x83\xac\xe3\x83\x99\xe3\x83\xab\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Level count score settings (n)\n\xe3\x83\xac\xe3\x83\x99\xe3\x83\xab\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapLoadTimeScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Level" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Map load time score settings (sec)\n\x09 * \xe3\x83\x9e\xe3\x83\x83\xe3\x83\x97\xe3\x83\xad\xe3\x83\xbc\xe3\x83\x89\xe6\x99\x82\xe9\x96\x93\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a \xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Map load time score settings (sec)\n\xe3\x83\x9e\xe3\x83\x83\xe3\x83\x97\xe3\x83\xad\xe3\x83\xbc\xe3\x83\x89\xe6\x99\x82\xe9\x96\x93\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a \xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Actor count score settings (n)\n\x09 * \xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor count score settings (n)\n\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentMaxCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Max component count score settings (n)\n\x09 * \xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max component count score settings (n)\n\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe6\x9c\x80\xe5\xa4\xa7\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentAverageCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Average component count score settings (n)\n\x09 * \xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe5\xb9\xb3\xe5\x9d\x87\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Average component count score settings (n)\n\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe5\xb9\xb3\xe5\x9d\x87\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorTickRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Tick ratio score settings (%)\n\x09 * \xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xaeTick\xe6\x95\xb0\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tick ratio score settings (%)\n\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xaeTick\xe6\x95\xb0\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlueprintRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Blueprint ratio score settings (%)\n\x09 * \xe3\x83\x96\xe3\x83\xab\xe3\x83\xbc\xe3\x83\x97\xe3\x83\xaa\xe3\x83\xb3\xe3\x83\x88\xe6\x95\xb0\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint ratio score settings (%)\n\xe3\x83\x96\xe3\x83\xab\xe3\x83\xbc\xe3\x83\x97\xe3\x83\xaa\xe3\x83\xb3\xe3\x83\x88\xe6\x95\xb0\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshActorSameMeshCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * StaticMeshActor with same StaticMesh score settings (n)\n\x09 * \xe5\x90\x8c\xe3\x81\x98\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\x8c\xe3\x82\xa2\xe3\x82\xb5\xe3\x82\xa4\xe3\x83\xb3\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8bStaticMeshActor\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StaticMeshActor with same StaticMesh score settings (n)\n\xe5\x90\x8c\xe3\x81\x98\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\x8c\xe3\x82\xa2\xe3\x82\xb5\xe3\x82\xa4\xe3\x83\xb3\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8bStaticMeshActor\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeedsAttachParentBoundsCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Component" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Needs AttachParentBounds count score settings (n)\n\x09 * AttachParentBounds\xe3\x81\x8c\xe5\xbf\x85\xe8\xa6\x81\xe3\x81\xaa\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Needs AttachParentBounds count score settings (n)\nAttachParentBounds\xe3\x81\x8c\xe5\xbf\x85\xe8\xa6\x81\xe3\x81\xaa\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeedsAutoManageAttachmentCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Audio / Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Needs AutoManageAttachment count score settings (n)\n\x09 * AutoManageAttachment\xe3\x81\x8c\xe5\xbf\x85\xe8\xa6\x81\xe3\x81\xaa\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Needs AutoManageAttachment count score settings (n)\nAutoManageAttachment\xe3\x81\x8c\xe5\xbf\x85\xe8\xa6\x81\xe3\x81\xaa\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeedsMultipleAudioPlayModeCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Needs multiple AudioPlayMode count score settings (n)\n\x09 * AudioPlayModeCount\xe3\x81\x8c\xe5\xbf\x85\xe8\xa6\x81\xe3\x81\xaa\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Needs multiple AudioPlayMode count score settings (n)\nAudioPlayModeCount\xe3\x81\x8c\xe5\xbf\x85\xe8\xa6\x81\xe3\x81\xaa\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SameMaterialsInMaterialSlotsCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Same materials in slots count score settings (n)\n\x09 * \xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x82\xb9\xe3\x83\xad\xe3\x83\x83\xe3\x83\x88\xe3\x81\xab\xe5\x90\x8c\xe3\x81\x98\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Same materials in slots count score settings (n)\n\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x82\xb9\xe3\x83\xad\xe3\x83\x83\xe3\x83\x88\xe3\x81\xab\xe5\x90\x8c\xe3\x81\x98\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MismatchNumOverrideMaterialCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Override material mismatch count score settings (n)\n\x09 * \xe3\x82\xaa\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x89\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\xae\xe6\x95\xb0\xe3\x81\x8c\xe5\x85\x83\xe3\x81\xae\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xa8\xe9\x81\x95\xe3\x81\x86\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Override material mismatch count score settings (n)\n\xe3\x82\xaa\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x89\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\xae\xe6\x95\xb0\xe3\x81\x8c\xe5\x85\x83\xe3\x81\xae\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xa8\xe9\x81\x95\xe3\x81\x86\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MissingMaterialsCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Missing materials count score settings (n)\n\x09 * \xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\x8c\xe3\x82\xa2\xe3\x82\xb5\xe3\x82\xa4\xe3\x83\xb3\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Missing materials count score settings (n)\n\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\x8c\xe3\x82\xa2\xe3\x82\xb5\xe3\x82\xa4\xe3\x83\xb3\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MissingMeshesCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Missing meshes count score settings (n)\n\x09 * \xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\x8c\xe3\x82\xa2\xe3\x82\xb5\xe3\x82\xa4\xe3\x83\xb3\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Missing meshes count score settings (n)\n\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\x8c\xe3\x82\xa2\xe3\x82\xb5\xe3\x82\xa4\xe3\x83\xb3\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoLodsMeshCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * No LODs mesh count score settings (n)\n\x09 * LOD\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "No LODs mesh count score settings (n)\nLOD\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MissingComponentsCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Component" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Missing components count score settings (n)\n\x09 * \xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Missing components count score settings (n)\n\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\x8c\xe5\xad\x98\xe5\x9c\xa8\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * StaticMesh vertex count ranking score settings (vtx)\n\x09 * \xe3\x82\xb9\xe3\x82\xbf\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StaticMesh vertex count ranking score settings (vtx)\n\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * StaticMesh hard-edge vertex count ranking score settings\n\x09 * \xe3\x82\xb9\xe3\x82\xbf\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StaticMesh hard-edge vertex count ranking score settings\n\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshNaniteCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Nanite StaticMesh vertex count ranking score settings (vtx)\n\x09 * Nanite\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Nanite StaticMesh vertex count ranking score settings (vtx)\nNanite\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Nanite StaticMesh hard-edge vertex count ranking score settings (vtx)\n\x09 * Nanite\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Nanite StaticMesh hard-edge vertex count ranking score settings (vtx)\nNanite\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * SkeletalMesh vertex count ranking score settings (vtx)\n\x09 * \xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SkeletalMesh vertex count ranking score settings (vtx)\n\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * SkeletalMesh hard-edge vertex count ranking score settings (vtx)\n\x09 * \xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SkeletalMesh hard-edge vertex count ranking score settings (vtx)\n\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshNaniteCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Nanite SkeletalMesh vertex count ranking score settings (vtx)\n\x09 * Nanite\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Nanite SkeletalMesh vertex count ranking score settings (vtx)\nNanite\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Nanite SkeletalMesh hard-edge vertex count ranking score settings (vtx)\n\x09 * \xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Nanite SkeletalMesh hard-edge vertex count ranking score settings (vtx)\n\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMeshCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Particle mesh vertex count ranking score settings (vtx)\n\x09 * \xe3\x83\x91\xe3\x83\xbc\xe3\x83\x86\xe3\x82\xa3\xe3\x82\xaf\xe3\x83\xab\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Particle mesh vertex count ranking score settings (vtx)\n\xe3\x83\x91\xe3\x83\xbc\xe3\x83\x86\xe3\x82\xa3\xe3\x82\xaf\xe3\x83\xab\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMeshHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Particle mesh hard-edge vertex count ranking score settings (vtx)\n\x09 * \xe3\x83\x91\xe3\x83\xbc\xe3\x83\x86\xe3\x82\xa3\xe3\x82\xaf\xe3\x83\xab\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Particle mesh hard-edge vertex count ranking score settings (vtx)\n\xe3\x83\x91\xe3\x83\xbc\xe3\x83\x86\xe3\x82\xa3\xe3\x82\xaf\xe3\x83\xab\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * SkeletalMesh bone count ranking score settings (n)\n\x09 * \xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SkeletalMesh bone count ranking score settings (n)\n\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IgnoreBoneReductionRateBoneCountThreshold_MetaData[] = {
		{ "Category", "Log|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Ignore bones when checking SkeletalMesh bone LODs (n)\n\x09 * \xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3LOD\xe3\x83\x81\xe3\x82\xa7\xe3\x83\x83\xe3\x82\xaf\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b\xe9\xaa\xa8\xe3\x81\xae\xe6\x95\xb0\xef\xbc\x88\xe6\x9c\xac\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Ignore bones when checking SkeletalMesh bone LODs (n)\n\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3LOD\xe3\x83\x81\xe3\x82\xa7\xe3\x83\x83\xe3\x82\xaf\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b\xe9\xaa\xa8\xe3\x81\xae\xe6\x95\xb0\xef\xbc\x88\xe6\x9c\xac\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneReductionRateScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * SkeletalMesh bone LOD ratio score settings (%)\n\x09 * \xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3LOD\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SkeletalMesh bone LOD ratio score settings (%)\n\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xab\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3LOD\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMeshNaniteCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Particle Nanite mesh vertex count ranking score settings (vtx)\n\x09 * \xe3\x83\x91\xe3\x83\xbc\xe3\x83\x86\xe3\x82\xa3\xe3\x82\xaf\xe3\x83\xab\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8bNanite\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Particle Nanite mesh vertex count ranking score settings (vtx)\n\xe3\x83\x91\xe3\x83\xbc\xe3\x83\x86\xe3\x82\xa3\xe3\x82\xaf\xe3\x83\xab\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8bNanite\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Particle Nanite mesh hard-edge vertex count ranking score settings (vtx)\n\x09 * \xe3\x83\x91\xe3\x83\xbc\xe3\x83\x86\xe3\x82\xa3\xe3\x82\xaf\xe3\x83\xab\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8bNanite\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Particle Nanite mesh hard-edge vertex count ranking score settings (vtx)\n\xe3\x83\x91\xe3\x83\xbc\xe3\x83\x86\xe3\x82\xa3\xe3\x82\xaf\xe3\x83\xab\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8bNanite\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\xae\xe3\x83\x8f\xe3\x83\xbc\xe3\x83\x89\xe3\x82\xa8\xe3\x83\x83\xe3\x82\xb8\xe9\xa0\x82\xe7\x82\xb9\xe6\x95\xb0\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xad\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xa0\x82\xe7\x82\xb9\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NiagaraStatefulEmitterRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Niagara stateful emitter ratio score settings (%)\n\x09 * Niagara\xe3\x81\xaeStateful\xe3\x82\xa8\xe3\x83\x9f\xe3\x83\x83\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Niagara stateful emitter ratio score settings (%)\nNiagara\xe3\x81\xaeStateful\xe3\x82\xa8\xe3\x83\x9f\xe3\x83\x83\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NiagaraEmitterOptimizationHintsScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Niagara optimization-ready emitter ratio score settings (%)\n\x09 * Niagara\xe3\x82\xa8\xe3\x83\x9f\xe3\x83\x83\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xae\xe6\x9c\x80\xe9\x81\xa9\xe5\x8c\x96\xe3\x81\xae\xe4\xbd\x99\xe5\x9c\xb0\xe3\x81\xae\xe3\x81\x82\xe3\x82\x8b\xe5\x80\x8b\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Niagara optimization-ready emitter ratio score settings (%)\nNiagara\xe3\x82\xa8\xe3\x83\x9f\xe3\x83\x83\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xae\xe6\x9c\x80\xe9\x81\xa9\xe5\x8c\x96\xe3\x81\xae\xe4\xbd\x99\xe5\x9c\xb0\xe3\x81\xae\xe3\x81\x82\xe3\x82\x8b\xe5\x80\x8b\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NiagaraSystemOptimizationHintsScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Particle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Niagara optimization-ready system ratio score settings (%)\n\x09 * NiagaraSystem\xe3\x81\xae\xe6\x9c\x80\xe9\x81\xa9\xe5\x8c\x96\xe3\x81\xae\xe4\xbd\x99\xe5\x9c\xb0\xe3\x81\xae\xe3\x81\x82\xe3\x82\x8b\xe5\x80\x8b\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Niagara optimization-ready system ratio score settings (%)\nNiagaraSystem\xe3\x81\xae\xe6\x9c\x80\xe9\x81\xa9\xe5\x8c\x96\xe3\x81\xae\xe4\xbd\x99\xe5\x9c\xb0\xe3\x81\xae\xe3\x81\x82\xe3\x82\x8b\xe5\x80\x8b\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TranslucentMaterialRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Material" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Translucent material ratio score settings (%)\n\x09 * \xe5\x8d\x8a\xe9\x80\x8f\xe6\x98\x8e\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Translucent material ratio score settings (%)\n\xe5\x8d\x8a\xe9\x80\x8f\xe6\x98\x8e\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CastDynamicShadowRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Lighting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Dynamic shadow ratio score settings (%)\n\x09 * \xe3\x83\x80\xe3\x82\xa4\xe3\x83\x8a\xe3\x83\x9f\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb7\xe3\x83\xa3\xe3\x83\x89\xe3\x82\xa6\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Dynamic shadow ratio score settings (%)\n\xe3\x83\x80\xe3\x82\xa4\xe3\x83\x8a\xe3\x83\x9f\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb7\xe3\x83\xa3\xe3\x83\x89\xe3\x82\xa6\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovableLightCastDynamicShadowCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Lighting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Movable light casting dynamic shadows count score settings (n)\n\x09 * \xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\xaa\xe3\x83\x96\xe3\x82\xb8\xe3\x82\xa7\xe3\x82\xaf\xe3\x83\x88\xe3\x81\x8cMovable\xe3\x81\xae\xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x88\xe3\x81\x8b\xe3\x82\x89\xe3\x83\x80\xe3\x82\xa4\xe3\x83\x8a\xe3\x83\x9f\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb7\xe3\x83\xa3\xe3\x83\x89\xe3\x82\xa6\xe3\x82\x92\xe6\x8a\x95\xe5\xbd\xb1\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Movable light casting dynamic shadows count score settings (n)\n\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\xaa\xe3\x83\x96\xe3\x82\xb8\xe3\x82\xa7\xe3\x82\xaf\xe3\x83\x88\xe3\x81\x8cMovable\xe3\x81\xae\xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x88\xe3\x81\x8b\xe3\x82\x89\xe3\x83\x80\xe3\x82\xa4\xe3\x83\x8a\xe3\x83\x9f\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb7\xe3\x83\xa3\xe3\x83\x89\xe3\x82\xa6\xe3\x82\x92\xe6\x8a\x95\xe5\xbd\xb1\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovableSceneLightCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Lighting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Movable light count score settings (n)\n\x09 * Movable\xe3\x81\xae\xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x88\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Movable light count score settings (n)\nMovable\xe3\x81\xae\xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x88\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverlapCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Overlap count score settings (n)\n\x09 * \xe3\x82\xaa\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x83\xa9\xe3\x83\x83\xe3\x83\x97\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Overlap count score settings (n)\n\xe3\x82\xaa\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x83\xa9\xe3\x83\x83\xe3\x83\x97\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x80\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NavMeshRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Navigation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * NavMesh ratio score settings (%)\n\x09 * NavMesh\xe3\x81\x8c\xe7\x94\x9f\xe6\x88\x90\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "NavMesh ratio score settings (%)\nNavMesh\xe3\x81\x8c\xe7\x94\x9f\xe6\x88\x90\xe3\x81\x95\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ErrorNavMeshPolygonsRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Navigation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Error NavMesh polygons ratio score settings (%)\n\x09 * NavMesh\xe3\x81\x8c\xe5\x9f\x8b\xe3\x82\x82\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x83\x9d\xe3\x83\xaa\xe3\x82\xb4\xe3\x83\xb3\xe3\x81\x8c\xe3\x81\x82\xe3\x82\x8b\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Error NavMesh polygons ratio score settings (%)\nNavMesh\xe3\x81\x8c\xe5\x9f\x8b\xe3\x82\x82\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x83\x9d\xe3\x83\xaa\xe3\x82\xb4\xe3\x83\xb3\xe3\x81\x8c\xe3\x81\x82\xe3\x82\x8b\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ErrorBrushPolygonsRatioScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Brush" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Error brush polygons ratio score settings (%)\n\x09 * Brush\xe3\x81\xab\xe7\xa9\xb4\xe3\x81\x8c\xe7\xa9\xba\xe3\x81\x84\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Error brush polygons ratio score settings (%)\nBrush\xe3\x81\xab\xe7\xa9\xb4\xe3\x81\x8c\xe7\xa9\xba\xe3\x81\x84\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe5\x89\xb2\xe5\x90\x88\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xef\xbc\x85\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PostProcessPixelShaderInstructionsScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|PostProcess" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * PostProcess pixel shader instructions score settings (inst)\n\x09 * \xe3\x83\x9d\xe3\x82\xb9\xe3\x83\x88\xe3\x83\x97\xe3\x83\xad\xe3\x82\xbb\xe3\x82\xb9\xe3\x81\xae\xe3\x83\x94\xe3\x82\xaf\xe3\x82\xbb\xe3\x83\xab\xe3\x82\xb7\xe3\x82\xa7\xe3\x83\xbc\xe3\x83\x80\xe3\x83\xbc\xe5\x91\xbd\xe4\xbb\xa4\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x91\xbd\xe4\xbb\xa4\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PostProcess pixel shader instructions score settings (inst)\n\xe3\x83\x9d\xe3\x82\xb9\xe3\x83\x88\xe3\x83\x97\xe3\x83\xad\xe3\x82\xbb\xe3\x82\xb9\xe3\x81\xae\xe3\x83\x94\xe3\x82\xaf\xe3\x82\xbb\xe3\x83\xab\xe3\x82\xb7\xe3\x82\xa7\xe3\x83\xbc\xe3\x83\x80\xe3\x83\xbc\xe5\x91\xbd\xe4\xbb\xa4\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe5\x91\xbd\xe4\xbb\xa4\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StreamingCompressedTextureSizeThreshold_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Streaming compressed texture size threshold\n\x09 * \xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\x99\xe3\x82\x8b\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xa9\x95\xe4\xbe\xa1\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Streaming compressed texture size threshold\n\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\x99\xe3\x82\x8b\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xa9\x95\xe4\xbe\xa1\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StreamingUncompressedTextureSizeThreshold_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Streaming uncompressed texture size threshold\n\x09 * \xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\x99\xe3\x82\x8b\xe9\x9d\x9e\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xa9\x95\xe4\xbe\xa1\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Streaming uncompressed texture size threshold\n\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\x99\xe3\x82\x8b\xe9\x9d\x9e\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xa9\x95\xe4\xbe\xa1\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StreamingTextureCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Streaming textures with counts exceeding the threshold (n)\n\x09 * \xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x81\xa7\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\xe4\xbb\xa5\xe4\xb8\x8a\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe6\x9e\x9a\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Streaming textures with counts exceeding the threshold (n)\n\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x81\xa7\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\xe4\xbb\xa5\xe4\xb8\x8a\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe6\x9e\x9a\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NonStreamingCompressedTextureSizeThreshold_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Non-Streaming compressed texture size threshold\n\x09 * \xe9\x9d\x9e\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xa9\x95\xe4\xbe\xa1\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Non-Streaming compressed texture size threshold\n\xe9\x9d\x9e\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xa9\x95\xe4\xbe\xa1\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NonStreamingUncompressedTextureSizeThreshold_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Non-Streaming uncompressed texture size threshold\n\x09 * \xe9\x9d\x9e\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe9\x9d\x9e\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xa9\x95\xe4\xbe\xa1\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Non-Streaming uncompressed texture size threshold\n\xe9\x9d\x9e\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe9\x9d\x9e\xe5\x9c\xa7\xe7\xb8\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\xe3\x81\xae\xe8\xa9\x95\xe4\xbe\xa1\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NonStreamingTextureCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Non-Streaming textures with counts exceeding the threshold (n)\n\x09 * \xe9\x9d\x9e\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x81\xa7\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\xe4\xbb\xa5\xe4\xb8\x8a\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe6\x9e\x9a\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Non-Streaming textures with counts exceeding the threshold (n)\n\xe9\x9d\x9e\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xaa\xe3\x83\xbc\xe3\x83\x9f\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x81\xa7\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\xe4\xbb\xa5\xe4\xb8\x8a\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe6\x9e\x9a\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StreamedInTextureCountScoreSettings_MetaData[] = {
		{ "Category", "Score Settings|Texture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Currently streamed-in textures with counts exceeding the threshold (n)\n\x09 * \xe4\xbd\xbf\xe7\x94\xa8\xe4\xb8\xad\xe3\x81\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x81\xa7\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\xe4\xbb\xa5\xe4\xb8\x8a\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe6\x9e\x9a\xef\xbc\x89\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/HealthCheckerSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Currently streamed-in textures with counts exceeding the threshold (n)\n\xe4\xbd\xbf\xe7\x94\xa8\xe4\xb8\xad\xe3\x81\xae\xe3\x83\x86\xe3\x82\xaf\xe3\x82\xb9\xe3\x83\x81\xe3\x83\xa3\xe3\x81\xa7\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\xe4\xbb\xa5\xe4\xb8\x8a\xe3\x81\xae\xe6\x95\xb0\xe3\x81\xae\xe3\x82\xb9\xe3\x82\xb3\xe3\x82\xa2\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe6\x9e\x9a\xef\xbc\x89" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UHealthCheckerSettings constinit property declarations *******************
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
// ********** End Class UHealthCheckerSettings constinit property declarations *********************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHealthCheckerSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UHealthCheckerSettings_Statics

// ********** Begin Class UHealthCheckerSettings Property Definitions ******************************
void Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bUnloadLevelsAfterCheck_SetBit(void* Obj)
{
	((UHealthCheckerSettings*)Obj)->bUnloadLevelsAfterCheck = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bUnloadLevelsAfterCheck = { "bUnloadLevelsAfterCheck", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UHealthCheckerSettings), &Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bUnloadLevelsAfterCheck_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUnloadLevelsAfterCheck_MetaData), NewProp_bUnloadLevelsAfterCheck_MetaData) };
void Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bIgnoreEditorOnlyActorsAndComponents_SetBit(void* Obj)
{
	((UHealthCheckerSettings*)Obj)->bIgnoreEditorOnlyActorsAndComponents = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bIgnoreEditorOnlyActorsAndComponents = { "bIgnoreEditorOnlyActorsAndComponents", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UHealthCheckerSettings), &Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bIgnoreEditorOnlyActorsAndComponents_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIgnoreEditorOnlyActorsAndComponents_MetaData), NewProp_bIgnoreEditorOnlyActorsAndComponents_MetaData) };
void Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bPostToMapCheck_SetBit(void* Obj)
{
	((UHealthCheckerSettings*)Obj)->bPostToMapCheck = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bPostToMapCheck = { "bPostToMapCheck", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UHealthCheckerSettings), &Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bPostToMapCheck_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPostToMapCheck_MetaData), NewProp_bPostToMapCheck_MetaData) };
void Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bPostToLog_SetBit(void* Obj)
{
	((UHealthCheckerSettings*)Obj)->bPostToLog = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bPostToLog = { "bPostToLog", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UHealthCheckerSettings), &Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bPostToLog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPostToLog_MetaData), NewProp_bPostToLog_MetaData) };
void Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bOpenReportWhenFinished_SetBit(void* Obj)
{
	((UHealthCheckerSettings*)Obj)->bOpenReportWhenFinished = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bOpenReportWhenFinished = { "bOpenReportWhenFinished", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UHealthCheckerSettings), &Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bOpenReportWhenFinished_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOpenReportWhenFinished_MetaData), NewProp_bOpenReportWhenFinished_MetaData) };
void Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bOpenMapCheckWhenFinished_SetBit(void* Obj)
{
	((UHealthCheckerSettings*)Obj)->bOpenMapCheckWhenFinished = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bOpenMapCheckWhenFinished = { "bOpenMapCheckWhenFinished", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UHealthCheckerSettings), &Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bOpenMapCheckWhenFinished_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOpenMapCheckWhenFinished_MetaData), NewProp_bOpenMapCheckWhenFinished_MetaData) };
void Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bUseUserNameInReport_SetBit(void* Obj)
{
	((UHealthCheckerSettings*)Obj)->bUseUserNameInReport = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bUseUserNameInReport = { "bUseUserNameInReport", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UHealthCheckerSettings), &Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bUseUserNameInReport_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseUserNameInReport_MetaData), NewProp_bUseUserNameInReport_MetaData) };
void Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bAddEngineVersionToSearchHints_SetBit(void* Obj)
{
	((UHealthCheckerSettings*)Obj)->bAddEngineVersionToSearchHints = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bAddEngineVersionToSearchHints = { "bAddEngineVersionToSearchHints", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UHealthCheckerSettings), &Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bAddEngineVersionToSearchHints_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAddEngineVersionToSearchHints_MetaData), NewProp_bAddEngineVersionToSearchHints_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ReportActorCategories = { "ReportActorCategories", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ReportActorCategories), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReportActorCategories_MetaData), NewProp_ReportActorCategories_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayMapLoadTimeRanking = { "MaxDisplayMapLoadTimeRanking", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayMapLoadTimeRanking), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayMapLoadTimeRanking_MetaData), NewProp_MaxDisplayMapLoadTimeRanking_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningAttachParentBoundsScale = { "WarningAttachParentBoundsScale", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, WarningAttachParentBoundsScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningAttachParentBoundsScale_MetaData), NewProp_WarningAttachParentBoundsScale_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayNeedsAttachParentBounds = { "MaxDisplayNeedsAttachParentBounds", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayNeedsAttachParentBounds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayNeedsAttachParentBounds_MetaData), NewProp_MaxDisplayNeedsAttachParentBounds_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayNeedsAutoManageAttachment = { "MaxDisplayNeedsAutoManageAttachment", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayNeedsAutoManageAttachment), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayNeedsAutoManageAttachment_MetaData), NewProp_MaxDisplayNeedsAutoManageAttachment_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayNeedsAudioPlayMode = { "MaxDisplayNeedsAudioPlayMode", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayNeedsAudioPlayMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayNeedsAudioPlayMode_MetaData), NewProp_MaxDisplayNeedsAudioPlayMode_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayStaticMeshActorSameMesh = { "MaxDisplayStaticMeshActorSameMesh", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayStaticMeshActorSameMesh), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayStaticMeshActorSameMesh_MetaData), NewProp_MaxDisplayStaticMeshActorSameMesh_MetaData) };
void Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_SetBit(void* Obj)
{
	((UHealthCheckerSettings*)Obj)->bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled = { "bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UHealthCheckerSettings), &Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_MetaData), NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplaySameMaterialsInMaterialSlots = { "MaxDisplaySameMaterialsInMaterialSlots", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplaySameMaterialsInMaterialSlots), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplaySameMaterialsInMaterialSlots_MetaData), NewProp_MaxDisplaySameMaterialsInMaterialSlots_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayMismatchNumOverrideMaterial = { "MaxDisplayMismatchNumOverrideMaterial", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayMismatchNumOverrideMaterial), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayMismatchNumOverrideMaterial_MetaData), NewProp_MaxDisplayMismatchNumOverrideMaterial_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayMissingMaterials = { "MaxDisplayMissingMaterials", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayMissingMaterials), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayMissingMaterials_MetaData), NewProp_MaxDisplayMissingMaterials_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayMissingMeshes = { "MaxDisplayMissingMeshes", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayMissingMeshes), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayMissingMeshes_MetaData), NewProp_MaxDisplayMissingMeshes_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayNoLodsMeshes = { "MaxDisplayNoLodsMeshes", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayNoLodsMeshes), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayNoLodsMeshes_MetaData), NewProp_MaxDisplayNoLodsMeshes_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayMissingComponents = { "MaxDisplayMissingComponents", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayMissingComponents), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayMissingComponents_MetaData), NewProp_MaxDisplayMissingComponents_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayVertexRanking = { "MaxDisplayVertexRanking", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayVertexRanking), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayVertexRanking_MetaData), NewProp_MaxDisplayVertexRanking_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayBoneCountRanking = { "MaxDisplayBoneCountRanking", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayBoneCountRanking), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayBoneCountRanking_MetaData), NewProp_MaxDisplayBoneCountRanking_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayBoneReductionRateRanking = { "MaxDisplayBoneReductionRateRanking", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayBoneReductionRateRanking), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayBoneReductionRateRanking_MetaData), NewProp_MaxDisplayBoneReductionRateRanking_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayErrorNavMeshPolygons = { "MaxDisplayErrorNavMeshPolygons", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayErrorNavMeshPolygons), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayErrorNavMeshPolygons_MetaData), NewProp_MaxDisplayErrorNavMeshPolygons_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_DrawNavMeshPolygonTimer = { "DrawNavMeshPolygonTimer", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, DrawNavMeshPolygonTimer), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DrawNavMeshPolygonTimer_MetaData), NewProp_DrawNavMeshPolygonTimer_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayErrorBrushPolygons = { "MaxDisplayErrorBrushPolygons", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MaxDisplayErrorBrushPolygons), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDisplayErrorBrushPolygons_MetaData), NewProp_MaxDisplayErrorBrushPolygons_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningNiagaraWarmupTime = { "WarningNiagaraWarmupTime", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, WarningNiagaraWarmupTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningNiagaraWarmupTime_MetaData), NewProp_WarningNiagaraWarmupTime_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningNiagaraRendererCount = { "WarningNiagaraRendererCount", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, WarningNiagaraRendererCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningNiagaraRendererCount_MetaData), NewProp_WarningNiagaraRendererCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningNiagaraVolumeTextureSize = { "WarningNiagaraVolumeTextureSize", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, WarningNiagaraVolumeTextureSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningNiagaraVolumeTextureSize_MetaData), NewProp_WarningNiagaraVolumeTextureSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningPostProcessPixelShaderInstructions = { "WarningPostProcessPixelShaderInstructions", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, WarningPostProcessPixelShaderInstructions), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningPostProcessPixelShaderInstructions_MetaData), NewProp_WarningPostProcessPixelShaderInstructions_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningCompressedTextureSize_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningCompressedTextureSize = { "WarningCompressedTextureSize", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, WarningCompressedTextureSize), Z_Construct_UEnum_HealthChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningCompressedTextureSize_MetaData), NewProp_WarningCompressedTextureSize_MetaData) }; // 2879030143
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningUncompressedTextureSize_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningUncompressedTextureSize = { "WarningUncompressedTextureSize", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, WarningUncompressedTextureSize), Z_Construct_UEnum_HealthChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningUncompressedTextureSize_MetaData), NewProp_WarningUncompressedTextureSize_MetaData) }; // 2879030143
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_LevelCountScoreSettings = { "LevelCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, LevelCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LevelCountScoreSettings_MetaData), NewProp_LevelCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MapLoadTimeScoreSettings = { "MapLoadTimeScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MapLoadTimeScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapLoadTimeScoreSettings_MetaData), NewProp_MapLoadTimeScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ActorCountScoreSettings = { "ActorCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ActorCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorCountScoreSettings_MetaData), NewProp_ActorCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ComponentMaxCountScoreSettings = { "ComponentMaxCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ComponentMaxCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentMaxCountScoreSettings_MetaData), NewProp_ComponentMaxCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ComponentAverageCountScoreSettings = { "ComponentAverageCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ComponentAverageCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentAverageCountScoreSettings_MetaData), NewProp_ComponentAverageCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ActorTickRatioScoreSettings = { "ActorTickRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ActorTickRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorTickRatioScoreSettings_MetaData), NewProp_ActorTickRatioScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_BlueprintRatioScoreSettings = { "BlueprintRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, BlueprintRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlueprintRatioScoreSettings_MetaData), NewProp_BlueprintRatioScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StaticMeshActorSameMeshCountScoreSettings = { "StaticMeshActorSameMeshCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, StaticMeshActorSameMeshCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshActorSameMeshCountScoreSettings_MetaData), NewProp_StaticMeshActorSameMeshCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NeedsAttachParentBoundsCountScoreSettings = { "NeedsAttachParentBoundsCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NeedsAttachParentBoundsCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeedsAttachParentBoundsCountScoreSettings_MetaData), NewProp_NeedsAttachParentBoundsCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NeedsAutoManageAttachmentCountScoreSettings = { "NeedsAutoManageAttachmentCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NeedsAutoManageAttachmentCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeedsAutoManageAttachmentCountScoreSettings_MetaData), NewProp_NeedsAutoManageAttachmentCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NeedsMultipleAudioPlayModeCountScoreSettings = { "NeedsMultipleAudioPlayModeCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NeedsMultipleAudioPlayModeCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeedsMultipleAudioPlayModeCountScoreSettings_MetaData), NewProp_NeedsMultipleAudioPlayModeCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_SameMaterialsInMaterialSlotsCountScoreSettings = { "SameMaterialsInMaterialSlotsCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, SameMaterialsInMaterialSlotsCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SameMaterialsInMaterialSlotsCountScoreSettings_MetaData), NewProp_SameMaterialsInMaterialSlotsCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MismatchNumOverrideMaterialCountScoreSettings = { "MismatchNumOverrideMaterialCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MismatchNumOverrideMaterialCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MismatchNumOverrideMaterialCountScoreSettings_MetaData), NewProp_MismatchNumOverrideMaterialCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MissingMaterialsCountScoreSettings = { "MissingMaterialsCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MissingMaterialsCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MissingMaterialsCountScoreSettings_MetaData), NewProp_MissingMaterialsCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MissingMeshesCountScoreSettings = { "MissingMeshesCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MissingMeshesCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MissingMeshesCountScoreSettings_MetaData), NewProp_MissingMeshesCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NoLodsMeshCountScoreSettings = { "NoLodsMeshCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NoLodsMeshCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoLodsMeshCountScoreSettings_MetaData), NewProp_NoLodsMeshCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MissingComponentsCountScoreSettings = { "MissingComponentsCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MissingComponentsCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MissingComponentsCountScoreSettings_MetaData), NewProp_MissingComponentsCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StaticMeshCountScoreSettings = { "StaticMeshCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, StaticMeshCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshCountScoreSettings_MetaData), NewProp_StaticMeshCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StaticMeshHardEdgeVertexCountScoreSettings = { "StaticMeshHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, StaticMeshHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshHardEdgeVertexCountScoreSettings_MetaData), NewProp_StaticMeshHardEdgeVertexCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StaticMeshNaniteCountScoreSettings = { "StaticMeshNaniteCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, StaticMeshNaniteCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshNaniteCountScoreSettings_MetaData), NewProp_StaticMeshNaniteCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings = { "StaticMeshNaniteHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, StaticMeshNaniteHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings_MetaData), NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_SkeletalMeshCountScoreSettings = { "SkeletalMeshCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, SkeletalMeshCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshCountScoreSettings_MetaData), NewProp_SkeletalMeshCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings = { "SkeletalMeshHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, SkeletalMeshHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings_MetaData), NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_SkeletalMeshNaniteCountScoreSettings = { "SkeletalMeshNaniteCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, SkeletalMeshNaniteCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshNaniteCountScoreSettings_MetaData), NewProp_SkeletalMeshNaniteCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings = { "SkeletalMeshNaniteHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, SkeletalMeshNaniteHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings_MetaData), NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ParticleMeshCountScoreSettings = { "ParticleMeshCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ParticleMeshCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMeshCountScoreSettings_MetaData), NewProp_ParticleMeshCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ParticleMeshHardEdgeVertexCountScoreSettings = { "ParticleMeshHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ParticleMeshHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMeshHardEdgeVertexCountScoreSettings_MetaData), NewProp_ParticleMeshHardEdgeVertexCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_BoneCountScoreSettings = { "BoneCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, BoneCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneCountScoreSettings_MetaData), NewProp_BoneCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_IgnoreBoneReductionRateBoneCountThreshold = { "IgnoreBoneReductionRateBoneCountThreshold", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, IgnoreBoneReductionRateBoneCountThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IgnoreBoneReductionRateBoneCountThreshold_MetaData), NewProp_IgnoreBoneReductionRateBoneCountThreshold_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_BoneReductionRateScoreSettings = { "BoneReductionRateScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, BoneReductionRateScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneReductionRateScoreSettings_MetaData), NewProp_BoneReductionRateScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ParticleMeshNaniteCountScoreSettings = { "ParticleMeshNaniteCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ParticleMeshNaniteCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMeshNaniteCountScoreSettings_MetaData), NewProp_ParticleMeshNaniteCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings = { "ParticleMeshNaniteHardEdgeVertexCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ParticleMeshNaniteHardEdgeVertexCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings_MetaData), NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NiagaraStatefulEmitterRatioScoreSettings = { "NiagaraStatefulEmitterRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NiagaraStatefulEmitterRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NiagaraStatefulEmitterRatioScoreSettings_MetaData), NewProp_NiagaraStatefulEmitterRatioScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NiagaraEmitterOptimizationHintsScoreSettings = { "NiagaraEmitterOptimizationHintsScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NiagaraEmitterOptimizationHintsScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NiagaraEmitterOptimizationHintsScoreSettings_MetaData), NewProp_NiagaraEmitterOptimizationHintsScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NiagaraSystemOptimizationHintsScoreSettings = { "NiagaraSystemOptimizationHintsScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NiagaraSystemOptimizationHintsScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NiagaraSystemOptimizationHintsScoreSettings_MetaData), NewProp_NiagaraSystemOptimizationHintsScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_TranslucentMaterialRatioScoreSettings = { "TranslucentMaterialRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, TranslucentMaterialRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TranslucentMaterialRatioScoreSettings_MetaData), NewProp_TranslucentMaterialRatioScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_CastDynamicShadowRatioScoreSettings = { "CastDynamicShadowRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, CastDynamicShadowRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CastDynamicShadowRatioScoreSettings_MetaData), NewProp_CastDynamicShadowRatioScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MovableLightCastDynamicShadowCountScoreSettings = { "MovableLightCastDynamicShadowCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MovableLightCastDynamicShadowCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovableLightCastDynamicShadowCountScoreSettings_MetaData), NewProp_MovableLightCastDynamicShadowCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MovableSceneLightCountScoreSettings = { "MovableSceneLightCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, MovableSceneLightCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovableSceneLightCountScoreSettings_MetaData), NewProp_MovableSceneLightCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_OverlapCountScoreSettings = { "OverlapCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, OverlapCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverlapCountScoreSettings_MetaData), NewProp_OverlapCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NavMeshRatioScoreSettings = { "NavMeshRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NavMeshRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NavMeshRatioScoreSettings_MetaData), NewProp_NavMeshRatioScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ErrorNavMeshPolygonsRatioScoreSettings = { "ErrorNavMeshPolygonsRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ErrorNavMeshPolygonsRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ErrorNavMeshPolygonsRatioScoreSettings_MetaData), NewProp_ErrorNavMeshPolygonsRatioScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ErrorBrushPolygonsRatioScoreSettings = { "ErrorBrushPolygonsRatioScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, ErrorBrushPolygonsRatioScoreSettings), Z_Construct_UScriptStruct_FFloatScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ErrorBrushPolygonsRatioScoreSettings_MetaData), NewProp_ErrorBrushPolygonsRatioScoreSettings_MetaData) }; // 3227664396
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_PostProcessPixelShaderInstructionsScoreSettings = { "PostProcessPixelShaderInstructionsScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, PostProcessPixelShaderInstructionsScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PostProcessPixelShaderInstructionsScoreSettings_MetaData), NewProp_PostProcessPixelShaderInstructionsScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamingCompressedTextureSizeThreshold_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamingCompressedTextureSizeThreshold = { "StreamingCompressedTextureSizeThreshold", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, StreamingCompressedTextureSizeThreshold), Z_Construct_UEnum_HealthChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StreamingCompressedTextureSizeThreshold_MetaData), NewProp_StreamingCompressedTextureSizeThreshold_MetaData) }; // 2879030143
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamingUncompressedTextureSizeThreshold_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamingUncompressedTextureSizeThreshold = { "StreamingUncompressedTextureSizeThreshold", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, StreamingUncompressedTextureSizeThreshold), Z_Construct_UEnum_HealthChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StreamingUncompressedTextureSizeThreshold_MetaData), NewProp_StreamingUncompressedTextureSizeThreshold_MetaData) }; // 2879030143
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamingTextureCountScoreSettings = { "StreamingTextureCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, StreamingTextureCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StreamingTextureCountScoreSettings_MetaData), NewProp_StreamingTextureCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NonStreamingCompressedTextureSizeThreshold_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NonStreamingCompressedTextureSizeThreshold = { "NonStreamingCompressedTextureSizeThreshold", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NonStreamingCompressedTextureSizeThreshold), Z_Construct_UEnum_HealthChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NonStreamingCompressedTextureSizeThreshold_MetaData), NewProp_NonStreamingCompressedTextureSizeThreshold_MetaData) }; // 2879030143
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NonStreamingUncompressedTextureSizeThreshold_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NonStreamingUncompressedTextureSizeThreshold = { "NonStreamingUncompressedTextureSizeThreshold", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NonStreamingUncompressedTextureSizeThreshold), Z_Construct_UEnum_HealthChecker_ETextureSize, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NonStreamingUncompressedTextureSizeThreshold_MetaData), NewProp_NonStreamingUncompressedTextureSizeThreshold_MetaData) }; // 2879030143
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NonStreamingTextureCountScoreSettings = { "NonStreamingTextureCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, NonStreamingTextureCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NonStreamingTextureCountScoreSettings_MetaData), NewProp_NonStreamingTextureCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamedInTextureCountScoreSettings = { "StreamedInTextureCountScoreSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthCheckerSettings, StreamedInTextureCountScoreSettings), Z_Construct_UScriptStruct_FIntScoreSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StreamedInTextureCountScoreSettings_MetaData), NewProp_StreamedInTextureCountScoreSettings_MetaData) }; // 4132731704
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHealthCheckerSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bUnloadLevelsAfterCheck,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bIgnoreEditorOnlyActorsAndComponents,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bPostToMapCheck,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bPostToLog,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bOpenReportWhenFinished,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bOpenMapCheckWhenFinished,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bUseUserNameInReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bAddEngineVersionToSearchHints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ReportActorCategories,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayMapLoadTimeRanking,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningAttachParentBoundsScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayNeedsAttachParentBounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayNeedsAutoManageAttachment,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayNeedsAudioPlayMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayStaticMeshActorSameMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_bSkipStaticMeshActorSameMeshCheckIfDynamicInstancingEnabled,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplaySameMaterialsInMaterialSlots,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayMismatchNumOverrideMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayMissingMaterials,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayMissingMeshes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayNoLodsMeshes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayMissingComponents,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayVertexRanking,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayBoneCountRanking,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayBoneReductionRateRanking,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayErrorNavMeshPolygons,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_DrawNavMeshPolygonTimer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MaxDisplayErrorBrushPolygons,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningNiagaraWarmupTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningNiagaraRendererCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningNiagaraVolumeTextureSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningPostProcessPixelShaderInstructions,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningCompressedTextureSize_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningCompressedTextureSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningUncompressedTextureSize_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_WarningUncompressedTextureSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_LevelCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MapLoadTimeScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ActorCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ComponentMaxCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ComponentAverageCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ActorTickRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_BlueprintRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StaticMeshActorSameMeshCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NeedsAttachParentBoundsCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NeedsAutoManageAttachmentCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NeedsMultipleAudioPlayModeCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_SameMaterialsInMaterialSlotsCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MismatchNumOverrideMaterialCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MissingMaterialsCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MissingMeshesCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NoLodsMeshCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MissingComponentsCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StaticMeshCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StaticMeshHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StaticMeshNaniteCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StaticMeshNaniteHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_SkeletalMeshCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_SkeletalMeshHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_SkeletalMeshNaniteCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_SkeletalMeshNaniteHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ParticleMeshCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ParticleMeshHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_BoneCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_IgnoreBoneReductionRateBoneCountThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_BoneReductionRateScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ParticleMeshNaniteCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ParticleMeshNaniteHardEdgeVertexCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NiagaraStatefulEmitterRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NiagaraEmitterOptimizationHintsScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NiagaraSystemOptimizationHintsScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_TranslucentMaterialRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_CastDynamicShadowRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MovableLightCastDynamicShadowCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_MovableSceneLightCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_OverlapCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NavMeshRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ErrorNavMeshPolygonsRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_ErrorBrushPolygonsRatioScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_PostProcessPixelShaderInstructionsScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamingCompressedTextureSizeThreshold_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamingCompressedTextureSizeThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamingUncompressedTextureSizeThreshold_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamingUncompressedTextureSizeThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamingTextureCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NonStreamingCompressedTextureSizeThreshold_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NonStreamingCompressedTextureSizeThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NonStreamingUncompressedTextureSizeThreshold_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NonStreamingUncompressedTextureSizeThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_NonStreamingTextureCountScoreSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthCheckerSettings_Statics::NewProp_StreamedInTextureCountScoreSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthCheckerSettings_Statics::PropPointers) < 2048);
// ********** End Class UHealthCheckerSettings Property Definitions ********************************
UObject* (*const Z_Construct_UClass_UHealthCheckerSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_HealthChecker,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthCheckerSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UHealthCheckerSettings_Statics::ClassParams = {
	&UHealthCheckerSettings::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UHealthCheckerSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UHealthCheckerSettings_Statics::PropPointers),
	0,
	0x000800A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthCheckerSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UHealthCheckerSettings_Statics::Class_MetaDataParams)
};
void UHealthCheckerSettings::StaticRegisterNativesUHealthCheckerSettings()
{
}
UClass* Z_Construct_UClass_UHealthCheckerSettings()
{
	if (!Z_Registration_Info_UClass_UHealthCheckerSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHealthCheckerSettings.OuterSingleton, Z_Construct_UClass_UHealthCheckerSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UHealthCheckerSettings.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UHealthCheckerSettings);
UHealthCheckerSettings::~UHealthCheckerSettings() {}
// ********** End Class UHealthCheckerSettings *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h__Script_HealthChecker_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UHealthCheckerSettings, UHealthCheckerSettings::StaticClass, TEXT("UHealthCheckerSettings"), &Z_Registration_Info_UClass_UHealthCheckerSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHealthCheckerSettings), 3907307342U) },
	};
}; // Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h__Script_HealthChecker_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h__Script_HealthChecker_940518401{
	TEXT("/Script/HealthChecker"),
	Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h__Script_HealthChecker_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_workspace_code_cpp_ue_5_7_CustonPlugins_Plugins_HealthChecker_Source_HealthChecker_Public_HealthCheckerSettings_h__Script_HealthChecker_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
