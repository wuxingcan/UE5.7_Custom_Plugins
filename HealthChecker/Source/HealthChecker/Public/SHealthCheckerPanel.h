// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HealthCheckerReport.h"
#include "Widgets/SCompoundWidget.h"

class IDetailsView;
class SScrollBox;

class SHealthCheckerPanel : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SHealthCheckerPanel) {}
		SLATE_ARGUMENT(TArray<FString>, FolderPaths)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	static void Open(const TArray<FString>& FolderPaths);
	void SetFolderPaths(const TArray<FString>& InFolderPaths);

private:

	FReply OnCheckClicked();
	FReply OnSettingsClicked();
	void RebuildResults();
	TSharedRef<SWidget> BuildSection(const FHealthCheckerTableSection& Section) const;
	TSharedRef<SWidget> BuildTableRow(const FHealthCheckerTableRow& Row, bool bHeader) const;
	FText GetFolderPathText() const;
	FText GetSettingsButtonText() const;
	FLinearColor GetScoreColor(const FString& Score) const;

	TArray<FString> FolderPaths;
	FHealthCheckerReportView ReportView;
	int32 MaxDisplayRows = 10;
	bool bShowSettings = false;

	TSharedPtr<IDetailsView> SettingsView;
	TSharedPtr<SBox> SettingsContainer;
	TSharedPtr<SScrollBox> ResultsBox;
	TSharedPtr<STextBlock> FolderPathText;
};
