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
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(8.f, 0.f, 4.f, 0.f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("DisplayCount", "显示条数"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SSpinBox<int32>)
					.MinValue(1)
					.MaxValue(100)
					.Value_Lambda([this]() { return MaxDisplayRows; })
					.OnValueChanged_Lambda([this](int32 NewValue)
					{
						MaxDisplayRows = FMath::Max(1, NewValue);
						RebuildResults();
					})
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
				SAssignNew(ResultsBox, SScrollBox)
			]
		]
	];

	RebuildResults();
}

FReply SCommonCheckerPanel::OnCheckClicked()
{
	UCommonCheckerEditorSubsystem::RunCommonCheckerForFolders(FolderPaths, true);
	ReportView = CommonCheckerReport::GetLast();
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
	if(FolderPaths.Num() == 0)
	{
		return LOCTEXT("NoFolder", "检测范围：全部资产");
	}
	return FText::FromString(FString::Printf(TEXT("检测范围：%s"), *FString::Join(FolderPaths, TEXT(", "))));
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

FReply SCommonCheckerPanel::OnRowClicked(const FCommonCheckerTableRow& Row) const
{
	SyncContentBrowserToAsset(Row.AssetPath);
	return FReply::Handled();
}

TSharedRef<SWidget> SCommonCheckerPanel::BuildTableRow(const FCommonCheckerTableRow& Row, bool bHeader) const
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

	if(bHeader || Row.AssetPath.IsEmpty())
	{
		return RowContent;
	}

	return SNew(SButton)
		.ButtonStyle(FAppStyle::Get(), "NoBorder")
		.ForegroundColor(FSlateColor::UseForeground())
		.OnClicked_Lambda([this, Row]()
		{
			return OnRowClicked(Row);
		})
		.ToolTipText(FText::FromString(FString::Printf(TEXT("点击跳转到资产: %s"), *Row.AssetPath)))
		[
			RowContent
		];
}

TSharedRef<SWidget> SCommonCheckerPanel::BuildSection(const FCommonCheckerTableSection& Section)
{
	const bool bCollapsed = IsSectionCollapsed(Section.Title);
	const bool bEnlarged = IsSectionEnlarged(Section.Title);
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
	const int32 RowLimit = bEnlarged ? OrderedRows.Num() : FMath::Min(MaxDisplayRows, OrderedRows.Num());
	TSharedRef<SVerticalBox> Table = SNew(SVerticalBox);
	FCommonCheckerTableRow HeaderRow;
	Table->AddSlot().AutoHeight()[ BuildTableRow(HeaderRow, true) ];
	for(int32 Index = 0; Index < RowLimit; ++Index)
	{
		Table->AddSlot().AutoHeight()[ BuildTableRow(OrderedRows[Index], false) ];
	}

	TSharedRef<SWidget> TableWidget = Table;
	if(bEnlarged)
	{
		TableWidget = SNew(SBox)
			.MinDesiredHeight(280.f)
			.MaxDesiredHeight(560.f)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					Table
				]
			];
	}

	const FString SectionTitle = Section.Title;
	return SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
		.Padding(8.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
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
					SNew(STextBlock)
					.Text(FText::FromString(Section.Title))
					.Font(FAppStyle::GetFontStyle("BoldFont"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(8.f, 0.f, 8.f, 0.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(0.f, 0.f, 6.f, 0.f)
					[
						SNew(SImage)
						.Image(GetScoreIcon(Section.Score))
						.DesiredSizeOverride(FVector2D(14.f, 14.f))
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
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 4.f, 0.f)
				[
					SNew(SButton)
					.Text(bCollapsed ? LOCTEXT("ExpandSection", "展开") : LOCTEXT("CollapseSection", "折叠"))
					.ToolTipText(bCollapsed ? LOCTEXT("ExpandSectionTip", "展开这个检查区域") : LOCTEXT("CollapseSectionTip", "折叠这个检查区域"))
					.OnClicked_Lambda([this, SectionTitle]()
					{
						return ToggleSectionCollapsed(SectionTitle);
					})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(bEnlarged ? LOCTEXT("ShrinkSection", "缩小") : LOCTEXT("EnlargeSection", "放大"))
					.ToolTipText(bEnlarged ? LOCTEXT("ShrinkSectionTip", "缩小这个检查区域") : LOCTEXT("EnlargeSectionTip", "放大这个检查区域并显示全部行"))
					.OnClicked_Lambda([this, SectionTitle]()
					{
						return ToggleSectionEnlarged(SectionTitle);
					})
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f, 0.f, 0.f)
			[
				SNew(SBox)
				.Visibility(bCollapsed ? EVisibility::Collapsed : EVisibility::Visible)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.f, 0.f, 0.f, 8.f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(Section.Description))
						.AutoWrapText(true)
						.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						TableWidget
					]
				]
			]
		];
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

	for(const FCommonCheckerTableSection& Section : ReportView.Sections)
	{
		ResultsBox->AddSlot()
		.Padding(0.f, 0.f, 0.f, 10.f)
		[
			BuildSection(Section)
		];
	}
}

#undef LOCTEXT_NAMESPACE
