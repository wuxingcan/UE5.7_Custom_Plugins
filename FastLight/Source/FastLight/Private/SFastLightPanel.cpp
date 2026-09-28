// Copyright Epic Games, Inc. All Rights Reserved.

#include "SFastLightPanel.h"

#include "FastLightShared.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/LightComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/RectLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Editor.h"
#include "ScopedTransaction.h"
#include "Styling/AppStyle.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Colors/SColorPicker.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "FastLight"

namespace
{
	TSharedRef<SWidget> MakeRow(const FText& Label, const TSharedRef<SWidget>& Value)
	{
		return SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.f, 0.f, 10.f, 0.f)
			[
				SNew(SBox)
				.WidthOverride(42.f)
				[
					SNew(STextBlock)
					.Text(Label)
					.Font(FAppStyle::GetFontStyle("SmallFont"))
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.f)
			.VAlign(VAlign_Center)
			[
				Value
			];
	}
}

void SFastLightPanel::Construct(const FArguments& InArgs)
{
	SetCanTick(true);

	const UEnum* UnitsEnum = StaticEnum<ELightUnits>();
	if(UnitsEnum)
	{
		for(int32 Index = 0; Index < UnitsEnum->NumEnums() - 1; ++Index)
		{
			if(UnitsEnum->HasMetaData(TEXT("Hidden"), Index))
			{
				continue;
			}
			UnitValues.Add(static_cast<ELightUnits>(UnitsEnum->GetValueByIndex(Index)));
			UnitLabels.Add(MakeShared<FString>(UnitsEnum->GetDisplayNameTextByIndex(Index).ToString()));
		}
	}

	ChildSlot
	[
		SNew(SBox)
		.Visibility(EVisibility::SelfHitTestInvisible)
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Top)
		.Padding(FMargin(0.f, 28.f, 14.f, 0.f))
		[
			SNew(SBox)
			.WidthOverride(248.f)
			.Visibility(this, &SFastLightPanel::GetPanelVisibility)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
				.Padding(FMargin(10.f, 8.f))
				.ToolTipText(LOCTEXT("PanelTip", "拖拽视口里的黄色箭头到道具或角色上。灯光会转向落点，并标出光线和表面的交点。拖拽时滚动滚轮可调整距离，按住 Alt 再滚动也可以。"))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.f, 0.f, 0.f, 8.f)
					[
						SNew(STextBlock)
						.Text(this, &SFastLightPanel::GetTitleText)
						.Font(FAppStyle::GetFontStyle("BoldFont"))
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.f, 2.f)
					[
						MakeRow(
							LOCTEXT("Intensity", "强度"),
							SNew(SSpinBox<float>)
							.MinValue(0.f)
							.MaxValue(100000000.f)
							.Delta(0.1f)
							.SliderExponent(3.f)
							.Value_Lambda([this]()
							{
								const ULightComponent* Light = GetLight();
								return Light ? Light->Intensity : 0.f;
							})
							.OnBeginSliderMovement(this, &SFastLightPanel::OnBeginIntensitySlider)
							.OnEndSliderMovement(this, &SFastLightPanel::OnEndSlider)
							.OnValueChanged(this, &SFastLightPanel::OnIntensityChanged)
							.OnValueCommitted(this, &SFastLightPanel::OnIntensityCommitted)
						)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.f, 2.f)
					[
						SNew(SBox)
						.Visibility(this, &SFastLightPanel::GetLocalLightVisibility)
						[
							MakeRow(
								LOCTEXT("Units", "单位"),
								SAssignNew(UnitCombo, SComboBox<TSharedPtr<FString>>)
								.OptionsSource(&UnitLabels)
								.OnGenerateWidget_Lambda([](TSharedPtr<FString> Item)
								{
									return SNew(STextBlock)
										.Text(FText::FromString(Item.IsValid() ? *Item : FString()))
										.Font(FAppStyle::GetFontStyle("SmallFont"));
								})
								.OnSelectionChanged(this, &SFastLightPanel::OnUnitSelected)
								.Content()
								[
									SNew(STextBlock)
									.Font(FAppStyle::GetFontStyle("SmallFont"))
									.Text_Lambda([this]()
									{
										const TSharedPtr<FString> Label = GetCurrentUnitLabel();
										return FText::FromString(Label.IsValid() ? *Label : FString());
									})
								]
							)
						]
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.f, 2.f)
					[
						SNew(SBox)
						.Visibility(this, &SFastLightPanel::GetLocalLightVisibility)
						[
							MakeRow(
								LOCTEXT("Attenuation", "衰减"),
								SNew(SSpinBox<float>)
								.MinValue(0.f)
								.MaxValue(1000000.f)
								.Delta(1.f)
								.SliderExponent(2.f)
								.Value_Lambda([this]()
								{
									const ULocalLightComponent* Light = GetLocalLight();
									return Light ? Light->AttenuationRadius : 0.f;
								})
								.OnBeginSliderMovement(this, &SFastLightPanel::OnBeginAttenuationSlider)
								.OnEndSliderMovement(this, &SFastLightPanel::OnEndSlider)
								.OnValueChanged(this, &SFastLightPanel::OnAttenuationChanged)
								.OnValueCommitted(this, &SFastLightPanel::OnAttenuationCommitted)
							)
						]
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.f, 2.f)
					[
						MakeRow(
							LOCTEXT("Volumetric", "体积"),
							SNew(SSpinBox<float>)
							.MinValue(0.f)
							.MaxValue(1000.f)
							.Delta(0.01f)
							.Value_Lambda([this]()
							{
								const ULightComponent* Light = GetLight();
								return Light ? Light->VolumetricScatteringIntensity : 0.f;
							})
							.OnBeginSliderMovement(this, &SFastLightPanel::OnBeginVolumetricSlider)
							.OnEndSliderMovement(this, &SFastLightPanel::OnEndSlider)
							.OnValueChanged(this, &SFastLightPanel::OnVolumetricChanged)
							.OnValueCommitted(this, &SFastLightPanel::OnVolumetricCommitted)
						)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.f, 2.f)
					[
						MakeRow(
							LOCTEXT("Color", "颜色"),
							SNew(SColorBlock)
							.Color_Lambda([this]()
							{
								const ULightComponent* Light = GetLight();
								return Light ? Light->GetLightColor() : FLinearColor::White;
							})
							.Size(FVector2D(72.f, 16.f))
							.OnMouseButtonDown(this, &SFastLightPanel::OnColorBlockClicked)
						)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.f, 8.f, 0.f, 0.f)
					[
						SNew(STextBlock)
						.Text(this, &SFastLightPanel::GetHitText)
						.Font(FAppStyle::GetFontStyle("SmallFont"))
						.ColorAndOpacity(FSlateColor::UseSubduedForeground())
						.AutoWrapText(true)
					]
				]
			]
		]
	];
}

void SFastLightPanel::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	if(!UnitCombo.IsValid())
	{
		return;
	}

	const TSharedPtr<FString> Desired = GetCurrentUnitLabel();
	if(Desired.IsValid() && UnitCombo->GetSelectedItem() != Desired)
	{
		bRefreshingUnits = true;
		UnitCombo->SetSelectedItem(Desired);
		bRefreshingUnits = false;
	}
}

ULightComponent* SFastLightPanel::GetLight() const
{
	return FastLightAim::FindSelectedLight();
}

ULocalLightComponent* SFastLightPanel::GetLocalLight() const
{
	return Cast<ULocalLightComponent>(GetLight());
}

EVisibility SFastLightPanel::GetPanelVisibility() const
{
	return GetLight() ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility SFastLightPanel::GetLocalLightVisibility() const
{
	return GetLocalLight() ? EVisibility::Visible : EVisibility::Collapsed;
}

FText SFastLightPanel::GetTitleText() const
{
	const ULightComponent* Light = GetLight();
	if(!Light)
	{
		return FText::GetEmpty();
	}

	FString TypeName = TEXT("灯光");
	if(Light->IsA<URectLightComponent>())
	{
		TypeName = TEXT("面光源");
	}
	else if(Light->IsA<USpotLightComponent>())
	{
		TypeName = TEXT("聚光灯");
	}
	else if(Light->IsA<UPointLightComponent>())
	{
		TypeName = TEXT("点光源");
	}
	else if(Light->IsA<UDirectionalLightComponent>())
	{
		TypeName = TEXT("定向光");
	}

	const AActor* Owner = Light->GetOwner();
	const FString ActorLabel = Owner ? Owner->GetActorLabel() : Light->GetName();
	return FText::FromString(FString::Printf(TEXT("%s   %s"), *TypeName, *ActorLabel));
}

FText SFastLightPanel::GetHitText() const
{
	const ULightComponent* Light = GetLight();
	if(!Light)
	{
		return FText::GetEmpty();
	}

	const FFastLightSurfaceHit* Hit = FFastLightAimState::Get().FindHit(Light);
	if(!Hit || !Hit->bOnSurface)
	{
		return LOCTEXT("NoHit", "当前方向上没有照到表面。拖拽黄色箭头到模型上。");
	}
	if(Hit->Label.IsEmpty())
	{
		return FText::FromString(FString::Printf(TEXT("交点   %.0f cm"), Hit->Distance));
	}
	return FText::FromString(FString::Printf(TEXT("交点   %s   %.0f cm"), *Hit->Label, Hit->Distance));
}

TSharedPtr<FString> SFastLightPanel::GetCurrentUnitLabel() const
{
	const ULocalLightComponent* Light = GetLocalLight();
	if(!Light)
	{
		return nullptr;
	}
	const int32 Index = UnitValues.IndexOfByKey(Light->IntensityUnits);
	return UnitLabels.IsValidIndex(Index) ? UnitLabels[Index] : nullptr;
}

void SFastLightPanel::BeginEdit(FText Description)
{
	if(bEditing || !GEditor)
	{
		return;
	}
	if(ULightComponent* Light = GetLight())
	{
		GEditor->BeginTransaction(Description);
		Light->Modify();
		bEditing = true;
	}
}

void SFastLightPanel::EndEdit()
{
	if(!bEditing)
	{
		return;
	}
	if(GEditor)
	{
		GEditor->EndTransaction();
	}
	bEditing = false;
}

void SFastLightPanel::ApplyFloat(UObject* Object, FName PropertyName, float NewValue)
{
	if(!Object)
	{
		return;
	}

	FFloatProperty* Property = FindFProperty<FFloatProperty>(Object->GetClass(), PropertyName);
	if(!Property)
	{
		return;
	}

	Property->SetPropertyValue_InContainer(Object, NewValue);
	FPropertyChangedEvent Event(Property, EPropertyChangeType::ValueSet);
	Object->PostEditChangeProperty(Event);
}

void SFastLightPanel::OnIntensityChanged(float NewValue)
{
	if(!bEditing)
	{
		BeginEdit(LOCTEXT("EditIntensity", "修改灯光强度"));
	}
	ApplyFloat(GetLight(), GET_MEMBER_NAME_CHECKED(ULightComponent, Intensity), NewValue);
}

void SFastLightPanel::OnIntensityCommitted(float NewValue, ETextCommit::Type CommitType)
{
	OnIntensityChanged(NewValue);
	EndEdit();
}

void SFastLightPanel::OnAttenuationChanged(float NewValue)
{
	if(!bEditing)
	{
		BeginEdit(LOCTEXT("EditAttenuation", "修改衰减半径"));
	}
	ApplyFloat(GetLocalLight(), GET_MEMBER_NAME_CHECKED(ULocalLightComponent, AttenuationRadius), FMath::Max(NewValue, 0.f));
}

void SFastLightPanel::OnAttenuationCommitted(float NewValue, ETextCommit::Type CommitType)
{
	OnAttenuationChanged(NewValue);
	EndEdit();
}

void SFastLightPanel::OnVolumetricChanged(float NewValue)
{
	if(!bEditing)
	{
		BeginEdit(LOCTEXT("EditVolumetric", "修改体积散射"));
	}
	ApplyFloat(GetLight(), GET_MEMBER_NAME_CHECKED(ULightComponent, VolumetricScatteringIntensity), FMath::Max(NewValue, 0.f));
}

void SFastLightPanel::OnVolumetricCommitted(float NewValue, ETextCommit::Type CommitType)
{
	OnVolumetricChanged(NewValue);
	EndEdit();
}

void SFastLightPanel::OnBeginIntensitySlider()
{
	BeginEdit(LOCTEXT("EditIntensity", "修改灯光强度"));
}

void SFastLightPanel::OnBeginAttenuationSlider()
{
	BeginEdit(LOCTEXT("EditAttenuation", "修改衰减半径"));
}

void SFastLightPanel::OnBeginVolumetricSlider()
{
	BeginEdit(LOCTEXT("EditVolumetric", "修改体积散射"));
}

void SFastLightPanel::OnEndSlider(float NewValue)
{
	EndEdit();
}

void SFastLightPanel::OnUnitSelected(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if(bRefreshingUnits || !Item.IsValid())
	{
		return;
	}

	ULocalLightComponent* Light = GetLocalLight();
	const int32 Index = UnitLabels.IndexOfByKey(Item);
	if(!Light || !UnitValues.IsValidIndex(Index) || Light->IntensityUnits == UnitValues[Index])
	{
		return;
	}

	const ELightUnits OldUnits = Light->IntensityUnits;
	const ELightUnits NewUnits = UnitValues[Index];
	float CosHalfConeAngle = -1.f;
	if(const USpotLightComponent* Spot = Cast<USpotLightComponent>(Light))
	{
		CosHalfConeAngle = FMath::Cos(FMath::DegreesToRadians(Spot->OuterConeAngle));
	}
	const float Factor = ULocalLightComponent::GetUnitsConversionFactor(OldUnits, NewUnits, CosHalfConeAngle);

	FScopedTransaction Transaction(LOCTEXT("EditUnits", "修改灯光单位"));
	Light->Modify();
	Light->Intensity *= Factor;
	Light->SetIntensityUnits(NewUnits);
	ApplyFloat(Light, GET_MEMBER_NAME_CHECKED(ULightComponent, Intensity), Light->Intensity);
}

FReply SFastLightPanel::OnColorBlockClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	ULightComponent* Light = GetLight();
	if(!Light || MouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
	{
		return FReply::Unhandled();
	}

	FColorPickerArgs Args;
	Args.bUseAlpha = false;
	Args.bOnlyRefreshOnOk = false;
	Args.InitialColor = Light->GetLightColor();
	Args.OnInteractivePickBegin = FSimpleDelegate::CreateSP(this, &SFastLightPanel::BeginEdit, LOCTEXT("EditColor", "修改灯光颜色"));
	Args.OnInteractivePickEnd = FSimpleDelegate::CreateSP(this, &SFastLightPanel::EndEdit);
	Args.OnColorCommitted = FOnLinearColorValueChanged::CreateSP(this, &SFastLightPanel::OnColorCommitted);
	OpenColorPicker(Args);
	return FReply::Handled();
}

void SFastLightPanel::OnColorCommitted(FLinearColor NewColor)
{
	ULightComponent* Light = GetLight();
	if(!Light)
	{
		return;
	}

	TUniquePtr<FScopedTransaction> LocalTransaction;
	if(!bEditing && GEditor)
	{
		LocalTransaction = MakeUnique<FScopedTransaction>(LOCTEXT("EditColor", "修改灯光颜色"));
		Light->Modify();
	}

	Light->SetLightColor(NewColor);
	FProperty* Property = FindFProperty<FProperty>(ULightComponent::StaticClass(), GET_MEMBER_NAME_CHECKED(ULightComponent, LightColor));
	if(Property)
	{
		FPropertyChangedEvent Event(Property, EPropertyChangeType::ValueSet);
		Light->PostEditChangeProperty(Event);
	}
}

#undef LOCTEXT_NAMESPACE
