// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ComponentVisualizer.h"
#include "Framework/Application/IInputProcessor.h"

class ULightComponent;
class FEditorViewportClient;
class FLevelEditorViewportClient;
class FPrimitiveDrawInterface;
class FSceneView;
class FCanvas;
class FViewport;

class FFastLightAimVisualizer : public FComponentVisualizer
{
public:
	explicit FFastLightAimVisualizer(TSharedPtr<FComponentVisualizer> InInner);

	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;
	virtual void DrawVisualizationHUD(const UActorComponent* Component, const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;
	virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click) override;
	virtual bool GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const override;
	virtual bool GetCustomInputCoordinateSystem(const FEditorViewportClient* ViewportClient, FMatrix& OutMatrix) const override;
	virtual bool HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale) override;
	virtual bool HandleInputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;
	virtual void TrackingStarted(FEditorViewportClient* InViewportClient) override;
	virtual void TrackingStopped(FEditorViewportClient* InViewportClient, bool bInDidMove) override;
	virtual void EndEditing() override;
	virtual UActorComponent* GetEditedComponent() const override;
	virtual bool ShouldAutoSelectElementOnHandleClick() const override;

	virtual ~FFastLightAimVisualizer() override;
	static bool IsOurVisualizer(const FComponentVisualizer* Visualizer);

private:
	TSharedPtr<FComponentVisualizer> Inner;
	TWeakObjectPtr<ULightComponent> EditedLight;
	bool bEditingAim = false;
	bool bForwardingToInner = false;
};

class FFastLightInputProcessor : public IInputProcessor
{
public:
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;
	virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;
	virtual bool HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;
	virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;
	virtual bool HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent) override;
	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;
	virtual const TCHAR* GetDebugName() const override { return TEXT("FastLightAim"); }

private:
	bool GetSceneMouse(const FPointerEvent& MouseEvent, FVector2D& OutPixel, FLevelEditorViewportClient*& OutClient) const;
	bool TraceCursor(const FVector2D& Pixel, FLevelEditorViewportClient* Client, const AActor* IgnoreActor, FHitResult& OutHit) const;
	void UpdateAimFromCursor(const FVector2D& Pixel, FLevelEditorViewportClient* Client, ULightComponent* Light) const;
};
