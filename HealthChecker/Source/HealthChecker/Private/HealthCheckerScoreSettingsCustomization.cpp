// Copyright UMIUSHI Inc. All Rights Reserved.

#include "HealthCheckerScoreSettingsCustomization.h"
#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "Widgets/SBoxPanel.h"

TSharedRef<IPropertyTypeCustomization> FHealthCheckerScoreSettingsCustomization::MakeInstance()
{
	return MakeShareable(new FHealthCheckerScoreSettingsCustomization);
}

void FHealthCheckerScoreSettingsCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& Utils)
{
	TSharedPtr<IPropertyHandle> HandleA = PropertyHandle->GetChildHandle("A");
	TSharedPtr<IPropertyHandle> HandleB = PropertyHandle->GetChildHandle("B");
	TSharedPtr<IPropertyHandle> HandleC = PropertyHandle->GetChildHandle("C");
	TSharedPtr<IPropertyHandle> HandleD = PropertyHandle->GetChildHandle("D");
	TSharedPtr<IPropertyHandle> HandleScoreWeight = PropertyHandle->GetChildHandle("ScoreWeight");
	TSharedPtr<IPropertyHandle> HandleAllowHealthCheck = PropertyHandle->GetChildHandle("bAllowHealthCheck");

#define HC4UE_ADD_LABELED_WIDGET(Label, ToolTip, Handle) \
	+ SHorizontalBox::Slot().AutoWidth().Padding(4, 0) \
	[ \
		SNew(STextBlock).Text(FText::FromString(Label)) \
		.ToolTipText(FText::FromString(ToolTip)) \
	] \
	+ SHorizontalBox::Slot().AutoWidth().Padding(2, 0, 12, 0) \
	[ \
		SNew(SBox) \
		.IsEnabled_Lambda([HandleAllowHealthCheck]() { \
			bool bEnabled = true; \
			HandleAllowHealthCheck->GetValue(bEnabled); \
			return bEnabled; \
		}) \
		[ Handle->CreatePropertyValueWidget() ] \
	]

	HeaderRow
	.NameContent()
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(500.f)
	[
		SNew(SHorizontalBox)

		// A～D
		HC4UE_ADD_LABELED_WIDGET("A", "A Rank Threshold", HandleA)
		HC4UE_ADD_LABELED_WIDGET("B", "B Rank Threshold", HandleB)
		HC4UE_ADD_LABELED_WIDGET("C", "C Rank Threshold", HandleC)
		HC4UE_ADD_LABELED_WIDGET("D", "D Rank Threshold", HandleD)

		// 空白を入れて右側に押し出す
		+ SHorizontalBox::Slot().FillWidth(1.f)

		// 総合評価のウエイト
		+ SHorizontalBox::Slot().AutoWidth().Padding(4, 0, 2, 0)
		[
			SNew(STextBlock)
			.Text(FText::FromString("W"))
			.ToolTipText(FText::FromString("Score Weight"))
		]
		+ SHorizontalBox::Slot().AutoWidth().Padding(2, 0, 2, 0)
		[
			SNew(SBox)
			.IsEnabled_Lambda([HandleAllowHealthCheck]() {
				bool bEnabled = true;
				HandleAllowHealthCheck->GetValue(bEnabled);
				return bEnabled;
			})
			[
				HandleScoreWeight->CreatePropertyValueWidget()
			]
		]

		// チェックボックス
		+ SHorizontalBox::Slot().AutoWidth().Padding(2, 0, 0, 0)
		[
			SNew(SCheckBox)
			.ToolTipText(FText::FromString(TEXT("Enable or Disable Health Check")))
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
	];

#undef HC4UE_ADD_LABELED_WIDGET
}

void FHealthCheckerScoreSettingsCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& Utils)
{
	// 縦並びの子要素表示を抑制
}
