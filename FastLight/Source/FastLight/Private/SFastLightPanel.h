// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Widgets/SCompoundWidget.h"
#include "Components/LocalLightComponent.h"

class ULightComponent;
template<typename OptionType> class SComboBox;

class SFastLightPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFastLightPanel) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	ULightComponent* GetLight() const;
	ULocalLightComponent* GetLocalLight() const;
	EVisibility GetPanelVisibility() const;
	EVisibility GetLocalLightVisibility() const;
	FText GetTitleText() const;
	FText GetHitText() const;
	TSharedPtr<FString> GetCurrentUnitLabel() const;

	void BeginEdit(FText Description);
	void EndEdit();
	void ApplyFloat(UObject* Object, FName PropertyName, float NewValue);
	void OnIntensityChanged(float NewValue);
	void OnIntensityCommitted(float NewValue, ETextCommit::Type CommitType);
	void OnAttenuationChanged(float NewValue);
	void OnAttenuationCommitted(float NewValue, ETextCommit::Type CommitType);
	void OnVolumetricChanged(float NewValue);
	void OnVolumetricCommitted(float NewValue, ETextCommit::Type CommitType);
	void OnBeginIntensitySlider();
	void OnBeginAttenuationSlider();
	void OnBeginVolumetricSlider();
	void OnEndSlider(float NewValue);
	void OnUnitSelected(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
	FReply OnColorBlockClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent);
	void OnColorCommitted(FLinearColor NewColor);

	TArray<TSharedPtr<FString>> UnitLabels;
	TArray<ELightUnits> UnitValues;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> UnitCombo;
	bool bEditing = false;
	bool bRefreshingUnits = false;
};
