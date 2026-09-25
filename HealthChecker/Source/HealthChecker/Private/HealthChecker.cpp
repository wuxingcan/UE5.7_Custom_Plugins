// Copyright UMIUSHI Inc. All Rights Reserved.

#include "HealthChecker.h"
#include "HealthCheckerStyle.h"
#include "SHealthCheckerPanel.h"
#include "ToolMenus.h"
#include "HealthCheckerTypes.h"
#include "HealthCheckerScoreSettingsCustomization.h"
#include "ContentBrowserMenuContexts.h"
#include "ContentBrowserDataMenuContexts.h"

#define LOCTEXT_NAMESPACE "HealthChecker"

void FHealthCheckerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FHealthCheckerStyle::Initialize();
	FHealthCheckerStyle::ReloadTextures();

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FHealthCheckerModule::RegisterMenus));

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	static TArray<FName> ScoreSettingsStructNames = { FIntScoreSettings::StaticStruct()->GetFName(), FFloatScoreSettings::StaticStruct()->GetFName() };
	for(const FName& ScoreSettingsStructName : ScoreSettingsStructNames)
	{
		PropertyModule.RegisterCustomPropertyTypeLayout(
			ScoreSettingsStructName,
			FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FHealthCheckerScoreSettingsCustomization::MakeInstance)
		);
	}
}

void FHealthCheckerModule::ShutdownModule()
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

	FHealthCheckerStyle::Shutdown();
}

void FHealthCheckerModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("ContentBrowser.FolderContextMenu");
	FToolMenuSection& Section = Menu->FindOrAddSection("HealthChecker");
	Section.AddDynamicEntry("HealthCheckerCheckAssets", FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection)
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
			"HealthCheckerCheckAssets",
			LOCTEXT("CheckAssets", "检测资产"),
			LOCTEXT("CheckAssetsTooltip", "打开资产检测窗口"),
			FSlateIcon(FHealthCheckerStyle::GetStyleSetName(), "HealthChecker.MenuIcon"),
			FUIAction(FExecuteAction::CreateLambda([SelectedPaths]()
			{
				SHealthCheckerPanel::Open(SelectedPaths);
			}))
		);
	}));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHealthCheckerModule, HealthChecker)
