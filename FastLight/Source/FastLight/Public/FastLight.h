// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "Containers/Ticker.h"

class FComponentVisualizer;
class IInputProcessor;
class ILevelEditor;
class SWidget;

class FFastLightModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void OnEngineInit();
	void RegisterVisualizers();
	void UnregisterVisualizers();
	void RegisterInput();
	void UnregisterInput();
	bool TryAttachOverlay(float DeltaTime);
	void DetachOverlay();

	struct FWrappedVisualizer
	{
		FName ClassName;
		TSharedPtr<FComponentVisualizer> Original;
	};

	TArray<FWrappedVisualizer> WrappedVisualizers;
	TSharedPtr<IInputProcessor> InputProcessor;
	TSharedPtr<SWidget> OverlayWidget;
	TWeakPtr<ILevelEditor> LevelEditor;
	FTSTicker::FDelegateHandle OverlayTickerHandle;
	bool bEngineInitDone = false;
};
