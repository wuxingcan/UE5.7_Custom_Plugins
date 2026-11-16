// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"
#include "Widgets/SCompoundWidget.h"

class SCheckBox;
class SProgressBar;
class SVerticalBox;
class STextBlock;

struct FBatchScreenShotSequenceItem
{
	FAssetData AssetData;
	bool bSelected = true;
};

class SBatchScreenShotPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBatchScreenShotPanel) {}
		SLATE_ARGUMENT(TArray<FString>, FolderPaths)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	static void Open(const TArray<FString>& FolderPaths);
	void SetFolderPaths(const TArray<FString>& InFolderPaths);

private:
	void RefreshSequenceList();
	void RebuildSequenceListWidget();
	void SetAllSelected(bool bSelected);

	FReply OnSelectAllClicked();
	FReply OnDeselectAllClicked();
	FReply OnExecuteClicked();
	FReply OnStopClicked();
	FReply OnOpenSequenceClicked(int32 Index);

	FText GetFolderPathText() const;
	FText GetStatusText() const;
	FText GetProgressText() const;
	TOptional<float> GetProgressPercent() const;
	EVisibility GetProgressVisibility() const;
	bool CanExecute() const;

	TArray<FString> FolderPaths;
	TArray<FBatchScreenShotSequenceItem> SequenceItems;
	bool bHideSkeletalMeshes = true;
	float ScreenshotSizeMultiplier = 1.f;
	bool bIsRunning = false;
	FString StatusMessage;
	int32 ProgressCurrent = 0;
	int32 ProgressTotal = 0;

	TSharedPtr<STextBlock> FolderPathText;
	TSharedPtr<STextBlock> StatusText;
	TSharedPtr<SVerticalBox> SequenceListBox;
	TSharedPtr<SCheckBox> HideSkeletalCheckBox;
};
