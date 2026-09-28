// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "CommonCheckerEditorSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCommonChecker, Log, All);

UENUM(BlueprintType)
enum class ECommonCheckerScope : uint8
{
	CurrentLevel UMETA(DisplayName = "当前关卡"),
	ContentFolder UMETA(DisplayName = "内容目录")
};

UCLASS()
class UCommonCheckerEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Editor")
	static void OpenCommonCheckerSettings();

	UFUNCTION(BlueprintCallable, Category="Editor")
	static bool RunCommonChecker(bool bSkipAutoOpenReport = false);

	UFUNCTION(BlueprintCallable, Category="Editor")
	static bool RunCommonCheckerForFolders(const TArray<FString>& FolderPaths, bool bSkipAutoOpenReport = false, ECommonCheckerScope Scope = ECommonCheckerScope::CurrentLevel);
};
