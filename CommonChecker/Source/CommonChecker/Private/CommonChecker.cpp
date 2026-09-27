// Copyright UMIUSHI Inc. All Rights Reserved.

#include "CommonChecker.h"
#include "CommonCheckerStyle.h"
#include "SCommonCheckerPanel.h"
#include "ToolMenus.h"
#include "CommonCheckerTypes.h"
#include "CommonCheckerScoreSettingsCustomization.h"
#include "ContentBrowserMenuContexts.h"
#include "ContentBrowserDataMenuContexts.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "CommonChecker"

void FCommonCheckerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCommonCheckerStyle::Initialize();
	FCommonCheckerStyle::ReloadTextures();

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCommonCheckerModule::RegisterMenus));

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	static TArray<FName> ScoreSettingsStructNames = { FIntScoreSettings::StaticStruct()->GetFName(), FFloatScoreSettings::StaticStruct()->GetFName() };
	for(const FName& ScoreSettingsStructName : ScoreSettingsStructNames)
	{
		PropertyModule.RegisterCustomPropertyTypeLayout(
			ScoreSettingsStructName,
			FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FCommonCheckerScoreSettingsCustomization::MakeInstance)
		);
	}
}

void FCommonCheckerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module. For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if(FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		static TArray<FName> ScoreSettingsStructNames = { FIntScoreSettings::StaticStruct()->GetFName(), FFloatScoreSettings::StaticStruct()->GetFName() };
		for(const FName& ScoreSettingsStructName : ScoreSettingsStructNames)
		{
			PropertyModule.UnregisterCustomPropertyTypeLayout(ScoreSettingsStructName);
		}
	}

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCommonCheckerStyle::Shutdown();
}

void FCommonCheckerModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("ContentBrowser.FolderContextMenu");
	FToolMenuSection& Section = Menu->FindOrAddSection("CommonChecker");
	Section.AddDynamicEntry("CommonCheckerCheckAssets", FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection)
	{
		TArray<FString> SelectedPaths;
		if(const UContentBrowserFolderContext* FolderContext = InSection.FindContext<UContentBrowserFolderContext>())
		{
			SelectedPaths = FolderContext->SelectedPackagePaths;
		}
		if(SelectedPaths.Num() == 0)
		{
			if(const UContentBrowserDataMenuContext_FolderMenu* DataContext = InSection.FindContext<UContentBrowserDataMenuContext_FolderMenu>())
			{
				for(const FContentBrowserItem& Item : DataContext->SelectedItems)
				{
					SelectedPaths.Add(Item.GetVirtualPath().ToString());
				}
			}
		}

		InSection.AddMenuEntry(
			"CommonCheckerCheckAssets",
			LOCTEXT("CheckAssets", "检测资产"),
			LOCTEXT("CheckAssetsTooltip", "打开资产检测窗口"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Search"),
			FUIAction(FExecuteAction::CreateLambda([SelectedPaths]()
			{
				SCommonCheckerPanel::Open(SelectedPaths);
			}))
		);
	}));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCommonCheckerModule, CommonChecker)
