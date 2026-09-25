// Copyright UMIUSHI Inc. All Rights Reserved.

#include "SHealthCheckerPanel.h"
#include "HealthCheckerEditorSubsystem.h"
#include "HealthCheckerSettings.h"
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

#define LOCTEXT_NAMESPACE "HealthChecker"

namespace
{
	static TWeakPtr<SWindow> GHealthCheckerWindow;
	static TWeakPtr<SHealthCheckerPanel> GHealthCheckerPanel;

	TSharedRef<SWidget> MakeCell(const FString& Text, bool bHeader)
	{
		return SNew(SBox)
			.Padding(FMargin(6.f, 4.f))
			[
				SNew(STextBlock)
				.Text(FText::FromString(Text))
				.Font(bHeader ? FAppStyle::GetFontStyle("BoldFont") : FAppStyle::GetFontStyle("NormalFont"))
				.AutoWrapText(!bHeader)
			];
	}
}

void SHealthCheckerPanel::Open(const TArray<FString>& InFolderPaths)
{
	if(TSharedPtr<SWindow> ExistingWindow = GHealthCheckerWindow.Pin())
	{
		if(TSharedPtr<SHealthCheckerPanel> ExistingPanel = GHealthCheckerPanel.Pin())
		{
			ExistingPanel->SetFolderPaths(InFolderPaths);
		}
		ExistingWindow->BringToFront(true);
		return;
	}

	TSharedRef<SHealthCheckerPanel> Panel = SNew(SHealthCheckerPanel).FolderPaths(InFolderPaths);
	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(LOCTEXT("WindowTitle", "资产检测"))
		.ClientSize(FVector2D(1180.f, 780.f))
		.SupportsMaximize(true)
		.SupportsMinimize(true)
		[
			Panel
		];

	GHealthCheckerWindow = Window;
	GHealthCheckerPanel = Panel;
	FSlateApplication::Get().AddWindow(Window);
}

void SHealthCheckerPanel::SetFolderPaths(const TArray<FString>& InFolderPaths)
{
	FolderPaths = InFolderPaths;
	if(FolderPathText.IsValid())
	{
		FolderPathText->SetText(GetFolderPathText());
	}
}

void SHealthCheckerPanel::Construct(const FArguments& InArgs)
{
	FolderPaths = InArgs._FolderPaths;
	ReportView = HealthCheckerReport::GetLast();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsArgs;
	DetailsArgs.bAllowSearch = true;
	DetailsArgs.bHideSelectionTip = true;
	DetailsArgs.bShowOptions = false;
	DetailsArgs.bShowPropertyMatrixButton = false;
	DetailsArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	SettingsView = PropertyModule.CreateDetailView(DetailsArgs);
	SettingsView->SetObject(GetMutableDefault<UHealthCheckerSettings>());
	SettingsView->OnFinishedChangingProperties().AddLambda([](const FPropertyChangedEvent&)
	{
		GetMutableDefault<UHealthCheckerSettings>()->SaveConfig();
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
			.Padding(8.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 8.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("CheckButton", "检测"))
					.OnClicked(this, &SHealthCheckerPanel::OnCheckClicked)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 12.f, 0.f)
				[
					SNew(SButton)
					.Text(this, &SHealthCheckerPanel::GetSettingsButtonText)
					.OnClicked(this, &SHealthCheckerPanel::OnSettingsClicked)
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.f)
				.VAlign(VAlign_Center)
				[
					SAssignNew(FolderPathText, STextBlock)
					.Text(this, &SHealthCheckerPanel::GetFolderPathText)
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
				.MaxDesiredHeight(360.f)
				.Padding(FMargin(8.f, 0.f, 8.f, 8.f))
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
					.Padding(4.f)
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
			.Padding(8.f)
			[
				SAssignNew(ResultsBox, SScrollBox)
			]
		]
	];

	RebuildResults();
}

FReply SHealthCheckerPanel::OnCheckClicked()
{
	UHealthCheckerEditorSubsystem::RunHealthChecker(true);
	ReportView = HealthCheckerReport::GetLast();
	RebuildResults();
	return FReply::Handled();
}

FReply SHealthCheckerPanel::OnSettingsClicked()
{
	bShowSettings = !bShowSettings;
	if(SettingsContainer.IsValid())
	{
		SettingsContainer->SetVisibility(bShowSettings ? EVisibility::Visible : EVisibility::Collapsed);
	}
	return FReply::Handled();
}

FText SHealthCheckerPanel::GetSettingsButtonText() const
{
	return bShowSettings ? LOCTEXT("HideSettings", "收起设置") : LOCTEXT("ShowSettings", "设置");
}

FText SHealthCheckerPanel::GetFolderPathText() const
{
	if(FolderPaths.Num() == 0)
	{
		return LOCTEXT("NoFolder", "文件夹: （未选择）");
	}
	return FText::FromString(FString::Printf(TEXT("文件夹: %s"), *FString::Join(FolderPaths, TEXT(", "))));
}

FLinearColor SHealthCheckerPanel::GetScoreColor(const FString& Score) const
{
	if(Score == TEXT("A")) return FLinearColor(0.18f, 0.80f, 0.44f);
	if(Score == TEXT("B")) return FLinearColor(0.20f, 0.60f, 0.86f);
	if(Score == TEXT("C")) return FLinearColor(0.95f, 0.77f, 0.06f);
	if(Score == TEXT("D")) return FLinearColor(0.90f, 0.49f, 0.13f);
	return FLinearColor(0.91f, 0.30f, 0.24f);
}

TSharedRef<SWidget> SHealthCheckerPanel::BuildTableRow(const FHealthCheckerTableRow& Row, bool bHeader) const
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

	return SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush(bHeader ? "DetailsView.CategoryTop" : "WhiteBrush"))
		.BorderBackgroundColor(bHeader ? FLinearColor(0.08f, 0.08f, 0.08f, 1.f) : FLinearColor(0.f, 0.f, 0.f, 0.15f))
		.Padding(0.f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(0.34f)[ MakeCell(bHeader ? TEXT("名称") : Row.Label, bHeader) ]
			+ SHorizontalBox::Slot().FillWidth(0.14f)[ MakeCell(bHeader ? TEXT("数值") : FString::FromInt(Row.Value), bHeader) ]
			+ SHorizontalBox::Slot().FillWidth(0.14f)[ MakeCell(bHeader ? TEXT("单位") : Row.Unit, bHeader) ]
			+ SHorizontalBox::Slot().FillWidth(0.18f)[ MakeCell(TotalText, bHeader) ]
			+ SHorizontalBox::Slot().FillWidth(0.20f)[ MakeCell(RatioText, bHeader) ]
		];
}

TSharedRef<SWidget> SHealthCheckerPanel::BuildSection(const FHealthCheckerTableSection& Section) const
{
	const int32 RowCount = FMath::Min(MaxDisplayRows, Section.Rows.Num());
	TSharedRef<SVerticalBox> Table = SNew(SVerticalBox);
	FHealthCheckerTableRow HeaderRow;
	Table->AddSlot().AutoHeight()[ BuildTableRow(HeaderRow, true) ];
	for(int32 Index = 0; Index < RowCount; ++Index)
	{
		Table->AddSlot().AutoHeight()[ BuildTableRow(Section.Rows[Index], false) ];
	}

	return SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
		.Padding(10.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 0.f, 0.f, 6.f)
			[
				SNew(SHorizontalBox)
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
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
					.BorderBackgroundColor(GetScoreColor(Section.Score))
					.Padding(FMargin(10.f, 2.f))
					[
						SNew(STextBlock)
						.Text(FText::FromString(Section.Score))
						.ColorAndOpacity(FLinearColor::White)
						.Font(FAppStyle::GetFontStyle("BoldFont"))
					]
				]
			]
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
				Table
			]
		];
}

void SHealthCheckerPanel::RebuildResults()
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
	.Padding(0.f, 0.f, 0.f, 8.f)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
		.Padding(12.f)
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
				.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
				.BorderBackgroundColor(GetScoreColor(ReportView.OverallScore))
				.Padding(FMargin(16.f, 8.f))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("OverallScore", "综合评分"))
						.ColorAndOpacity(FLinearColor::White)
					]
					+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
					[
						SNew(STextBlock)
						.Text(FText::FromString(ReportView.OverallScore))
						.ColorAndOpacity(FLinearColor::White)
						.Font(FCoreStyle::GetDefaultFontStyle("Bold", 28))
					]
				]
			]
		]
	];

	if(!ReportView.OverallDescription.IsEmpty())
	{
		ResultsBox->AddSlot()
		.Padding(0.f, 0.f, 0.f, 8.f)
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

	for(const FHealthCheckerTableSection& Section : ReportView.Sections)
	{
		ResultsBox->AddSlot()
		.Padding(0.f, 0.f, 0.f, 10.f)
		[
			BuildSection(Section)
		];
	}
}

#undef LOCTEXT_NAMESPACE
