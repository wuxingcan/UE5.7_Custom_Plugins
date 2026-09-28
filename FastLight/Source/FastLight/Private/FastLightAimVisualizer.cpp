// Copyright Epic Games, Inc. All Rights Reserved.

#include "FastLightAimVisualizer.h"

#include "FastLightShared.h"

#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "Components/LightComponent.h"
#include "ComponentVisualizerManager.h"
#include "Editor.h"
#include "Editor/UnrealEdEngine.h"
#include "EditorViewportClient.h"
#include "UnrealEdGlobals.h"
#include "Engine/Engine.h"
#include "Framework/Application/SlateApplication.h"
#include "LevelEditorViewport.h"
#include "SceneManagement.h"
#include "SceneView.h"

namespace
{
	const FLinearColor GAimColor(1.f, 0.82f, 0.12f, 1.f);
	const FLinearColor GAimPressedColor(1.f, 1.f, 1.f, 1.f);

	struct HFastLightAimProxy : public HComponentVisProxy
	{
		DECLARE_HIT_PROXY();

		HFastLightAimProxy(const UActorComponent* InComponent)
			: HComponentVisProxy(InComponent, HPP_Foreground)
		{
		}

		virtual EMouseCursor::Type GetMouseCursor() override
		{
			return EMouseCursor::GrabHand;
		}
	};

	IMPLEMENT_HIT_PROXY(HFastLightAimProxy, HComponentVisProxy);

	void DrawDashed(FPrimitiveDrawInterface* PDI, const FVector& Start, const FVector& End, const FLinearColor& Color, float Thickness)
	{
		const FVector Delta = End - Start;
		const float Length = Delta.Size();
		if(Length < KINDA_SMALL_NUMBER)
		{
			return;
		}

		const FVector Direction = Delta / Length;
		const float Dash = FMath::Clamp(Length * 0.035f, 8.f, 28.f);
		const float Gap = Dash * 0.65f;
		for(float Distance = 0.f; Distance < Length; Distance += Dash + Gap)
		{
			const float DashEnd = FMath::Min(Distance + Dash, Length);
			PDI->DrawLine(Start + Direction * Distance, Start + Direction * DashEnd, Color, SDPG_Foreground, Thickness);
		}
	}
}

namespace
{
	TSet<const FFastLightAimVisualizer*>& GetLiveVisualizers()
	{
		static TSet<const FFastLightAimVisualizer*> Visualizers;
		return Visualizers;
	}
}

FFastLightAimVisualizer::FFastLightAimVisualizer(TSharedPtr<FComponentVisualizer> InInner)
	: Inner(MoveTemp(InInner))
{
	GetLiveVisualizers().Add(this);
}

FFastLightAimVisualizer::~FFastLightAimVisualizer()
{
	GetLiveVisualizers().Remove(this);
}

bool FFastLightAimVisualizer::IsOurVisualizer(const FComponentVisualizer* Visualizer)
{
	return GetLiveVisualizers().Contains(static_cast<const FFastLightAimVisualizer*>(Visualizer));
}

void FFastLightAimVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	if(Inner.IsValid())
	{
		Inner->DrawVisualization(Component, View, PDI);
	}

	const ULightComponent* Light = Cast<ULightComponent>(Component);
	if(!Light || !View || !PDI)
	{
		return;
	}

	const FVector Origin = Light->GetComponentLocation();
	const FVector Direction = Light->GetDirection().GetSafeNormal();
	if(Direction.IsNearlyZero())
	{
		return;
	}

	FFastLightAimState& State = FFastLightAimState::Get();
	const bool bThisDrag = State.bDragging && State.DraggingLight.Get() == Light;
	const float TraceDistance = FastLightAim::GetTraceDistance(Light);
	FVector End = Origin + Direction * FMath::Min(TraceDistance, 800.f);
	FFastLightSurfaceHit SurfaceHit;

	if(bThisDrag)
	{
		End = State.DragTarget;
		SurfaceHit = State.DragHit;
	}
	else if(UWorld* World = Light->GetWorld())
	{
		FHitResult Hit;
		const FVector TraceStart = Origin + Direction * 2.f;
		const FVector TraceEnd = Origin + Direction * TraceDistance;
		if(FastLightAim::TraceScene(World, TraceStart, TraceEnd, Light->GetOwner(), Hit))
		{
			End = Hit.ImpactPoint;
			SurfaceHit = FastLightAim::MakeHit(Light, Hit);
		}
	}

	State.SetHit(Light, SurfaceHit);

	const FVector LineEnd = SurfaceHit.bOnSurface || bThisDrag ? End : Origin + Direction * FMath::Clamp(TraceDistance * 0.35f, 120.f, 1200.f);
	const FVector DrawDirection = (LineEnd - Origin).GetSafeNormal();
	if(DrawDirection.IsNearlyZero())
	{
		return;
	}

	DrawDashed(PDI, Origin + DrawDirection * 6.f, LineEnd, GAimColor, bThisDrag ? 2.2f : 1.5f);

	const float ViewDistance = FMath::Max((View->ViewMatrices.GetViewOrigin() - LineEnd).Size(), 50.f);
	const float ViewHeight = FMath::Max(static_cast<float>(View->UnscaledViewRect.Height()), 1.f);
	const float HandleRadius = FMath::Clamp(ViewDistance * (14.f / ViewHeight), 5.f, 36.f);
	const FVector ToCamera = (View->ViewMatrices.GetViewOrigin() - LineEnd).GetSafeNormal();
	const FVector HandleCenter = LineEnd + ToCamera * HandleRadius;
	FVector HandleRight = FVector::CrossProduct(FVector::UpVector, ToCamera).GetSafeNormal();
	if(HandleRight.IsNearlyZero())
	{
		HandleRight = FVector::RightVector;
	}
	const FVector HandleUp = FVector::CrossProduct(ToCamera, HandleRight);

	const FLinearColor HandleColor = bThisDrag ? GAimPressedColor : GAimColor;
	PDI->SetHitProxy(new HFastLightAimProxy(Light));
	DrawCircle(PDI, HandleCenter, HandleRight, HandleUp, HandleColor, HandleRadius, 20, SDPG_Foreground, bThisDrag ? 2.75f : 1.6f);
	PDI->DrawPoint(HandleCenter, HandleColor, bThisDrag ? 16.f : 11.f, SDPG_Foreground);
	PDI->SetHitProxy(nullptr);
}

void FFastLightAimVisualizer::DrawVisualizationHUD(const UActorComponent* Component, const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas)
{
	if(Inner.IsValid())
	{
		Inner->DrawVisualizationHUD(Component, Viewport, View, Canvas);
	}

	const ULightComponent* Light = Cast<ULightComponent>(Component);
	if(!Light || !View || !Canvas || !GEngine)
	{
		return;
	}

	const FFastLightSurfaceHit* Hit = FFastLightAimState::Get().FindHit(Light);
	if(!Hit || !Hit->bOnSurface)
	{
		return;
	}

	FVector2D Pixel;
	if(!View->WorldToPixel(Hit->Location, Pixel))
	{
		return;
	}

	const FString Text = Hit->Label.IsEmpty()
		? FString::Printf(TEXT("%.0f cm"), Hit->Distance)
		: FString::Printf(TEXT("%s   %.0f cm"), *Hit->Label, Hit->Distance);
	FCanvasTextItem TextItem(Pixel + FVector2D(14.f, -18.f), FText::FromString(Text), GEngine->GetSmallFont(), GAimColor);
	TextItem.EnableShadow(FLinearColor::Black);
	Canvas->DrawItem(TextItem);
}

bool FFastLightAimVisualizer::VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click)
{
	if(VisProxy && VisProxy->IsA(HFastLightAimProxy::StaticGetType()) && Click.GetKey() == EKeys::LeftMouseButton)
	{
		ULightComponent* Light = const_cast<ULightComponent*>(Cast<ULightComponent>(VisProxy->Component.Get()));
		if(!Light)
		{
			return false;
		}

		bForwardingToInner = false;
		bEditingAim = true;
		EditedLight = Light;

		FFastLightAimState& State = FFastLightAimState::Get();
		State.DraggingLight = Light;
		State.bDragging = true;
		State.DragTarget = Light->GetComponentLocation() + Light->GetDirection() * 400.f;
		if(const FFastLightSurfaceHit* Existing = State.FindHit(Light))
		{
			if(Existing->bOnSurface)
			{
				State.DragTarget = Existing->Location;
				State.DragHit = *Existing;
			}
		}
		State.BeginAimTransaction(Light);
		return true;
	}

	bEditingAim = false;
	EditedLight.Reset();
	bForwardingToInner = Inner.IsValid() && Inner->VisProxyHandleClick(InViewportClient, VisProxy, Click);
	return bForwardingToInner;
}

bool FFastLightAimVisualizer::GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const
{
	if(bForwardingToInner && Inner.IsValid())
	{
		return Inner->GetWidgetLocation(ViewportClient, OutLocation);
	}
	return false;
}

bool FFastLightAimVisualizer::GetCustomInputCoordinateSystem(const FEditorViewportClient* ViewportClient, FMatrix& OutMatrix) const
{
	if(bForwardingToInner && Inner.IsValid())
	{
		return Inner->GetCustomInputCoordinateSystem(ViewportClient, OutMatrix);
	}
	return false;
}

namespace
{
	void AimLightFromPixel(FLevelEditorViewportClient* Client, const FVector2D& Pixel, ULightComponent* Light);
}

bool FFastLightAimVisualizer::HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale)
{
	if(bForwardingToInner && Inner.IsValid())
	{
		return Inner->HandleInputDelta(ViewportClient, Viewport, DeltaTranslate, DeltaRotate, DeltaScale);
	}
	return false;
}

bool FFastLightAimVisualizer::HandleInputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event)
{
	if(bEditingAim && Key == EKeys::Escape && Event == IE_Pressed)
	{
		if(GUnrealEd)
		{
			GUnrealEd->ComponentVisManager.ClearActiveComponentVis();
		}
		return true;
	}
	if(bForwardingToInner && Inner.IsValid())
	{
		return Inner->HandleInputKey(ViewportClient, Viewport, Key, Event);
	}
	return false;
}

void FFastLightAimVisualizer::TrackingStarted(FEditorViewportClient* InViewportClient)
{
	if(bForwardingToInner && Inner.IsValid())
	{
		Inner->TrackingStarted(InViewportClient);
	}
}

void FFastLightAimVisualizer::TrackingStopped(FEditorViewportClient* InViewportClient, bool bInDidMove)
{
	if(bForwardingToInner && Inner.IsValid())
	{
		Inner->TrackingStopped(InViewportClient, bInDidMove);
	}
}

void FFastLightAimVisualizer::EndEditing()
{
	if(bEditingAim)
	{
		if(ULightComponent* Light = EditedLight.Get())
		{
			if(AActor* Owner = Light->GetOwner())
			{
				Owner->PostEditMove(true);
			}
		}
		FFastLightAimState& State = FFastLightAimState::Get();
		State.bDragging = false;
		State.DraggingLight.Reset();
		State.EndAimTransaction();
		bEditingAim = false;
		EditedLight.Reset();
	}
	if(bForwardingToInner && Inner.IsValid())
	{
		Inner->EndEditing();
	}
	bForwardingToInner = false;
}

UActorComponent* FFastLightAimVisualizer::GetEditedComponent() const
{
	if(bEditingAim)
	{
		return EditedLight.Get();
	}
	if(bForwardingToInner && Inner.IsValid())
	{
		return Inner->GetEditedComponent();
	}
	return nullptr;
}

bool FFastLightAimVisualizer::ShouldAutoSelectElementOnHandleClick() const
{
	if(bEditingAim)
	{
		return false;
	}
	if(bForwardingToInner && Inner.IsValid())
	{
		return Inner->ShouldAutoSelectElementOnHandleClick();
	}
	return FComponentVisualizer::ShouldAutoSelectElementOnHandleClick();
}

void FFastLightInputProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{
}

bool FFastLightInputProcessor::GetSceneMouse(const FPointerEvent& MouseEvent, FVector2D& OutPixel, FLevelEditorViewportClient*& OutClient) const
{
	OutClient = GCurrentLevelEditingViewportClient;
	if(!OutClient || !OutClient->Viewport || !FSlateApplication::IsInitialized())
	{
		return false;
	}

	FSlateApplication& App = FSlateApplication::Get();
	const FWidgetPath Path = App.LocateWindowUnderMouse(MouseEvent.GetScreenSpacePosition(), App.GetInteractiveTopLevelWindows());
	if(!Path.IsValid() || Path.Widgets.Num() == 0)
	{
		return false;
	}

	for(int32 Index = Path.Widgets.Num() - 1; Index >= 0; --Index)
	{
		if(Path.Widgets[Index].Widget->GetType() == TEXT("SViewport"))
		{
			const FGeometry& Geometry = Path.Widgets[Index].Geometry;
			OutPixel = Geometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
			const FIntPoint Size = OutClient->Viewport->GetSizeXY();
			return OutPixel.X >= 0.f && OutPixel.Y >= 0.f && OutPixel.X < Size.X && OutPixel.Y < Size.Y;
		}
	}
	return false;
}

namespace
{
	bool DeprojectViewportPixel(FLevelEditorViewportClient* Client, const FVector2D& Pixel, FVector& OutOrigin, FVector& OutDirection)
	{
		if(!Client || !Client->Viewport || !Client->GetScene())
		{
			return false;
		}

		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			Client->Viewport,
			Client->GetScene(),
			Client->EngineShowFlags)
			.SetRealtimeUpdate(true));
		FSceneView* View = Client->CalcSceneView(&ViewFamily);
		if(!View)
		{
			return false;
		}

		FSceneView::DeprojectScreenToWorld(
			Pixel,
			View->UnscaledViewRect,
			View->ViewMatrices.GetInvViewProjectionMatrix(),
			OutOrigin,
			OutDirection);
		return !OutDirection.IsNearlyZero();
	}

	void AimLightFromPixel(FLevelEditorViewportClient* Client, const FVector2D& Pixel, ULightComponent* Light)
	{
		if(!Client || !Light)
		{
			return;
		}

		FVector RayOrigin = FVector::ZeroVector;
		FVector RayDirection = FVector::ForwardVector;
		if(!DeprojectViewportPixel(Client, Pixel, RayOrigin, RayDirection))
		{
			return;
		}
		RayDirection.Normalize();

		FFastLightAimState& State = FFastLightAimState::Get();
		FHitResult Hit;
		const bool bHit = FastLightAim::TraceScene(Client->GetWorld(), RayOrigin, RayOrigin + RayDirection * 500000.f, Light->GetOwner(), Hit);
		FVector Target = RayOrigin + RayDirection * 800.f;
		if(bHit)
		{
			Target = Hit.ImpactPoint;
			State.DragHit = FastLightAim::MakeHit(Light, Hit);
		}
		else
		{
			const float KeepDistance = FMath::Max(FVector::Distance(Light->GetComponentLocation(), State.DragTarget), 200.f);
			const FVector ViewDirection = Client->GetViewRotation().Vector();
			const float Denominator = FVector::DotProduct(RayDirection, ViewDirection);
			if(FMath::Abs(Denominator) > KINDA_SMALL_NUMBER)
			{
				const FVector PlanePoint = Light->GetComponentLocation() + Light->GetDirection() * KeepDistance;
				const float Travel = FVector::DotProduct(PlanePoint - RayOrigin, ViewDirection) / Denominator;
				if(Travel > 0.f)
				{
					Target = RayOrigin + RayDirection * Travel;
				}
			}
			State.DragHit = FFastLightSurfaceHit();
			State.DragHit.Location = Target;
			State.DragHit.Distance = FVector::Distance(Light->GetComponentLocation(), Target);
		}

		State.DragTarget = Target;
		FastLightAim::AimLightAt(Light, Target);
		if(GEditor)
		{
			GEditor->RedrawLevelEditingViewports();
		}
	}
}

bool FFastLightInputProcessor::TraceCursor(const FVector2D& Pixel, FLevelEditorViewportClient* Client, const AActor* IgnoreActor, FHitResult& OutHit) const
{
	if(!Client || !Client->GetWorld())
	{
		return false;
	}

	FVector RayOrigin = FVector::ZeroVector;
	FVector RayDirection = FVector::ForwardVector;
	if(!DeprojectViewportPixel(Client, Pixel, RayOrigin, RayDirection))
	{
		return false;
	}

	return FastLightAim::TraceScene(Client->GetWorld(), RayOrigin, RayOrigin + RayDirection * 500000.f, IgnoreActor, OutHit);
}

void FFastLightInputProcessor::UpdateAimFromCursor(const FVector2D& Pixel, FLevelEditorViewportClient* Client, ULightComponent* Light) const
{
	AimLightFromPixel(Client, Pixel, Light);
}

bool FFastLightInputProcessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	(void)SlateApp;
	(void)MouseEvent;
	return false;
}

bool FFastLightInputProcessor::HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	if(MouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
	{
		return false;
	}

	FFastLightAimState& State = FFastLightAimState::Get();
	if(!State.bDragging)
	{
		return false;
	}

	if(GUnrealEd)
	{
		GUnrealEd->ComponentVisManager.ClearActiveComponentVis();
	}
	else
	{
		State.bDragging = false;
		State.EndAimTransaction();
	}
	if(GEditor)
	{
		GEditor->RedrawLevelEditingViewports();
	}
	return false;
}

bool FFastLightInputProcessor::HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	FFastLightAimState& State = FFastLightAimState::Get();
	if(!State.bDragging || !MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return false;
	}

	ULightComponent* Light = State.DraggingLight.Get();
	if(!Light)
	{
		State.CancelAim();
		return false;
	}

	FVector2D Pixel;
	FLevelEditorViewportClient* Client = nullptr;
	if(!GetSceneMouse(MouseEvent, Pixel, Client))
	{
		return false;
	}

	AimLightFromPixel(Client, Pixel, Light);
	return true;
}

bool FFastLightInputProcessor::HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent)
{
	const float WheelDelta = InWheelEvent.GetWheelDelta();
	if(FMath::IsNearlyZero(WheelDelta) || InGestureEvent != nullptr)
	{
		return false;
	}

	FFastLightAimState& State = FFastLightAimState::Get();
	if(!State.bDragging)
	{
		return false;
	}

	if(ULightComponent* Light = State.DraggingLight.Get())
	{
		FastLightAim::AdjustDistance(Light, WheelDelta, false);
		return true;
	}
	return false;
}

bool FFastLightInputProcessor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	if(InKeyEvent.GetKey() != EKeys::Escape || !FFastLightAimState::Get().bDragging)
	{
		return false;
	}

	if(GUnrealEd)
	{
		GUnrealEd->ComponentVisManager.ClearActiveComponentVis();
	}
	else
	{
		FFastLightAimState::Get().CancelAim();
	}
	return true;
}
