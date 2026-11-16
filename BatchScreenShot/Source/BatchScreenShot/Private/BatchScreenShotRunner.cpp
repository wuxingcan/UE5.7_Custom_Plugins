// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatchScreenShotRunner.h"

#include "Subsystems/AssetEditorSubsystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Editor.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "HighResScreenshot.h"
#include "ILevelSequenceEditorToolkit.h"
#include "ISequencer.h"
#include "LevelSequence.h"
#include "LevelSequenceEditorBlueprintLibrary.h"
#include "Misc/Paths.h"
#include "MovieScene.h"
#include "MovieSceneSequencePlayer.h"
#include "MovieSceneTimeHelpers.h"
#include "MovieSceneTimeUnit.h"
#include "UnrealClient.h"

namespace BatchScreenShotRunnerPrivate
{
	static constexpr float OpenSettleTime = 0.75f;
	static constexpr float SeekSettleTime = 0.5f;

	static bool ActorHasSkeletalMesh(const AActor* Actor)
	{
		if(!Actor)
		{
			return false;
		}

		TInlineComponentArray<USkeletalMeshComponent*> SkelComps(Actor);
		return SkelComps.Num() > 0;
	}

	static void CollectSkeletalMeshActorsFromWorld(UWorld* World, TSet<AActor*>& OutActors)
	{
		if(!World)
		{
			return;
		}

		for(TActorIterator<AActor> It(World); It; ++It)
		{
			if(ActorHasSkeletalMesh(*It))
			{
				OutActors.Add(*It);
			}
		}
	}

	static TSharedPtr<ISequencer> FindSequencer(ULevelSequence* LevelSequence)
	{
		if(!LevelSequence || !GEditor)
		{
			return nullptr;
		}

		UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
		IAssetEditorInstance* AssetEditor = AssetEditorSubsystem
			? AssetEditorSubsystem->FindEditorForAsset(LevelSequence, false)
			: nullptr;
		ILevelSequenceEditorToolkit* LevelSequenceEditor = static_cast<ILevelSequenceEditorToolkit*>(AssetEditor);
		return LevelSequenceEditor ? LevelSequenceEditor->GetSequencer() : nullptr;
	}

	static void CollectSkeletalMeshActorsFromSequencer(ULevelSequence* LevelSequence, TSet<AActor*>& OutActors)
	{
		TSharedPtr<ISequencer> Sequencer = FindSequencer(LevelSequence);
		UMovieScene* MovieScene = LevelSequence ? LevelSequence->GetMovieScene() : nullptr;
		if(!Sequencer.IsValid() || !MovieScene)
		{
			return;
		}

		const TArray<FMovieSceneBinding>& Bindings = MovieScene->GetBindings();
		for(const FMovieSceneBinding& Binding : Bindings)
		{
			TArrayView<TWeakObjectPtr<>> BoundObjects = Sequencer->FindBoundObjects(
				Binding.GetObjectGuid(),
				Sequencer->GetFocusedTemplateID());

			for(const TWeakObjectPtr<>& WeakObject : BoundObjects)
			{
				UObject* BoundObject = WeakObject.Get();
				if(!BoundObject)
				{
					continue;
				}

				if(AActor* Actor = Cast<AActor>(BoundObject))
				{
					if(ActorHasSkeletalMesh(Actor))
					{
						OutActors.Add(Actor);
					}
				}
				else if(USkeletalMeshComponent* SkelComp = Cast<USkeletalMeshComponent>(BoundObject))
				{
					if(AActor* Owner = SkelComp->GetOwner())
					{
						OutActors.Add(Owner);
					}
				}
			}
		}
	}
}

void FBatchScreenShotRunner::Start(
	const TArray<FAssetData>& InSequences,
	bool bInHideSkeletalMeshes,
	float InScreenshotSizeMultiplier,
	FOnBatchScreenShotProgress InOnProgress,
	FOnBatchScreenShotFinished InOnFinished)
{
	Cancel();

	Sequences = InSequences;
	bHideSkeletalMeshes = bInHideSkeletalMeshes;
	ScreenshotSizeMultiplier = FMath::Max(0.01f, InScreenshotSizeMultiplier);
	OnProgress = MoveTemp(InOnProgress);
	OnFinished = MoveTemp(InOnFinished);
	CurrentIndex = 0;
	CaptureShotIndex = 0;
	ShotFrames.Reset();
	Step = EStep::OpenSequence;
	StepTimer = 0.f;
	bRunning = Sequences.Num() > 0;

	if(!bRunning)
	{
		SetStatus(TEXT("没有可执行的 Level Sequence。"));
		Finish();
		return;
	}

	SetStatus(FString::Printf(TEXT("开始批量截图（共 %d 个 Sequence，每个 3 张）..."), Sequences.Num()));
	TickerHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateSP(this, &FBatchScreenShotRunner::Tick),
		0.f);
}

void FBatchScreenShotRunner::Cancel()
{
	if(TickerHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
		TickerHandle.Reset();
	}
	if(ScreenshotProcessedHandle.IsValid())
	{
		FScreenshotRequest::OnScreenshotRequestProcessed().Remove(ScreenshotProcessedHandle);
		ScreenshotProcessedHandle.Reset();
	}
	bScreenshotProcessed = false;

	RestoreHiddenActors();
	ULevelSequenceEditorBlueprintLibrary::SetLockCameraCutToViewport(false);
	bRunning = false;
	Step = EStep::Idle;
	CurrentIndex = INDEX_NONE;
	CaptureShotIndex = 0;
	ShotFrames.Reset();
}

bool FBatchScreenShotRunner::Tick(float DeltaTime)
{
	if(!bRunning)
	{
		return false;
	}

	StepTimer += DeltaTime;

	switch(Step)
	{
	case EStep::OpenSequence:
		{
			RestoreHiddenActors();
			CaptureShotIndex = 0;
			ShotFrames.Reset();

			if(!OpenCurrentSequence())
			{
				SetStatus(FString::Printf(TEXT("跳过无法打开的 Sequence：%s"), *GetCurrentSequenceName()));
				Step = EStep::AdvanceSequence;
				StepTimer = 0.f;
				break;
			}

			SetStatus(FString::Printf(
				TEXT("(%d/%d) 已打开 %s，等待视图就绪..."),
				CurrentIndex + 1,
				Sequences.Num(),
				*GetCurrentSequenceName()));
			Step = EStep::PrepareView;
			StepTimer = 0.f;
		}
		break;

	case EStep::PrepareView:
		if(StepTimer >= BatchScreenShotRunnerPrivate::OpenSettleTime)
		{
			if(!IsCurrentSequenceReady())
			{
				OpenCurrentSequence();
				StepTimer = 0.f;
				break;
			}

			ULevelSequenceEditorBlueprintLibrary::Pause();
			ULevelSequenceEditorBlueprintLibrary::SetLockCameraCutToViewport(true);

			if(!BuildShotFramesForCurrentSequence())
			{
				SetStatus(FString::Printf(TEXT("跳过无有效时间范围的 Sequence：%s"), *GetCurrentSequenceName()));
				Step = EStep::AdvanceSequence;
				StepTimer = 0.f;
				break;
			}

			SetStatus(FString::Printf(
				TEXT("(%d/%d) 已切到相机，准备截图：%s"),
				CurrentIndex + 1,
				Sequences.Num(),
				*GetCurrentSequenceName()));
			Step = EStep::SeekFrame;
			StepTimer = 0.f;
		}
		break;

	case EStep::SeekFrame:
		{
			if(!IsCurrentSequenceReady())
			{
				Step = EStep::PrepareView;
				StepTimer = 0.f;
				break;
			}

			if(!SeekToCurrentShotFrame())
			{
				SetStatus(FString::Printf(
					TEXT("(%d/%d) 跳过无效帧 %s：%s"),
					CurrentIndex + 1,
					Sequences.Num(),
					*GetShotLabel(),
					*GetCurrentSequenceName()));
				Step = EStep::AdvanceShot;
				StepTimer = 0.f;
				break;
			}

			SetStatus(FString::Printf(
				TEXT("(%d/%d) 定位到%s帧：%s"),
				CurrentIndex + 1,
				Sequences.Num(),
				*GetShotLabel(),
				*GetCurrentSequenceName()));
			Step = EStep::Capture;
			StepTimer = 0.f;
		}
		break;

	case EStep::Capture:
		if(!IsCurrentSequenceReady())
		{
			SetStatus(FString::Printf(TEXT("(%d/%d) Sequence 编辑器状态已变化，重新准备：%s"),
				CurrentIndex + 1,
				Sequences.Num(),
				*GetCurrentSequenceName()));
			Step = EStep::PrepareView;
			StepTimer = 0.f;
			break;
		}

		if(StepTimer >= BatchScreenShotRunnerPrivate::SeekSettleTime)
		{
			if(FScreenshotRequest::IsScreenshotRequested() || GIsHighResScreenshot)
			{
				SetStatus(TEXT("等待上一张截图处理完成..."));
				break;
			}

			ULevelSequenceEditorBlueprintLibrary::Pause();
			ULevelSequenceEditorBlueprintLibrary::SetLockCameraCutToViewport(true);
			ULevelSequenceEditorBlueprintLibrary::ForceUpdate();

			// 最终求值会重新生成或显示 Spawnable，必须在求值后隐藏再请求截图。
			if(bHideSkeletalMeshes)
			{
				HideSkeletalMeshesForActiveSequence();
			}
			if(GEditor)
			{
				GEditor->RedrawLevelEditingViewports(true);
			}

			TakeScreenshotForCurrentShot();
			SetStatus(FString::Printf(
				TEXT("(%d/%d) 正在截图 %s：%s_%02d"),
				CurrentIndex + 1,
				Sequences.Num(),
				*GetShotLabel(),
				*GetCurrentSequenceName(),
				CaptureShotIndex + 1));
			Step = EStep::WaitForScreenshot;
			StepTimer = 0.f;
		}
		break;

	case EStep::WaitForScreenshot:
		if(bScreenshotProcessed)
		{
			if(ScreenshotProcessedHandle.IsValid())
			{
				FScreenshotRequest::OnScreenshotRequestProcessed().Remove(ScreenshotProcessedHandle);
				ScreenshotProcessedHandle.Reset();
			}
			Step = EStep::AdvanceShot;
			StepTimer = 0.f;
		}
		break;

	case EStep::AdvanceShot:
		++CaptureShotIndex;
		if(CaptureShotIndex >= ShotsPerSequence)
		{
			Step = EStep::AdvanceSequence;
		}
		else
		{
			Step = EStep::SeekFrame;
		}
		StepTimer = 0.f;
		break;

	case EStep::AdvanceSequence:
		{
			RestoreHiddenActors();
			++CurrentIndex;
			if(CurrentIndex >= Sequences.Num())
			{
				CurrentIndex = Sequences.Num() - 1;
				CaptureShotIndex = ShotsPerSequence - 1;
				SetStatus(FString::Printf(
					TEXT("批量截图完成，共 %d 个 Sequence（%d 张）。"),
					Sequences.Num(),
					GetProgressTotal()));
				Finish();
				return false;
			}

			Step = EStep::OpenSequence;
			StepTimer = 0.f;
		}
		break;

	default:
		break;
	}

	return true;
}

void FBatchScreenShotRunner::SetStatus(const FString& Message)
{
	if(OnProgress.IsBound())
	{
		OnProgress.Execute(Message, GetProgressCurrent(), GetProgressTotal());
	}
}

int32 FBatchScreenShotRunner::GetProgressTotal() const
{
	return Sequences.Num() * ShotsPerSequence;
}

int32 FBatchScreenShotRunner::GetProgressCurrent() const
{
	const int32 Total = GetProgressTotal();
	if(Total <= 0)
	{
		return 0;
	}

	if(!Sequences.IsValidIndex(CurrentIndex))
	{
		return Total;
	}

	return FMath::Clamp(CurrentIndex * ShotsPerSequence + CaptureShotIndex + 1, 0, Total);
}

void FBatchScreenShotRunner::Finish()
{
	if(TickerHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
		TickerHandle.Reset();
	}
	if(ScreenshotProcessedHandle.IsValid())
	{
		FScreenshotRequest::OnScreenshotRequestProcessed().Remove(ScreenshotProcessedHandle);
		ScreenshotProcessedHandle.Reset();
	}

	RestoreHiddenActors();
	ULevelSequenceEditorBlueprintLibrary::SetLockCameraCutToViewport(false);
	bRunning = false;
	Step = EStep::Idle;

	if(OnFinished.IsBound())
	{
		OnFinished.Execute();
	}
}

void FBatchScreenShotRunner::OnScreenshotProcessed()
{
	bScreenshotProcessed = true;
}

FString FBatchScreenShotRunner::GetCurrentSequenceName() const
{
	if(!Sequences.IsValidIndex(CurrentIndex))
	{
		return TEXT("Invalid");
	}
	return Sequences[CurrentIndex].AssetName.ToString();
}

FString FBatchScreenShotRunner::GetShotLabel() const
{
	switch(CaptureShotIndex)
	{
	case 0: return TEXT("首");
	case 1: return TEXT("中");
	case 2: return TEXT("尾");
	default: return TEXT("?");
	}
}

bool FBatchScreenShotRunner::OpenCurrentSequence()
{
	if(!Sequences.IsValidIndex(CurrentIndex))
	{
		return false;
	}

	ULevelSequence* LevelSequence = Cast<ULevelSequence>(Sequences[CurrentIndex].GetAsset());
	if(!LevelSequence)
	{
		return false;
	}

	return ULevelSequenceEditorBlueprintLibrary::OpenLevelSequence(LevelSequence);
}

bool FBatchScreenShotRunner::IsCurrentSequenceReady() const
{
	if(!Sequences.IsValidIndex(CurrentIndex))
	{
		return false;
	}

	ULevelSequence* LevelSequence = Cast<ULevelSequence>(Sequences[CurrentIndex].GetAsset());
	return LevelSequence
		&& ULevelSequenceEditorBlueprintLibrary::GetCurrentLevelSequence() == LevelSequence
		&& BatchScreenShotRunnerPrivate::FindSequencer(LevelSequence).IsValid();
}

bool FBatchScreenShotRunner::BuildShotFramesForCurrentSequence()
{
	ShotFrames.Reset();

	if(!Sequences.IsValidIndex(CurrentIndex))
	{
		return false;
	}

	ULevelSequence* LevelSequence = Cast<ULevelSequence>(Sequences[CurrentIndex].GetAsset());
	UMovieScene* MovieScene = LevelSequence ? LevelSequence->GetMovieScene() : nullptr;
	if(!MovieScene)
	{
		return false;
	}

	const TRange<FFrameNumber> PlaybackRange = MovieScene->GetPlaybackRange();
	const FFrameNumber StartFrame = UE::MovieScene::DiscreteInclusiveLower(PlaybackRange);
	const FFrameNumber ExclusiveEnd = UE::MovieScene::DiscreteExclusiveUpper(PlaybackRange);
	FFrameNumber EndFrame = ExclusiveEnd - 1;
	if(EndFrame < StartFrame)
	{
		EndFrame = StartFrame;
	}

	const int32 Span = EndFrame.Value - StartFrame.Value;
	const FFrameNumber MidFrame = StartFrame + (Span / 2);

	ShotFrames.Add(StartFrame);
	ShotFrames.Add(MidFrame);
	ShotFrames.Add(EndFrame);
	return ShotFrames.Num() == ShotsPerSequence;
}

bool FBatchScreenShotRunner::SeekToCurrentShotFrame()
{
	if(!ShotFrames.IsValidIndex(CaptureShotIndex))
	{
		return false;
	}

	ULevelSequenceEditorBlueprintLibrary::Pause();

	const FFrameNumber Frame = ShotFrames[CaptureShotIndex];
	FMovieSceneSequencePlaybackParams PlaybackParams(FFrameTime(Frame), EUpdatePositionMethod::Play);
	ULevelSequenceEditorBlueprintLibrary::SetGlobalPosition(PlaybackParams, EMovieSceneTimeUnit::TickResolution);
	ULevelSequenceEditorBlueprintLibrary::SetLockCameraCutToViewport(true);
	ULevelSequenceEditorBlueprintLibrary::ForceUpdate();
	if(GEditor)
	{
		GEditor->RedrawLevelEditingViewports(true);
	}
	return true;
}

void FBatchScreenShotRunner::HideSkeletalMeshesForActiveSequence()
{
	RestoreHiddenActors();

	TSet<AActor*> ActorsToHide;
	ULevelSequence* LevelSequence = nullptr;
	if(Sequences.IsValidIndex(CurrentIndex))
	{
		LevelSequence = Cast<ULevelSequence>(Sequences[CurrentIndex].GetAsset());
	}

	BatchScreenShotRunnerPrivate::CollectSkeletalMeshActorsFromSequencer(LevelSequence, ActorsToHide);

	// 绑定可能只解析成功一部分，始终补充世界中的骨骼网格体 Actor 以覆盖 Spawnable。
	UWorld* World = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
	BatchScreenShotRunnerPrivate::CollectSkeletalMeshActorsFromWorld(World, ActorsToHide);

	for(AActor* Actor : ActorsToHide)
	{
		if(!Actor)
		{
			continue;
		}

		FHiddenActorState& State = HiddenActors.AddDefaulted_GetRef();
		State.Actor = Actor;
		State.bWasTemporarilyHiddenInEditor = Actor->IsTemporarilyHiddenInEditor();
		State.bWasActorHiddenInGame = Actor->IsHidden();

		TInlineComponentArray<USkeletalMeshComponent*> SkelComps(Actor);
		for(USkeletalMeshComponent* SkelComp : SkelComps)
		{
			if(SkelComp)
			{
				State.ComponentVisibility.Emplace(SkelComp, SkelComp->GetVisibleFlag());
				SkelComp->SetVisibility(false, true);
				SkelComp->SetHiddenInGame(true, true);
				SkelComp->MarkRenderStateDirty();
			}
		}

		// 编辑器视口截图依赖 TemporarilyHiddenInEditor，仅 SetVisibility 对 Spawnable 不够。
		Actor->SetIsTemporarilyHiddenInEditor(true);
		Actor->SetActorHiddenInGame(true);
		Actor->MarkComponentsRenderStateDirty();
	}
}

void FBatchScreenShotRunner::RestoreHiddenActors()
{
	for(const FHiddenActorState& State : HiddenActors)
	{
		AActor* Actor = State.Actor.Get();
		if(!Actor)
		{
			continue;
		}

		for(const TPair<TWeakObjectPtr<USceneComponent>, bool>& CompState : State.ComponentVisibility)
		{
			if(USceneComponent* Component = CompState.Key.Get())
			{
				Component->SetVisibility(CompState.Value, true);
				Component->SetHiddenInGame(false, true);
			}
		}

		Actor->SetIsTemporarilyHiddenInEditor(State.bWasTemporarilyHiddenInEditor);
		Actor->SetActorHiddenInGame(State.bWasActorHiddenInGame);
		Actor->MarkComponentsRenderStateDirty();
	}

	HiddenActors.Reset();
}

void FBatchScreenShotRunner::TakeScreenshotForCurrentShot()
{
	const FString SequenceName = GetCurrentSequenceName();
	const FString Filename = FPaths::Combine(
		FPaths::ScreenShotDir(),
		FString::Printf(TEXT("%s_%02d"), *SequenceName, CaptureShotIndex + 1));

	FHighResScreenshotConfig& Config = GetHighResScreenshotConfig();
	Config.SetFilename(Filename);
	Config.ResolutionMultiplier = ScreenshotSizeMultiplier;
	Config.bDateTimeBasedNaming = false;
	Config.bMaskEnabled = false;

	bScreenshotProcessed = false;
	ScreenshotProcessedHandle = FScreenshotRequest::OnScreenshotRequestProcessed().AddSP(
		this, &FBatchScreenShotRunner::OnScreenshotProcessed);
	GIsHighResScreenshot = true;
	FScreenshotRequest::RequestScreenshot(false);
}
