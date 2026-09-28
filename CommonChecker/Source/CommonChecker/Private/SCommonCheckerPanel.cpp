// Copyright UMIUSHI Inc. All Rights Reserved.

#include "SCommonCheckerPanel.h"
#include "CommonCheckerEditorSubsystem.h"
#include "CommonCheckerSettings.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/AppStyle.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SWindow.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SSplitter.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"

#define LOCTEXT_NAMESPACE "CommonChecker"

namespace
{
	static TWeakPtr<SWindow> GCommonCheckerWindow;
	static TWeakPtr<SCommonCheckerPanel> GCommonCheckerPanel;

	TSharedRef<SWidget> MakeCell(const FString& Text, bool bHeader, const FLinearColor& TextColor = FLinearColor::White)
	{
		return SNew(SBox)
			.Padding(FMargin(6.f, 4.f))
			[
				SNew(STextBlock)
				.Text(FText::FromString(Text))
				.Font(bHeader ? FAppStyle::GetFontStyle("BoldFont") : FAppStyle::GetFontStyle("NormalFont"))
				.AutoWrapText(!bHeader)
				.ColorAndOpacity(TextColor)
			];
	}
}

void SCommonCheckerPanel::Open(const TArray<FString>& InFolderPaths)
{
	if(TSharedPtr<SWindow> ExistingWindow = GCommonCheckerWindow.Pin())
	{
		if(TSharedPtr<SCommonCheckerPanel> ExistingPanel = GCommonCheckerPanel.Pin())
		{
			ExistingPanel->SetFolderPaths(InFolderPaths);
		}
		ExistingWindow->BringToFront(true);
		return;
	}

	TSharedRef<SCommonCheckerPanel> Panel = SNew(SCommonCheckerPanel).FolderPaths(InFolderPaths);
	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(LOCTEXT("WindowTitle", "资产检测"))
		.ClientSize(FVector2D(1280.f, 820.f))
		.SupportsMaximize(true)
		.SupportsMinimize(true)
		[
			Panel
		];

	GCommonCheckerWindow = Window;
	GCommonCheckerPanel = Panel;
	FSlateApplication::Get().AddWindow(Window);
}

void SCommonCheckerPanel::SetFolderPaths(const TArray<FString>& InFolderPaths)
{
	FolderPaths = InFolderPaths;
	if(FolderPathText.IsValid())
	{
		FolderPathText->SetText(GetFolderPathText());
	}
}

void SCommonCheckerPanel::Construct(const FArguments& InArgs)
{
	FolderPaths = InArgs._FolderPaths;
	ReportView = CommonCheckerReport::GetLast();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsArgs;
	DetailsArgs.bAllowSearch = true;
	DetailsArgs.bHideSelectionTip = true;
	DetailsArgs.bShowOptions = false;
	DetailsArgs.bShowPropertyMatrixButton = false;
	DetailsArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	SettingsView = PropertyModule.CreateDetailView(DetailsArgs);
	SettingsView->SetObject(GetMutableDefault<UCommonCheckerSettings>());
	SettingsView->OnFinishedChangingProperties().AddLambda([](const FPropertyChangedEvent&)
	{
		GetMutableDefault<UCommonCheckerSettings>()->SaveConfig();
	});

	ChildSlot
	[
		SNew(SScrollBox)
		.Orientation(Orient_Vertical)
		.ScrollBarAlwaysVisible(true)
		+ SScrollBox::Slot()
		[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(0.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(12.f, 10.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 10.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("CheckButton", "检测"))
					.OnClicked(this, &SCommonCheckerPanel::OnCheckClicked)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 4.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("ScopeLevel", "当前关卡"))
					.ToolTipText(LOCTEXT("ScopeLevelTip", "只检查当前打开关卡里的 Actor、组件和蓝图实例"))
					.ButtonColorAndOpacity_Lambda([this]()
					{
						return FSlateColor(CheckScope == ECommonCheckerScope::CurrentLevel ? FLinearColor(0.10f, 0.35f, 0.62f) : FLinearColor(0.18f, 0.18f, 0.18f));
					})
					.OnClicked_Lambda([this]()
					{
						CheckScope = ECommonCheckerScope::CurrentLevel;
						if(FolderPathText.IsValid())
						{
							FolderPathText->SetText(GetFolderPathText());
						}
						return FReply::Handled();
					})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 16.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("ScopeFolder", "内容目录"))
					.ToolTipText(LOCTEXT("ScopeFolderTip", "只检查内容浏览器选中目录里的网格、材质和贴图"))
					.ButtonColorAndOpacity_Lambda([this]()
					{
						return FSlateColor(CheckScope == ECommonCheckerScope::ContentFolder ? FLinearColor(0.10f, 0.35f, 0.62f) : FLinearColor(0.18f, 0.18f, 0.18f));
					})
					.OnClicked_Lambda([this]()
					{
						CheckScope = ECommonCheckerScope::ContentFolder;
						if(FolderPathText.IsValid())
						{
							FolderPathText->SetText(GetFolderPathText());
						}
						return FReply::Handled();
					})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 16.f, 0.f)
				[
					SNew(SButton)
					.Text(this, &SCommonCheckerPanel::GetSettingsButtonText)
					.OnClicked(this, &SCommonCheckerPanel::OnSettingsClicked)
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.f)
				.VAlign(VAlign_Center)
				[
					SAssignNew(FolderPathText, STextBlock)
					.Text(this, &SCommonCheckerPanel::GetFolderPathText)
					.Font(FAppStyle::GetFontStyle("NormalFont"))
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(SettingsContainer, SBox)
				.Visibility(EVisibility::Collapsed)
				.MaxDesiredHeight(420.f)
				.Padding(FMargin(12.f, 0.f, 12.f, 10.f))
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
					.Padding(6.f)
					[
						SNew(SScrollBox)
						+ SScrollBox::Slot()
						[
							SettingsView.ToSharedRef()
						]
					]
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SSeparator)
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			.Padding(12.f, 10.f)
			[
				SAssignNew(ResultsBox, SVerticalBox)
			]
		]
		]
	];

	RebuildResults();
}

FReply SCommonCheckerPanel::OnCheckClicked()
{
	if(CheckScope == ECommonCheckerScope::ContentFolder)
	{
		TArray<FString> Paths = FolderPaths;
		if(Paths.Num() == 0)
		{
			Paths.Add(TEXT("/Game"));
		}
		UCommonCheckerEditorSubsystem::RunCommonCheckerForFolders(Paths, true, ECommonCheckerScope::ContentFolder);
	}
	else
	{
		UCommonCheckerEditorSubsystem::RunCommonCheckerForFolders(TArray<FString>(), true, ECommonCheckerScope::CurrentLevel);
	}
	ReportView = CommonCheckerReport::GetLast();
	SelectedSectionIndex = 0;
	SelectedRowIndex = INDEX_NONE;
	RebuildResults();
	return FReply::Handled();
}

FReply SCommonCheckerPanel::OnSettingsClicked()
{
	bShowSettings = !bShowSettings;
	if(SettingsContainer.IsValid())
	{
		SettingsContainer->SetVisibility(bShowSettings ? EVisibility::Visible : EVisibility::Collapsed);
	}
	return FReply::Handled();
}

FText SCommonCheckerPanel::GetSettingsButtonText() const
{
	return bShowSettings ? LOCTEXT("HideSettings", "收起设置") : LOCTEXT("ShowSettings", "设置");
}

FText SCommonCheckerPanel::GetFolderPathText() const
{
	if(CheckScope == ECommonCheckerScope::ContentFolder)
	{
		if(FolderPaths.Num() == 0)
		{
			return LOCTEXT("FolderScopeAll", "检查范围：内容目录 /Game");
		}
		return FText::FromString(FString::Printf(TEXT("检查范围：内容目录 %s"), *FString::Join(FolderPaths, TEXT(", "))));
	}
	return LOCTEXT("LevelScope", "检查范围：当前打开的关卡");
}

FText SCommonCheckerPanel::GetScoreLabel(const FString& Score) const
{
	if(Score == TEXT("A"))
	{
		return LOCTEXT("ImpactNone", "通过");
	}
	if(Score == TEXT("B"))
	{
		return LOCTEXT("ImpactMinor", "警告");
	}
	return LOCTEXT("ImpactMajor", "提醒");
}

FLinearColor SCommonCheckerPanel::GetScoreColor(const FString& Score) const
{
	if(Score == TEXT("A"))
	{
		return FLinearColor(0.18f, 0.80f, 0.44f);
	}
	if(Score == TEXT("B"))
	{
		return FLinearColor(0.95f, 0.77f, 0.06f);
	}
	return FLinearColor(0.91f, 0.30f, 0.24f);
}

const FSlateBrush* SCommonCheckerPanel::GetScoreIcon(const FString& Score) const
{
	if(Score == TEXT("A"))
	{
		return FAppStyle::GetBrush("Icons.SuccessWithColor");
	}
	if(Score == TEXT("B"))
	{
		return FAppStyle::GetBrush("Icons.WarningWithColor");
	}
	return FAppStyle::GetBrush("Icons.ErrorWithColor");
}

bool SCommonCheckerPanel::IsSectionCollapsed(const FString& Title) const
{
	const bool* Found = CollapsedSections.Find(Title);
	return Found && *Found;
}

bool SCommonCheckerPanel::IsSectionEnlarged(const FString& Title) const
{
	const bool* Found = EnlargedSections.Find(Title);
	return Found && *Found;
}

FReply SCommonCheckerPanel::ToggleSectionCollapsed(const FString& Title)
{
	CollapsedSections.FindOrAdd(Title) = !IsSectionCollapsed(Title);
	RebuildResults();
	return FReply::Handled();
}

FReply SCommonCheckerPanel::ToggleSectionEnlarged(const FString& Title)
{
	const bool bEnlarged = !IsSectionEnlarged(Title);
	EnlargedSections.FindOrAdd(Title) = bEnlarged;
	if(bEnlarged)
	{
		CollapsedSections.FindOrAdd(Title) = false;
	}
	RebuildResults();
	return FReply::Handled();
}

void SCommonCheckerPanel::SyncContentBrowserToAsset(const FString& AssetPath) const
{
	if(AssetPath.IsEmpty())
	{
		return;
	}

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath(FSoftObjectPath(AssetPath));
	if(!AssetData.IsValid())
	{
		FString PackagePath = AssetPath;
		int32 DotIndex = INDEX_NONE;
		if(PackagePath.FindChar(TEXT('.'), DotIndex))
		{
			PackagePath.LeftInline(DotIndex);
			AssetData = AssetRegistryModule.Get().GetAssetByObjectPath(FSoftObjectPath(PackagePath));
		}
	}

	if(AssetData.IsValid())
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		ContentBrowserModule.Get().SyncBrowserToAssets(TArray<FAssetData>{ AssetData }, true, true);
	}
}

FReply SCommonCheckerPanel::OnDetailRowClicked(int32 RowIndex, FString AssetPath)
{
	SelectedRowIndex = RowIndex;
	if(!AssetPath.IsEmpty())
	{
		SyncContentBrowserToAsset(AssetPath);
	}
	RebuildResults();
	return FReply::Handled();
}

TSharedRef<SWidget> SCommonCheckerPanel::BuildTableRow(const FCommonCheckerTableRow& Row, bool bHeader, bool bSelected, int32 RowIndex)
{
	FString RatioText = TEXT("-");
	if(bHeader)
	{
		RatioText = TEXT("占比");
	}
	else if(Row.bHasRatio)
	{
		const float Rounded = FMath::FloorToFloat(Row.Ratio);
		RatioText = (Rounded == Row.Ratio)
			? FString::Printf(TEXT("%d%%"), (int32)Row.Ratio)
			: FString::Printf(TEXT("%.1f%%"), Row.Ratio);
	}

	const FString TotalText = bHeader ? FString(TEXT("总计")) : (Row.TotalValue == 0 ? FString(TEXT("-")) : FString::FromInt(Row.TotalValue));
	const bool bWarning = !bHeader && Row.Score == TEXT("B");
	const bool bAlert = !bHeader && !Row.Score.IsEmpty() && Row.Score != TEXT("A") && Row.Score != TEXT("B");
	FLinearColor TextColor = bHeader ? FLinearColor::White : FLinearColor(0.9f, 0.9f, 0.9f, 1.f);
	FLinearColor RowColor(0.f, 0.f, 0.f, 0.15f);
	FString NameText = bHeader ? FString(TEXT("名称")) : Row.Label;
	if(bWarning)
	{
		TextColor = FLinearColor(1.f, 0.86f, 0.35f);
		RowColor = FLinearColor(0.45f, 0.32f, 0.05f, 0.95f);
		NameText = FString::Printf(TEXT("警告  %s"), *Row.Label);
	}
	else if(bAlert)
	{
		TextColor = FLinearColor(1.f, 0.55f, 0.48f);
		RowColor = FLinearColor(0.55f, 0.12f, 0.10f, 0.95f);
		NameText = FString::Printf(TEXT("提醒  %s"), *Row.Label);
	}

	if(bSelected)
	{
		RowColor = FLinearColor(0.05f, 0.28f, 0.48f, 0.95f);
		TextColor = FLinearColor::White;
	}

	TSharedRef<SWidget> RowContent = SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush(bHeader ? "DetailsView.CategoryTop" : "WhiteBrush"))
		.BorderBackgroundColor(bHeader ? FLinearColor(0.08f, 0.08f, 0.08f, 1.f) : RowColor)
		.Padding(0.f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(0.34f)[ MakeCell(NameText, bHeader || bWarning || bAlert, TextColor) ]
			+ SHorizontalBox::Slot().FillWidth(0.14f)[ MakeCell(bHeader ? TEXT("数值") : FString::FromInt(Row.Value), bHeader, TextColor) ]
			+ SHorizontalBox::Slot().FillWidth(0.14f)[ MakeCell(bHeader ? TEXT("单位") : Row.Unit, bHeader, TextColor) ]
			+ SHorizontalBox::Slot().FillWidth(0.18f)[ MakeCell(TotalText, bHeader, TextColor) ]
			+ SHorizontalBox::Slot().FillWidth(0.20f)[ MakeCell(RatioText, bHeader, TextColor) ]
		];

	if(bHeader)
	{
		return RowContent;
	}

	return SNew(SButton)
		.ButtonStyle(FAppStyle::Get(), "NoBorder")
		.ForegroundColor(FSlateColor::UseForeground())
		.OnClicked_Lambda([this, RowIndex, AssetPath = Row.AssetPath]()
		{
			return OnDetailRowClicked(RowIndex, AssetPath);
		})
		.ToolTipText(Row.AssetPath.IsEmpty()
			? LOCTEXT("SelectRowTip", "选中这一项")
			: FText::FromString(FString::Printf(TEXT("选中并跳转到资产: %s"), *Row.AssetPath)))
		[
			RowContent
		];
}

TSharedRef<SWidget> SCommonCheckerPanel::BuildSectionDetail(const FCommonCheckerTableSection& Section)
{
	TArray<FCommonCheckerTableRow> OrderedRows = Section.Rows;
	OrderedRows.StableSort([](const FCommonCheckerTableRow& A, const FCommonCheckerTableRow& B)
	{
		auto Rank = [](const FString& Score)
		{
			if(Score.IsEmpty() || Score == TEXT("A")) return 2;
			if(Score == TEXT("B")) return 1;
			return 0;
		};
		return Rank(A.Score) < Rank(B.Score);
	});

	TSharedRef<SVerticalBox> Table = SNew(SVerticalBox);
	FCommonCheckerTableRow HeaderRow;
	Table->AddSlot().AutoHeight()[ BuildTableRow(HeaderRow, true, false, INDEX_NONE) ];
	for(int32 RowIndex = 0; RowIndex < OrderedRows.Num(); ++RowIndex)
	{
		Table->AddSlot().AutoHeight()[ BuildTableRow(OrderedRows[RowIndex], false, RowIndex == SelectedRowIndex, RowIndex) ];
	}

	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.f, 0.f, 0.f, 8.f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.f, 0.f, 8.f, 0.f)
			[
				SNew(SImage)
				.Image(GetScoreIcon(Section.Score))
				.DesiredSizeOverride(FVector2D(18.f, 18.f))
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.f)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText::FromString(Section.Title))
					.Font(FAppStyle::GetFontStyle("BoldFont"))
				]
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText::FromString(Section.EnglishTitle))
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(GetScoreLabel(Section.Score))
				.ColorAndOpacity(GetScoreColor(Section.Score))
				.Font(FAppStyle::GetFontStyle("BoldFont"))
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.f, 0.f, 0.f, 8.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Section.Explanation))
			.AutoWrapText(true)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.f, 0.f, 0.f, 10.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Section.Description))
			.AutoWrapText(true)
			.ColorAndOpacity(FSlateColor::UseSubduedForeground())
		]
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				OrderedRows.Num() > 0
					? StaticCastSharedRef<SWidget>(Table)
					: StaticCastSharedRef<SWidget>(SNew(STextBlock).Text(LOCTEXT("NoRows", "这一类没有具体执行项。")))
			]
		];
}

TSharedRef<SWidget> SCommonCheckerPanel::BuildCategoryList()
{
	TSharedRef<SVerticalBox> List = SNew(SVerticalBox);
	for(int32 Index = 0; Index < ReportView.Sections.Num(); ++Index)
	{
		const FCommonCheckerTableSection& Section = ReportView.Sections[Index];
		const bool bSelected = Index == SelectedSectionIndex;
		List->AddSlot()
		.AutoHeight()
		.Padding(0.f, 0.f, 0.f, 2.f)
		[
			SNew(SButton)
			.ButtonStyle(FAppStyle::Get(), "SimpleButton")
			.OnClicked_Lambda([this, Index]()
			{
				return OnCategoryClicked(Index);
			})
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
				.BorderBackgroundColor(bSelected ? FLinearColor(0.16f, 0.16f, 0.16f, 1.f) : FLinearColor(0.f, 0.f, 0.f, 0.f))
				.Padding(FMargin(8.f, 6.f))
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(0.f, 0.f, 8.f, 0.f)
					[
						SNew(SImage)
						.Image(GetScoreIcon(Section.Score))
						.DesiredSizeOverride(FVector2D(14.f, 14.f))
					]
					+ SHorizontalBox::Slot()
					.FillWidth(1.f)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(FText::FromString(Section.Title))
						.ColorAndOpacity(bSelected ? FLinearColor::White : FLinearColor(0.82f, 0.82f, 0.82f))
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(8.f, 0.f, 0.f, 0.f)
					[
						SNew(STextBlock)
						.Text(GetScoreLabel(Section.Score))
						.ColorAndOpacity(GetScoreColor(Section.Score))
					]
				]
			]
		];
	}
	return List;
}

FReply SCommonCheckerPanel::OnCategoryClicked(int32 SectionIndex)
{
	SelectedSectionIndex = SectionIndex;
	SelectedRowIndex = INDEX_NONE;
	RebuildResults();
	return FReply::Handled();
}

void SCommonCheckerPanel::RebuildResults()
{
	if(!ResultsBox.IsValid())
	{
		return;
	}

	ResultsBox->ClearChildren();

	if(!ReportView.bValid)
	{
		ResultsBox->AddSlot()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("EmptyReport", "点击“检测”后，结果会以表格显示在这里。"))
		];
		return;
	}

	ResultsBox->AddSlot()
	.AutoHeight()
	.Padding(0.f, 0.f, 0.f, 10.f)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
		.Padding(14.f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText::FromString(FString::Printf(TEXT("项目: %s"), *ReportView.Project)))
				]
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText::FromString(FString::Printf(TEXT("地图: %s"), *ReportView.Map)))
				]
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText::FromString(FString::Printf(TEXT("引擎: %s"), *ReportView.Engine)))
				]
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText::FromString(FString::Printf(TEXT("生成: %s    版本: %s"), *ReportView.GeneratedBy, *ReportView.Version)))
				]
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText::FromString(FString::Printf(TEXT("更新时间: %s"), *ReportView.LastUpdate)))
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(16.f, 0.f, 0.f, 0.f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
				.Padding(FMargin(16.f, 10.f))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("OverallScore", "综合结果"))
					]
					+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0.f, 6.f, 0.f, 0.f)
					[
						SNew(SImage)
						.Image(GetScoreIcon(ReportView.OverallScore))
						.DesiredSizeOverride(FVector2D(28.f, 28.f))
					]
					+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0.f, 4.f, 0.f, 0.f)
					[
						SNew(STextBlock)
						.Text(GetScoreLabel(ReportView.OverallScore))
						.ColorAndOpacity(GetScoreColor(ReportView.OverallScore))
						.Font(FAppStyle::GetFontStyle("BoldFont"))
					]
				]
			]
		]
	];

	if(!ReportView.OverallDescription.IsEmpty())
	{
		ResultsBox->AddSlot()
		.AutoHeight()
		.Padding(0.f, 0.f, 0.f, 10.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(ReportView.OverallDescription))
			.AutoWrapText(true)
		];
	}

	if(ReportView.Sections.Num() == 0)
	{
		ResultsBox->AddSlot()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("NoSections", "检测完成，没有可显示的评分项。"))
		];
		return;
	}

	SelectedSectionIndex = FMath::Clamp(SelectedSectionIndex, 0, ReportView.Sections.Num() - 1);
	const FCommonCheckerTableSection& SelectedSection = ReportView.Sections[SelectedSectionIndex];

	ResultsBox->AddSlot()
	.FillHeight(1.f)
	[
		SNew(SSplitter)
		.Orientation(Orient_Horizontal)
		+ SSplitter::Slot()
		.Value(0.42f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
			.Padding(8.f)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					BuildCategoryList()
				]
			]
		]
		+ SSplitter::Slot()
		.Value(0.58f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
			.Padding(12.f)
			[
				BuildSectionDetail(SelectedSection)
			]
		]
	];
}

#undef LOCTEXT_NAMESPACE
