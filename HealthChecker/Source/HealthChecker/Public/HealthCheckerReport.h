// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

struct FHealthCheckerTableRow
{
	FString Label;
	int32 Value = 0;
	int32 TotalValue = 0;
	FString Unit;
	FString TotalLabel;
	bool bHasRatio = false;
	float Ratio = 0.f;
};

struct FHealthCheckerTableSection
{
	FString Title;
	FString Score;
	FString Description;
	TArray<FHealthCheckerTableRow> Rows;
};

struct FHealthCheckerReportView
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
	TArray<FHealthCheckerTableSection> Sections;
};

namespace HealthCheckerReport
{
	const FHealthCheckerReportView& GetLast();
	void SetLast(FHealthCheckerReportView View);
}
