// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonCheckerReport.h"
#include "Widgets/SCompoundWidget.h"

class IDetailsView;
class SScrollBox;

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
	TSharedRef<SWidget> BuildSection(const FCommonCheckerTableSection& Section);
	TSharedRef<SWidget> BuildTableRow(const FCommonCheckerTableRow& Row, bool bHeader) const;
	FReply OnRowClicked(const FCommonCheckerTableRow& Row) const;
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

	TArray<FString> FolderPaths;
	FCommonCheckerReportView ReportView;
	int32 MaxDisplayRows = 10;
	bool bShowSettings = false;
	TMap<FString, bool> CollapsedSections;
	TMap<FString, bool> EnlargedSections;

	TSharedPtr<IDetailsView> SettingsView;
	TSharedPtr<SBox> SettingsContainer;
	TSharedPtr<SScrollBox> ResultsBox;
	TSharedPtr<STextBlock> FolderPathText;
};
