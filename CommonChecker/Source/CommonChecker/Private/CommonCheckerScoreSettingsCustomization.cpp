// Copyright UMIUSHI Inc. All Rights Reserved.

#include "CommonCheckerScoreSettingsCustomization.h"
#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Input/SCheckBox.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "CommonChecker"

TSharedRef<IPropertyTypeCustomization> FCommonCheckerScoreSettingsCustomization::MakeInstance()
{
	return MakeShareable(new FCommonCheckerScoreSettingsCustomization);
}

namespace
{
	TSharedRef<SWidget> MakeRankBadge(const FString& Rank, const FLinearColor& Color)
	{
		return SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
			.BorderBackgroundColor(Color)
			.Padding(FMargin(6.f, 2.f))
			[
				SNew(STextBlock)
				.Text(FText::FromString(Rank))
				.Font(FAppStyle::GetFontStyle("BoldFont"))
				.ColorAndOpacity(FLinearColor::White)
			];
	}

	TSharedRef<SWidget> MakeThresholdWidget(const TSharedPtr<IPropertyHandle>& Handle, const TSharedPtr<IPropertyHandle>& HandleAllowHealthCheck)
	{
		return SNew(SBox)
			.MinDesiredWidth(56.f)
			.MaxDesiredWidth(90.f)
			.IsEnabled_Lambda([HandleAllowHealthCheck]()
			{
				bool bEnabled = true;
				if(HandleAllowHealthCheck.IsValid())
				{
					HandleAllowHealthCheck->GetValue(bEnabled);
				}
				return bEnabled;
			})
			[
				Handle->CreatePropertyValueWidget()
			];
	}
}

void FCommonCheckerScoreSettingsCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& Utils)
{
	TSharedPtr<IPropertyHandle> HandleA = PropertyHandle->GetChildHandle("A");
	TSharedPtr<IPropertyHandle> HandleB = PropertyHandle->GetChildHandle("B");
	TSharedPtr<IPropertyHandle> HandleScoreWeight = PropertyHandle->GetChildHandle("ScoreWeight");
	TSharedPtr<IPropertyHandle> HandleAllowHealthCheck = PropertyHandle->GetChildHandle("bAllowHealthCheck");

	const FLinearColor ColorPass = FLinearColor(0.18f, 0.80f, 0.44f);
	const FLinearColor ColorWarn = FLinearColor(0.95f, 0.77f, 0.06f);
	const FLinearColor ColorFail = FLinearColor(0.91f, 0.30f, 0.24f);

	HeaderRow
	.NameContent()
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(560.f)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(0.f, 0.f, 4.f, 0.f)
		.VAlign(VAlign_Center)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 4.f, 0.f).VAlign(VAlign_Center)[ MakeRankBadge(TEXT("通过"), ColorPass) ]
			+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 4.f, 0.f).VAlign(VAlign_Center)[ MakeThresholdWidget(HandleA, HandleAllowHealthCheck) ]
			+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 4.f, 0.f).VAlign(VAlign_Center)[ MakeRankBadge(TEXT("警告"), ColorWarn) ]
			+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 4.f, 0.f).VAlign(VAlign_Center)[ MakeThresholdWidget(HandleB, HandleAllowHealthCheck) ]
			+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 8.f, 0.f).VAlign(VAlign_Center)[ MakeRankBadge(TEXT("提醒"), ColorFail) ]
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		[
			SNew(SSpacer)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(0.f, 0.f, 8.f, 0.f)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			.Padding(FMargin(8.f, 4.f))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 6.f, 0.f)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("ScoreWeightLabel", "权重"))
					.ToolTipText(LOCTEXT("ScoreWeightTooltip", "该项在综合评分中的权重"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(SBox)
					.MinDesiredWidth(50.f)
					.MaxDesiredWidth(70.f)
					.IsEnabled_Lambda([HandleAllowHealthCheck]()
					{
						bool bEnabled = true;
						if(HandleAllowHealthCheck.IsValid())
						{
							HandleAllowHealthCheck->GetValue(bEnabled);
						}
						return bEnabled;
					})
					[
						HandleScoreWeight->CreatePropertyValueWidget()
					]
				]
			]
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(0.f, 0.f, 4.f, 0.f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("EnableCheckLabel", "启用"))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SCheckBox)
				.ToolTipText(LOCTEXT("EnableCheckTooltip", "是否启用该项健康检查"))
				.OnCheckStateChanged_Lambda([HandleAllowHealthCheck](ECheckBoxState NewState)
				{
					HandleAllowHealthCheck->SetValue(NewState == ECheckBoxState::Checked);
				})
				.IsChecked_Lambda([HandleAllowHealthCheck]()
				{
					bool bChecked = false;
					HandleAllowHealthCheck->GetValue(bChecked);
					return bChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
				})
			]
		]
	];
}

void FCommonCheckerScoreSettingsCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& Utils)
{
	// 抑制默认的纵向子属性显示，所有控件已在 Header 中展示
}

#undef LOCTEXT_NAMESPACE
