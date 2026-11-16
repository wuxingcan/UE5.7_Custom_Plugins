// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"
#include "Containers/Ticker.h"
#include "Misc/FrameNumber.h"

class AActor;
class USceneComponent;
class ULevelSequence;

DECLARE_DELEGATE_ThreeParams(FOnBatchScreenShotProgress, const FString& /*Status*/, int32 /*Current*/, int32 /*Total*/);
DECLARE_DELEGATE(FOnBatchScreenShotFinished);

/**
 * Sequentially opens Level Sequences, locks camera cut to viewport,
 * optionally hides skeletal meshes, then takes high-res screenshots at the
 * configured size multiplier at start / middle / end frames.
 */
class FBatchScreenShotRunner : public TSharedFromThis<FBatchScreenShotRunner>
{
public:
	static constexpr int32 ShotsPerSequence = 3;

	void Start(
		const TArray<FAssetData>& InSequences,
		bool bInHideSkeletalMeshes,
		float InScreenshotSizeMultiplier,
		FOnBatchScreenShotProgress InOnProgress,
		FOnBatchScreenShotFinished InOnFinished);

	void Cancel();
	bool IsRunning() const { return bRunning; }

private:
	enum class EStep : uint8
	{
		Idle,
		OpenSequence,
		PrepareView,
		SeekFrame,
		Capture,
		WaitForScreenshot,
		AdvanceShot,
		AdvanceSequence
	};

	bool Tick(float DeltaTime);
	void SetStatus(const FString& Message);
	void Finish();
	void OnScreenshotProcessed();
	void RestoreHiddenActors();
	void HideSkeletalMeshesForActiveSequence();
	bool OpenCurrentSequence();
	bool IsCurrentSequenceReady() const;
	bool BuildShotFramesForCurrentSequence();
	bool SeekToCurrentShotFrame();
	void TakeScreenshotForCurrentShot();
	FString GetCurrentSequenceName() const;
	FString GetShotLabel() const;
	int32 GetProgressCurrent() const;
	int32 GetProgressTotal() const;

	TArray<FAssetData> Sequences;
	TArray<FFrameNumber> ShotFrames;
	int32 CurrentIndex = INDEX_NONE;
	int32 CaptureShotIndex = 0;
	bool bHideSkeletalMeshes = false;
	float ScreenshotSizeMultiplier = 1.f;
	bool bRunning = false;
	EStep Step = EStep::Idle;
	float StepTimer = 0.f;

	FOnBatchScreenShotProgress OnProgress;
	FOnBatchScreenShotFinished OnFinished;
	FTSTicker::FDelegateHandle TickerHandle;
	FDelegateHandle ScreenshotProcessedHandle;
	bool bScreenshotProcessed = false;

	struct FHiddenActorState
	{
		TWeakObjectPtr<AActor> Actor;
		bool bWasTemporarilyHiddenInEditor = false;
		bool bWasActorHiddenInGame = false;
		TArray<TPair<TWeakObjectPtr<USceneComponent>, bool>> ComponentVisibility;
	};
	TArray<FHiddenActorState> HiddenActors;
};
