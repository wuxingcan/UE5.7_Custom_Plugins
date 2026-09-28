// Copyright Epic Games, Inc. All Rights Reserved.

#include "FastLight.h"

#include "FastLightAimVisualizer.h"
#include "FastLightShared.h"
#include "SFastLightPanel.h"

#include "ComponentVisualizer.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/RectLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Framework/Application/SlateApplication.h"
#include "ILevelEditor.h"
#include "LevelEditor.h"
#include "SLevelViewport.h"
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"

#define LOCTEXT_NAMESPACE "FastLight"

void FFastLightModule::StartupModule()
{
	if(GUnrealEd)
	{
		OnEngineInit();
	}
	else
	{
		FCoreDelegates::OnPostEngineInit.AddRaw(this, &FFastLightModule::OnEngineInit);
	}
}

void FFastLightModule::ShutdownModule()
{
	FCoreDelegates::OnPostEngineInit.RemoveAll(this);
	if(OverlayTickerHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(OverlayTickerHandle);
		OverlayTickerHandle.Reset();
	}
	FFastLightAimState::Get().CancelAim();
	DetachOverlay();
	UnregisterInput();
	UnregisterVisualizers();
	bEngineInitDone = false;
}

void FFastLightModule::OnEngineInit()
{
	if(bEngineInitDone)
	{
		return;
	}
	bEngineInitDone = true;
	RegisterVisualizers();
	RegisterInput();
	OverlayTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateRaw(this, &FFastLightModule::TryAttachOverlay),
		0.25f);
}

void FFastLightModule::RegisterVisualizers()
{
	if(!GUnrealEd)
	{
		return;
	}

	const UClass* Classes[] = {
		UPointLightComponent::StaticClass(),
		USpotLightComponent::StaticClass(),
		URectLightComponent::StaticClass(),
		UDirectionalLightComponent::StaticClass()
	};

	for(const UClass* Class : Classes)
	{
		const FName ClassName = Class->GetFName();
		TSharedPtr<FComponentVisualizer> Existing = GUnrealEd->FindComponentVisualizer(ClassName);
		if(FFastLightAimVisualizer::IsOurVisualizer(Existing.Get()))
		{
			continue;
		}

		TSharedPtr<FFastLightAimVisualizer> Wrapper = MakeShared<FFastLightAimVisualizer>(Existing);
		GUnrealEd->RegisterComponentVisualizer(ClassName, Wrapper);
		WrappedVisualizers.Add({ ClassName, Existing });
	}
}

void FFastLightModule::UnregisterVisualizers()
{
	if(!GUnrealEd)
	{
		WrappedVisualizers.Reset();
		return;
	}

	for(const FWrappedVisualizer& Wrapped : WrappedVisualizers)
	{
		if(Wrapped.Original.IsValid())
		{
			GUnrealEd->RegisterComponentVisualizer(Wrapped.ClassName, Wrapped.Original);
		}
		else
		{
			GUnrealEd->UnregisterComponentVisualizer(Wrapped.ClassName);
		}
	}
	WrappedVisualizers.Reset();
}

void FFastLightModule::RegisterInput()
{
	if(!FSlateApplication::IsInitialized() || InputProcessor.IsValid())
	{
		return;
	}

	InputProcessor = MakeShared<FFastLightInputProcessor>();
	FSlateApplication::Get().RegisterInputPreProcessor(InputProcessor);
}

void FFastLightModule::UnregisterInput()
{
	if(InputProcessor.IsValid() && FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().UnregisterInputPreProcessor(InputProcessor);
	}
	InputProcessor.Reset();
}

bool FFastLightModule::TryAttachOverlay(float DeltaTime)
{
	if(!FModuleManager::Get().IsModuleLoaded("LevelEditor"))
	{
		return true;
	}

	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<ILevelEditor> Editor = LevelEditor.Pin();
	if(!Editor.IsValid())
	{
		Editor = LevelEditorModule.GetFirstLevelEditor();
		LevelEditor = Editor;
	}
	if(!Editor.IsValid())
	{
		return true;
	}

	TSharedPtr<SLevelViewport> Viewport = Editor->GetActiveViewportInterface();
	if(!Viewport.IsValid())
	{
		return true;
	}

	if(!OverlayWidget.IsValid())
	{
		OverlayWidget = SNew(SFastLightPanel);
	}
	Viewport->AddOverlayWidget(OverlayWidget.ToSharedRef());
	OverlayTickerHandle.Reset();
	return false;
}

void FFastLightModule::DetachOverlay()
{
	if(!OverlayWidget.IsValid())
	{
		return;
	}

	if(TSharedPtr<ILevelEditor> Editor = LevelEditor.Pin())
	{
		if(TSharedPtr<SLevelViewport> Viewport = Editor->GetActiveViewportInterface())
		{
			Viewport->RemoveOverlayWidget(OverlayWidget.ToSharedRef());
		}
	}
	OverlayWidget.Reset();
	LevelEditor.Reset();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFastLightModule, FastLight)
