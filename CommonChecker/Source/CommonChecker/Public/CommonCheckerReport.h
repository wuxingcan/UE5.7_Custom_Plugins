// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

struct FCommonCheckerTableRow
{
	FString Label;
	int32 Value = 0;
	int32 TotalValue = 0;
	FString Unit;
	FString TotalLabel;
	bool bHasRatio = false;
	float Ratio = 0.f;
	FString AssetPath;
	FString Score;
};

struct FCommonCheckerTableSection
{
	FString Title;
	FString Score;
	FString Description;
	TArray<FCommonCheckerTableRow> Rows;
};

struct FCommonCheckerReportView
{
	bool bValid = false;
	FString Project;
	FString Map;
	FString Engine;
	FString GeneratedBy;
	FString Version;
	FString LastUpdate;
	FString OverallScore;
	FString OverallDescription;
	TArray<FCommonCheckerTableSection> Sections;
};

namespace CommonCheckerReport
{
	const FCommonCheckerReportView& GetLast();
	void SetLast(FCommonCheckerReportView View);
}
