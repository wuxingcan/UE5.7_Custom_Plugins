// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonEFX.h"

#include "CommonEFXExporter.h"

#include "Common/TcpListener.h"
#include "Common/TcpSocketBuilder.h"
#include "ContentBrowserDataMenuContexts.h"
#include "ContentBrowserItem.h"
#include "ContentBrowserModule.h"
#include "ContentBrowserMenuContexts.h"
#include "Framework/Notifications/NotificationManager.h"
#include "HAL/IConsoleManager.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Misc/MessageDialog.h"
#include "Misc/Paths.h"
#include "NiagaraSystem.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Styling/AppStyle.h"
#include "ToolMenus.h"
#include "Widgets/Notifications/SNotificationList.h"

DEFINE_LOG_CATEGORY_STATIC(LogCommonEFX, Log, All);

#define LOCTEXT_NAMESPACE "FCommonEFXModule"

namespace
{
	/** Port the plugin listens on for import requests. */
	constexpr int32 ImportListenerPort = 11788;

	/** Snapshot that is imported whenever a message is received on the listener port. */
	const TCHAR* const FixedSnapshotFile =
		TEXT("D:/workspace/code/cpp/ue/5.5/CustonPlugins/Saved/CommonEFX/NS_DragonFlame_Fire.niagara.json");

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

	void OnImportFromFileTo(const FString& DestinationPath)
	{
		FString NewAssetPath;
		FString Error;
		if (FCommonEFXExporter::ImportSystemFromFileWithDialog(NewAssetPath, Error, DestinationPath))
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

	void OnImportFromFile()
	{
		OnImportFromFileTo(FString());
	}

	FString NormalizeContentPath(FString Path)
	{
		Path.TrimStartAndEndInline();
		if (Path.StartsWith(TEXT("/All/")))
		{
			Path.RightChopInline(4);
		}
		if (Path.StartsWith(TEXT("/All")))
		{
			Path.RightChopInline(4);
		}
		if (!Path.StartsWith(TEXT("/")))
		{
			Path = TEXT("/") + Path;
		}
		return Path;
	}

	TArray<FString> GetFolderContextPaths(const FToolMenuSection& InSection)
	{
		TArray<FString> SelectedPaths;
		if (const UContentBrowserFolderContext* FolderContext = InSection.FindContext<UContentBrowserFolderContext>())
		{
			SelectedPaths = FolderContext->SelectedPackagePaths;
		}
		if (SelectedPaths.Num() == 0)
		{
			if (const UContentBrowserDataMenuContext_FolderMenu* DataContext = InSection.FindContext<UContentBrowserDataMenuContext_FolderMenu>())
			{
				for (const FContentBrowserItem& Item : DataContext->SelectedItems)
				{
					SelectedPaths.Add(Item.GetVirtualPath().ToString());
				}
			}
		}
		return SelectedPaths;
	}

	/** Headless verification: export a system, rebuild it from the snapshot and export the rebuild for diffing. */
	void OnRoundTrip(const TArray<FString>& Args)
	{
		if (Args.Num() < 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Usage: CommonEFX.RoundTrip <AssetPath> [OutputDirectory]"));
			return;
		}

		const FString OutputDirectory = Args.Num() > 1
			? Args[1]
			: FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("CommonEFX"), TEXT("RoundTrip"));

		FString SourceFile;
		FString RebuiltFile;
		FString Error;
		if (FCommonEFXExporter::RunRoundTripCheck(Args[0], OutputDirectory, SourceFile, RebuiltFile, Error))
		{
			UE_LOG(LogTemp, Display, TEXT("CommonEFX.RoundTrip succeeded. source=%s rebuilt=%s"), *SourceFile, *RebuiltFile);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CommonEFX.RoundTrip failed: %s"), *Error);
		}
	}

	FAutoConsoleCommand GRoundTripCommand(
		TEXT("CommonEFX.RoundTrip"),
		TEXT("CommonEFX.RoundTrip <AssetPath> [OutputDirectory]: exports, rebuilds and re-exports a Niagara system."),
		FConsoleCommandWithArgsDelegate::CreateStatic(&OnRoundTrip));
}

void FCommonEFXModule::StartupModule()
{
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCommonEFXModule::RegisterMenus));

	StartImportListener();
}

void FCommonEFXModule::ShutdownModule()
{
	StopImportListener();

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

void FCommonEFXModule::StartImportListener()
{
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (!SocketSubsystem)
	{
		UE_LOG(LogCommonEFX, Error, TEXT("无法获取网络子系统，端口 %d 未监听。"), ImportListenerPort);
		return;
	}

	const FIPv4Endpoint ListenEndpoint(FIPv4Address::Any, ImportListenerPort);
	ImportListenerSocket = FTcpSocketBuilder(TEXT("CommonEFX.ImportListener"))
		.AsReusable(true)
		.BoundToEndpoint(ListenEndpoint)
		.Listening(8);

	if (!ImportListenerSocket)
	{
		UE_LOG(LogCommonEFX, Error, TEXT("无法监听端口 %d，可能已被其他程序占用。"), ImportListenerPort);
		return;
	}

	ImportListener = MakeShared<FTcpListener>(*ImportListenerSocket, FTimespan::FromMilliseconds(100), true);
	ImportListener->OnConnectionAccepted().BindRaw(this, &FCommonEFXModule::HandleImportConnection);

	ImportTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateRaw(this, &FCommonEFXModule::TickImportRequests), 0.1f);

	UE_LOG(LogCommonEFX, Display, TEXT("CommonEFX 正在监听端口 %d，收到消息后将导入 %s。"), ImportListenerPort, FixedSnapshotFile);
}

void FCommonEFXModule::StopImportListener()
{
	if (ImportTickerHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(ImportTickerHandle);
		ImportTickerHandle.Reset();
	}

	if (ImportListener.IsValid())
	{
		ImportListener.Reset();
	}

	if (ImportListenerSocket)
	{
		if (ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM))
		{
			SocketSubsystem->DestroySocket(ImportListenerSocket);
		}
		ImportListenerSocket = nullptr;
	}
}

bool FCommonEFXModule::HandleImportConnection(FSocket* ConnectionSocket, const FIPv4Endpoint& RemoteEndpoint)
{
	if (!ConnectionSocket)
	{
		return false;
	}

	// Give the client a short window to deliver its payload without blocking the listener thread for long.
	const bool bReadable = ConnectionSocket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromMilliseconds(500));

	uint8 Buffer[256];
	int32 BytesRead = 0;
	const bool bReceivedMessage = bReadable
		&& ConnectionSocket->Recv(Buffer, int32(UE_ARRAY_COUNT(Buffer)), BytesRead)
		&& BytesRead > 0;
	if (bReceivedMessage)
	{
		UE_LOG(LogCommonEFX, Display, TEXT("收到来自 %s 的导入请求（%d 字节）。"), *RemoteEndpoint.ToString(), BytesRead);
		bImportRequested.Store(true);

		// Acknowledge the request; the actual import runs on the game thread.
		const ANSICHAR Response[] = "OK";
		int32 BytesSent = 0;
		ConnectionSocket->Send(reinterpret_cast<const uint8*>(Response), int32(UE_ARRAY_COUNT(Response)) - 1, BytesSent);
	}
	else
	{
		UE_LOG(LogCommonEFX, Warning, TEXT("来自 %s 的连接没有发送消息，已忽略。"), *RemoteEndpoint.ToString());
	}

	// Returning false makes FTcpListener close and destroy the connection socket.
	return false;
}

bool FCommonEFXModule::TickImportRequests(float DeltaTime)
{
	if (bImportRequested.Exchange(false))
	{
		ImportFixedSnapshot();
	}

	return true;
}

void FCommonEFXModule::ImportFixedSnapshot()
{
	const FString SnapshotFile(FixedSnapshotFile);
	if (!FPaths::FileExists(SnapshotFile))
	{
		UE_LOG(LogCommonEFX, Error, TEXT("导入失败：参数文件不存在：%s"), *SnapshotFile);
		ShowNotification(
			FText::Format(LOCTEXT("NetworkImportMissingFile", "参数文件不存在：{0}"), FText::FromString(SnapshotFile)),
			false);
		return;
	}

	FString Error;
	if (UNiagaraSystem* System = FCommonEFXExporter::ImportSystemFromFile(SnapshotFile, Error))
	{
		UE_LOG(LogCommonEFX, Display, TEXT("已根据网络请求从 %s 重建 Niagara 特效：%s"), *SnapshotFile, *System->GetPathName());
		ShowNotification(
			FText::Format(LOCTEXT("NetworkImportSuccess", "已从参数文件还原 Niagara 效果：{0}"), FText::FromString(System->GetPathName())),
			true);
	}
	else
	{
		UE_LOG(LogCommonEFX, Error, TEXT("根据网络请求导入失败：%s"), *Error);
		ShowNotification(
			FText::Format(LOCTEXT("NetworkImportFailed", "Niagara 效果还原失败：{0}"), FText::FromString(Error)),
			false);
	}
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
			LOCTEXT("ExportSelectedTooltip", "读取内容浏览器中选中的 Niagara System，导出系统设置、用户参数、发射器、渲染器与节点图"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("Icons.Export")),
			FUIAction(FExecuteAction::CreateStatic(&OnExportSelected)));

		Section.AddMenuEntry(
			"CommonEFXImportFromFile",
			LOCTEXT("ImportFromFile", "从参数文件还原 Niagara 效果..."),
			LOCTEXT("ImportFromFileTooltip", "读取参数文件，不依赖原资产，直接新建一个 Niagara System 并还原效果"),
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
			LOCTEXT("ImportAssetTooltip", "读取参数文件，不依赖原资产，直接新建一个 Niagara System 并还原效果"),
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
					LOCTEXT("ExportAssetTooltip", "导出该 Niagara System 的系统设置、用户参数、发射器、渲染器与节点图"),
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

	// Content Browser folder context menu (must be a dynamic entry or UE 5.5 drops it).
	if (UToolMenu* FolderMenu = UToolMenus::Get()->ExtendMenu(TEXT("ContentBrowser.FolderContextMenu")))
	{
		FToolMenuSection& Section = FolderMenu->FindOrAddSection("CommonEFX");
		Section.AddDynamicEntry(
			"CommonEFXFolderEntry",
			FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection)
			{
				const TArray<FString> SelectedPaths = GetFolderContextPaths(InSection);
				FString DestinationPath;
				if (SelectedPaths.Num() > 0)
				{
					DestinationPath = NormalizeContentPath(SelectedPaths[0]);
				}

				InSection.AddMenuEntry(
					"CommonEFXImportFolder",
					LOCTEXT("ImportFolder", "从参数文件还原 Niagara 效果..."),
					LOCTEXT("ImportFolderTooltip", "读取参数文件，在当前文件夹新建 Niagara System 并还原效果"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("Icons.Import")),
					FUIAction(FExecuteAction::CreateLambda([DestinationPath]()
					{
						OnImportFromFileTo(DestinationPath);
					})));

				InSection.AddMenuEntry(
					"CommonEFXExportFolder",
					LOCTEXT("ExportFolder", "导出选中的 Niagara 参数..."),
					LOCTEXT("ExportFolderTooltip", "读取内容浏览器中选中的 Niagara System，导出系统设置、用户参数、发射器、渲染器与节点图"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("Icons.Export")),
					FUIAction(FExecuteAction::CreateStatic(&OnExportSelected)));
			}));
	}

	UE_LOG(LogTemp, Display, TEXT("CommonEFX: menus registered (Tools, asset context, folder context)."));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCommonEFXModule, CommonEFX)
