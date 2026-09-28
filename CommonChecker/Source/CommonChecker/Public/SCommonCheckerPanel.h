// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonCheckerEditorSubsystem.h"
#include "CommonCheckerReport.h"
#include "Widgets/SCompoundWidget.h"

class IDetailsView;
class SVerticalBox;

class SCommonCheckerPanel : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SCommonCheckerPanel) {}
		SLATE_ARGUMENT(TArray<FString>, FolderPaths)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	static void Open(const TArray<FString>& FolderPaths);
	void SetFolderPaths(const TArray<FString>& InFolderPaths);

private:

	FReply OnCheckClicked();
	FReply OnSettingsClicked();
	void RebuildResults();
	TSharedRef<SWidget> BuildCategoryList();
	TSharedRef<SWidget> BuildSectionDetail(const FCommonCheckerTableSection& Section);
	TSharedRef<SWidget> BuildTableRow(const FCommonCheckerTableRow& Row, bool bHeader, bool bSelected, int32 RowIndex);
	FReply OnCategoryClicked(int32 SectionIndex);
	FReply OnDetailRowClicked(int32 RowIndex, FString AssetPath);
	void SyncContentBrowserToAsset(const FString& AssetPath) const;
	FText GetFolderPathText() const;
	FText GetSettingsButtonText() const;
	FText GetScoreLabel(const FString& Score) const;
	FLinearColor GetScoreColor(const FString& Score) const;
	const FSlateBrush* GetScoreIcon(const FString& Score) const;
	bool IsSectionCollapsed(const FString& Title) const;
	bool IsSectionEnlarged(const FString& Title) const;
	FReply ToggleSectionCollapsed(const FString& Title);
	FReply ToggleSectionEnlarged(const FString& Title);

	int32 SelectedSectionIndex = 0;
	int32 SelectedRowIndex = INDEX_NONE;

	TArray<FString> FolderPaths;
	ECommonCheckerScope CheckScope = ECommonCheckerScope::CurrentLevel;
	FCommonCheckerReportView ReportView;
	int32 MaxDisplayRows = 10;
	bool bShowSettings = false;
	TMap<FString, bool> CollapsedSections;
	TMap<FString, bool> EnlargedSections;

	TSharedPtr<IDetailsView> SettingsView;
	TSharedPtr<SBox> SettingsContainer;
	TSharedPtr<SVerticalBox> ResultsBox;
	TSharedPtr<STextBlock> FolderPathText;
};
