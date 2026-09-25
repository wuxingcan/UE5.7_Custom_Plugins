// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "HealthCheckerEditorSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHealthChecker, Log, All);

UCLASS()
class UHealthCheckerEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Editor")
	static void OpenHealthCheckerSettings();

	UFUNCTION(BlueprintCallable, Category="Editor")
	static bool RunHealthChecker(bool bSkipAutoOpenReport = false);
};
