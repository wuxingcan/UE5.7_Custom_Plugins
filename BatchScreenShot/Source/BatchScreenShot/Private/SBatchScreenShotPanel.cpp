// Copyright Epic Games, Inc. All Rights Reserved.

#include "SBatchScreenShotPanel.h"
#include "BatchScreenShotRunner.h"

#include "Subsystems/AssetEditorSubsystem.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ContentBrowserModule.h"
#include "Editor.h"
#include "Framework/Application/SlateApplication.h"
#include "IContentBrowserSingleton.h"
#include "LevelSequence.h"
#include "LevelSequenceEditorBlueprintLibrary.h"
#include "Styling/AppStyle.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "BatchScreenShot"

namespace
{
	static TWeakPtr<SWindow> GBatchScreenShotWindow;
	static TWeakPtr<SBatchScreenShotPanel> GBatchScreenShotPanel;
	static TSharedPtr<FBatchScreenShotRunner> GBatchScreenShotRunner;

	FString NormalizeFolderPath(FString Path)
	{
		Path.ReplaceInline(TEXT("\\"), TEXT("/"));
		Path.RemoveFromStart(TEXT("/All"));
		if(Path.StartsWith(TEXT("/Game")) || Path.StartsWith(TEXT("/Engine")) || Path.StartsWith(TEXT("/Plugins")))
		{
			return Path;
		}
		if(!Path.StartsWith(TEXT("/")))
		{
			Path = TEXT("/") + Path;
		}
		return Path;
	}
}

void SBatchScreenShotPanel::Open(const TArray<FString>& InFolderPaths)
{
	if(TSharedPtr<SWindow> ExistingWindow = GBatchScreenShotWindow.Pin())
	{
		if(TSharedPtr<SBatchScreenShotPanel> ExistingPanel = GBatchScreenShotPanel.Pin())
		{
			ExistingPanel->SetFolderPaths(InFolderPaths);
		}
		ExistingWindow->BringToFront(true);
		return;
	}

	TSharedRef<SBatchScreenShotPanel> Panel = SNew(SBatchScreenShotPanel).FolderPaths(InFolderPaths);
	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(LOCTEXT("WindowTitle", "批量截图"))
		.ClientSize(FVector2D(720.f, 640.f))
		.SupportsMaximize(true)
		.SupportsMinimize(true)
		[
			Panel
		];

	GBatchScreenShotWindow = Window;
	GBatchScreenShotPanel = Panel;
	FSlateApplication::Get().AddWindow(Window);
}

void SBatchScreenShotPanel::SetFolderPaths(const TArray<FString>& InFolderPaths)
{
	FolderPaths.Reset();
	for(const FString& Path : InFolderPaths)
	{
		FolderPaths.Add(NormalizeFolderPath(Path));
	}

	if(FolderPathText.IsValid())
	{
		FolderPathText->SetText(GetFolderPathText());
	}

	RefreshSequenceList();
}

void SBatchScreenShotPanel::Construct(const FArguments& InArgs)
{
	for(const FString& Path : InArgs._FolderPaths)
	{
		FolderPaths.Add(NormalizeFolderPath(Path));
	}

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(12.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 0.f, 0.f, 8.f)
			[
				SAssignNew(FolderPathText, STextBlock)
				.Text(GetFolderPathText())
				.AutoWrapText(true)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 0.f, 0.f, 8.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 8.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("SelectAll", "全选"))
					.IsEnabled_Lambda([this]() { return !bIsRunning; })
					.OnClicked(this, &SBatchScreenShotPanel::OnSelectAllClicked)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 16.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("DeselectAll", "取消全选"))
					.IsEnabled_Lambda([this]() { return !bIsRunning; })
					.OnClicked(this, &SBatchScreenShotPanel::OnDeselectAllClicked)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SAssignNew(HideSkeletalCheckBox, SCheckBox)
					.IsEnabled_Lambda([this]() { return !bIsRunning; })
					.IsChecked_Lambda([this]()
					{
						return bHideSkeletalMeshes ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
					})
					.OnCheckStateChanged_Lambda([this](ECheckBoxState NewState)
					{
						bHideSkeletalMeshes = (NewState == ECheckBoxState::Checked);
					})
					[
						SNew(STextBlock)
						.Text(LOCTEXT("HideSkeletal", "隐藏骨骼网格体"))
						.ToolTipText(LOCTEXT("HideSkeletalTip", "勾选后截图前禁用 Sequence 上骨骼网格体（含 Spawnable）的编辑器显示"))
					]
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.f)
				[
					SNullWidget::NullWidget
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("Execute", "执行"))
					.IsEnabled(this, &SBatchScreenShotPanel::CanExecute)
					.OnClicked(this, &SBatchScreenShotPanel::OnExecuteClicked)
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SSeparator)
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			.Padding(0.f, 8.f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
				.Padding(6.f)
				[
					SNew(SScrollBox)
					+ SScrollBox::Slot()
					[
						SAssignNew(SequenceListBox, SVerticalBox)
					]
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f, 0.f, 0.f)
			[
				SNew(SVerticalBox)
				.Visibility(this, &SBatchScreenShotPanel::GetProgressVisibility)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.f, 0.f, 0.f, 4.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(1.f)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("ProgressLabel", "执行进度"))
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(this, &SBatchScreenShotPanel::GetProgressText)
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SBox)
					.HeightOverride(12.f)
					[
						SNew(SProgressBar)
						.Percent(this, &SBatchScreenShotPanel::GetProgressPercent)
					]
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f, 0.f, 0.f)
			[
				SAssignNew(StatusText, STextBlock)
				.Text(this, &SBatchScreenShotPanel::GetStatusText)
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
		]
	];

	RefreshSequenceList();
}

void SBatchScreenShotPanel::RefreshSequenceList()
{
	SequenceItems.Reset();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FARFilter Filter;
	Filter.bRecursivePaths = true;
	Filter.bRecursiveClasses = true;
	Filter.ClassPaths.Add(ULevelSequence::StaticClass()->GetClassPathName());

	if(FolderPaths.Num() == 0)
	{
		Filter.PackagePaths.Add(TEXT("/Game"));
	}
	else
	{
		for(const FString& FolderPath : FolderPaths)
		{
			Filter.PackagePaths.Add(FName(*FolderPath));
		}
	}

	TArray<FAssetData> Assets;
	AssetRegistryModule.Get().GetAssets(Filter, Assets);
	Assets.Sort([](const FAssetData& A, const FAssetData& B)
	{
		return A.AssetName.LexicalLess(B.AssetName);
	});

	for(const FAssetData& Asset : Assets)
	{
		FBatchScreenShotSequenceItem& Item = SequenceItems.AddDefaulted_GetRef();
		Item.AssetData = Asset;
		Item.bSelected = true;
	}

	StatusMessage = SequenceItems.Num() > 0
		? FString::Printf(TEXT("找到 %d 个 Level Sequence"), SequenceItems.Num())
		: TEXT("该目录下没有 Level Sequence");

	RebuildSequenceListWidget();
}

void SBatchScreenShotPanel::RebuildSequenceListWidget()
{
	if(!SequenceListBox.IsValid())
	{
		return;
	}

	SequenceListBox->ClearChildren();

	if(SequenceItems.Num() == 0)
	{
		SequenceListBox->AddSlot()
		.AutoHeight()
		.Padding(4.f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("NoSequences", "该目录下没有 Level Sequence。"))
		];
		return;
	}

	for(int32 Index = 0; Index < SequenceItems.Num(); ++Index)
	{
		SequenceListBox->AddSlot()
		.AutoHeight()
		.Padding(2.f, 1.f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.f)
			.VAlign(VAlign_Center)
			[
				SNew(SCheckBox)
				.IsEnabled_Lambda([this]() { return !bIsRunning; })
				.IsChecked_Lambda([this, Index]()
				{
					return SequenceItems.IsValidIndex(Index) && SequenceItems[Index].bSelected
						? ECheckBoxState::Checked
						: ECheckBoxState::Unchecked;
				})
				.OnCheckStateChanged_Lambda([this, Index](ECheckBoxState NewState)
				{
					if(SequenceItems.IsValidIndex(Index))
					{
						SequenceItems[Index].bSelected = (NewState == ECheckBoxState::Checked);
					}
				})
				[
					SNew(STextBlock)
					.Text(FText::FromName(SequenceItems[Index].AssetData.AssetName))
					.ToolTipText(FText::FromName(SequenceItems[Index].AssetData.PackageName))
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(8.f, 0.f, 0.f, 0.f)
			[
				SNew(SButton)
				.Text(LOCTEXT("OpenSequence", "打开"))
				.ToolTipText(LOCTEXT("OpenSequenceTip", "在内容浏览器中定位并打开此 Level Sequence"))
				.IsEnabled_Lambda([this]() { return !bIsRunning; })
				.OnClicked(this, &SBatchScreenShotPanel::OnOpenSequenceClicked, Index)
			]
		];
	}
}

FReply SBatchScreenShotPanel::OnOpenSequenceClicked(int32 Index)
{
	if(!SequenceItems.IsValidIndex(Index))
	{
		return FReply::Handled();
	}

	const FAssetData& AssetData = SequenceItems[Index].AssetData;
	if(!AssetData.IsValid())
	{
		StatusMessage = TEXT("无效的 Level Sequence。");
		return FReply::Handled();
	}

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	ContentBrowserModule.Get().SyncBrowserToAssets(TArray<FAssetData>{ AssetData }, true, true);

	ULevelSequence* LevelSequence = Cast<ULevelSequence>(AssetData.GetAsset());
	if(!LevelSequence)
	{
		StatusMessage = FString::Printf(TEXT("无法加载：%s"), *AssetData.AssetName.ToString());
		return FReply::Handled();
	}

	if(ULevelSequenceEditorBlueprintLibrary::OpenLevelSequence(LevelSequence))
	{
		StatusMessage = FString::Printf(TEXT("已打开：%s"), *AssetData.AssetName.ToString());
	}
	else if(GEditor)
	{
		if(UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
		{
			AssetEditorSubsystem->OpenEditorForAsset(LevelSequence);
			StatusMessage = FString::Printf(TEXT("已打开：%s"), *AssetData.AssetName.ToString());
		}
	}

	return FReply::Handled();
}

void SBatchScreenShotPanel::SetAllSelected(bool bSelected)
{
	for(FBatchScreenShotSequenceItem& Item : SequenceItems)
	{
		Item.bSelected = bSelected;
	}
}

FReply SBatchScreenShotPanel::OnSelectAllClicked()
{
	SetAllSelected(true);
	return FReply::Handled();
}

FReply SBatchScreenShotPanel::OnDeselectAllClicked()
{
	SetAllSelected(false);
	return FReply::Handled();
}

bool SBatchScreenShotPanel::CanExecute() const
{
	if(bIsRunning)
	{
		return false;
	}

	for(const FBatchScreenShotSequenceItem& Item : SequenceItems)
	{
		if(Item.bSelected)
		{
			return true;
		}
	}
	return false;
}

FReply SBatchScreenShotPanel::OnExecuteClicked()
{
	if(bIsRunning)
	{
		return FReply::Handled();
	}

	TArray<FAssetData> Selected;
	Selected.Reserve(SequenceItems.Num());
	for(const FBatchScreenShotSequenceItem& Item : SequenceItems)
	{
		if(Item.bSelected)
		{
			Selected.Add(Item.AssetData);
		}
	}

	if(Selected.Num() == 0)
	{
		StatusMessage = TEXT("请至少勾选一个 Level Sequence。");
		return FReply::Handled();
	}

	bIsRunning = true;
	ProgressCurrent = 0;
	ProgressTotal = Selected.Num();
	StatusMessage = FString::Printf(TEXT("准备执行 %d 个 Sequence..."), Selected.Num());

	GBatchScreenShotRunner = MakeShared<FBatchScreenShotRunner>();
	TWeakPtr<SBatchScreenShotPanel> WeakPanel = SharedThis(this);
	GBatchScreenShotRunner->Start(
		Selected,
		bHideSkeletalMeshes,
		FOnBatchScreenShotProgress::CreateLambda([WeakPanel](const FString& Status, int32 Current, int32 Total)
		{
			if(TSharedPtr<SBatchScreenShotPanel> Panel = WeakPanel.Pin())
			{
				Panel->StatusMessage = Status;
				Panel->ProgressCurrent = Current;
				Panel->ProgressTotal = Total;
			}
		}),
		FOnBatchScreenShotFinished::CreateLambda([WeakPanel]()
		{
			if(TSharedPtr<SBatchScreenShotPanel> Panel = WeakPanel.Pin())
			{
				Panel->bIsRunning = false;
				if(Panel->ProgressTotal > 0)
				{
					Panel->ProgressCurrent = Panel->ProgressTotal;
				}
			}
			GBatchScreenShotRunner.Reset();
		}));

	return FReply::Handled();
}

FText SBatchScreenShotPanel::GetFolderPathText() const
{
	if(FolderPaths.Num() == 0)
	{
		return LOCTEXT("FolderAll", "目录：/Game");
	}
	return FText::FromString(FString::Printf(TEXT("目录：%s"), *FString::Join(FolderPaths, TEXT(", "))));
}

FText SBatchScreenShotPanel::GetStatusText() const
{
	return FText::FromString(StatusMessage);
}

FText SBatchScreenShotPanel::GetProgressText() const
{
	if(ProgressTotal <= 0)
	{
		return FText::GetEmpty();
	}
	return FText::FromString(FString::Printf(TEXT("%d / %d"), ProgressCurrent, ProgressTotal));
}

TOptional<float> SBatchScreenShotPanel::GetProgressPercent() const
{
	if(ProgressTotal <= 0)
	{
		return 0.f;
	}
	return static_cast<float>(ProgressCurrent) / static_cast<float>(ProgressTotal);
}

EVisibility SBatchScreenShotPanel::GetProgressVisibility() const
{
	return (bIsRunning || ProgressTotal > 0) ? EVisibility::Visible : EVisibility::Collapsed;
}

#undef LOCTEXT_NAMESPACE
