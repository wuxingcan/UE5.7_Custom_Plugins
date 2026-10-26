// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatchScreenShot.h"
#include "SBatchScreenShotPanel.h"

#include "ContentBrowserDataMenuContexts.h"
#include "ContentBrowserMenuContexts.h"
#include "Styling/AppStyle.h"
#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "FBatchScreenShotModule"

void FBatchScreenShotModule::StartupModule()
{
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBatchScreenShotModule::RegisterMenus));
}

void FBatchScreenShotModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

void FBatchScreenShotModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("ContentBrowser.FolderContextMenu");
	FToolMenuSection& Section = Menu->FindOrAddSection("BatchScreenShot");
	Section.AddDynamicEntry("BatchScreenShotEntry", FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection)
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
			"BatchScreenShotOpen",
			LOCTEXT("BatchScreenShot", "批量截图"),
			LOCTEXT("BatchScreenShotTooltip", "列出目录下所有 Level Sequence，批量高分辨率截图"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Visible"),
			FUIAction(FExecuteAction::CreateLambda([SelectedPaths]()
			{
				SBatchScreenShotPanel::Open(SelectedPaths);
			}))
		);
	}));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBatchScreenShotModule, BatchScreenShot)
