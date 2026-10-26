// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonEFX.h"

#include "CommonEFXExporter.h"

#include "ContentBrowserModule.h"
#include "ContentBrowserMenuContexts.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Misc/MessageDialog.h"
#include "NiagaraSystem.h"
#include "Styling/AppStyle.h"
#include "ToolMenus.h"
#include "Widgets/Notifications/SNotificationList.h"

#define LOCTEXT_NAMESPACE "FCommonEFXModule"

namespace
{
	void ShowNotification(const FText& Message, bool bSuccess)
	{
		FNotificationInfo Info(Message);
		Info.ExpireDuration = bSuccess ? 5.0f : 8.0f;
		Info.bUseSuccessFailIcons = true;
		Info.bFireAndForget = true;

		if (TSharedPtr<SNotificationItem> Item = FSlateNotificationManager::Get().AddNotification(Info))
		{
			Item->SetCompletionState(bSuccess ? SNotificationItem::CS_Success : SNotificationItem::CS_Fail);
		}
	}

	void ShowError(const FString& Error)
	{
		if (!Error.IsEmpty())
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Error), LOCTEXT("CommonEFXErrorTitle", "CommonEFX"));
		}
	}

	void OnExportSelected()
	{
		FString File;
		FString Error;
		if (FCommonEFXExporter::ExportSelectedSystemToFile(File, Error))
		{
			ShowNotification(
				FText::Format(LOCTEXT("ExportSuccess", "Niagara 参数已导出到：{0}"), FText::FromString(File)),
				true);
		}
		else
		{
			ShowError(Error);
		}
	}

	void OnImportFromFile()
	{
		FString NewAssetPath;
		FString Error;
		if (FCommonEFXExporter::ImportSystemFromFileWithDialog(NewAssetPath, Error))
		{
			ShowNotification(
				FText::Format(LOCTEXT("ImportSuccess", "已从参数文件还原 Niagara 效果：{0}"), FText::FromString(NewAssetPath)),
				true);
		}
		else
		{
			ShowError(Error);
		}
	}
}

void FCommonEFXModule::StartupModule()
{
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCommonEFXModule::RegisterMenus));
}

void FCommonEFXModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

void FCommonEFXModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	// Level Editor / Main Frame -> Tools
	if (UToolMenu* ToolsMenu = UToolMenus::Get()->ExtendMenu(TEXT("MainFrame.MainMenu.Tools")))
	{
		FToolMenuSection& Section = ToolsMenu->FindOrAddSection("CommonEFX");
		Section.AddMenuEntry(
			"CommonEFXExportSelected",
			LOCTEXT("ExportSelected", "导出选中的 Niagara 参数..."),
			LOCTEXT("ExportSelectedTooltip", "读取内容浏览器中选中的 Niagara System，导出所有节点参数并标记修改值/默认值"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("Icons.Export")),
			FUIAction(FExecuteAction::CreateStatic(&OnExportSelected)));

		Section.AddMenuEntry(
			"CommonEFXImportFromFile",
			LOCTEXT("ImportFromFile", "从参数文件还原 Niagara 效果..."),
			LOCTEXT("ImportFromFileTooltip", "读取 Niagara 参数文件，复制原始系统并把记录的修改值还原到新资产"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("Icons.Import")),
			FUIAction(FExecuteAction::CreateStatic(&OnImportFromFile)));
	}

	// Content Browser asset context menu
	if (UToolMenu* AssetMenu = UToolMenus::Get()->ExtendMenu(TEXT("ContentBrowser.AssetContextMenu")))
	{
		FToolMenuSection& Section = AssetMenu->FindOrAddSection("CommonEFX");

		// Restoring always starts from a snapshot file, so this entry is shown for every asset.
		Section.AddMenuEntry(
			"CommonEFXImportAsset",
			LOCTEXT("ImportAsset", "从参数文件还原 Niagara 效果..."),
			LOCTEXT("ImportAssetTooltip", "读取 Niagara 参数文件，复制原始系统并把记录的参数值还原到新资产"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("Icons.Import")),
			FUIAction(FExecuteAction::CreateStatic(&OnImportFromFile)));

		Section.AddDynamicEntry(
			"CommonEFXAssetEntry",
			FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection)
			{
				const UContentBrowserAssetContextMenuContext* Context =
					InSection.FindContext<UContentBrowserAssetContextMenuContext>();
				if (!Context)
				{
					return;
				}

				TArray<FAssetData> SystemAssets;
				for (const FAssetData& Asset : Context->SelectedAssets)
				{
					if (Asset.IsInstanceOf<UNiagaraSystem>())
					{
						SystemAssets.Add(Asset);
					}
				}

				if (SystemAssets.Num() == 0)
				{
					return;
				}

				InSection.AddMenuEntry(
					"CommonEFXExportAsset",
					LOCTEXT("ExportAsset", "导出 Niagara 参数..."),
					LOCTEXT("ExportAssetTooltip", "导出该 Niagara System 的所有节点参数，并标记修改值与默认值"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("Icons.Export")),
					FUIAction(FExecuteAction::CreateLambda([SystemAssets]()
					{
						UNiagaraSystem* System = Cast<UNiagaraSystem>(SystemAssets[0].GetAsset());
						if (!System)
						{
							return;
						}

						FString File;
						FString Error;
						if (FCommonEFXExporter::ExportSystemToFileWithDialog(System, File, Error))
						{
							ShowNotification(
								FText::Format(LOCTEXT("ExportSuccess", "Niagara 参数已导出到：{0}"), FText::FromString(File)),
								true);
						}
						else
						{
							ShowError(Error);
						}
					})));
			}));
	}

	// Content Browser folder context menu
	if (UToolMenu* FolderMenu = UToolMenus::Get()->ExtendMenu(TEXT("ContentBrowser.FolderContextMenu")))
	{
		FToolMenuSection& Section = FolderMenu->FindOrAddSection("CommonEFX");

		Section.AddMenuEntry(
			"CommonEFXExportFolder",
			LOCTEXT("ExportFolder", "导出选中的 Niagara 参数..."),
			LOCTEXT("ExportFolderTooltip", "读取内容浏览器中选中的 Niagara System，导出所有节点参数并标记修改值/默认值"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("Icons.Export")),
			FUIAction(FExecuteAction::CreateStatic(&OnExportSelected)));

		Section.AddMenuEntry(
			"CommonEFXImportFolder",
			LOCTEXT("ImportFolder", "从参数文件还原 Niagara 效果..."),
			LOCTEXT("ImportFolderTooltip", "读取 Niagara 参数文件，复制原始系统并把记录的参数值还原到新资产"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("Icons.Import")),
			FUIAction(FExecuteAction::CreateStatic(&OnImportFromFile)));
	}

	UE_LOG(LogTemp, Display, TEXT("CommonEFX: menus registered (Tools, asset context, folder context)."));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCommonEFXModule, CommonEFX)
