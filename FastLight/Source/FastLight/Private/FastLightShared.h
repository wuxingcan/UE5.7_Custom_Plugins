// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class ULightComponent;
class AActor;

struct FFastLightSurfaceHit
{
	bool bOnSurface = false;
	FVector Location = FVector::ZeroVector;
	FVector Normal = FVector::UpVector;
	TWeakObjectPtr<AActor> Actor;
	FString Label;
	float Distance = 0.f;
};

class FFastLightAimState
{
public:
	static FFastLightAimState& Get();

	TWeakObjectPtr<ULightComponent> DraggingLight;
	bool bDragging = false;
	bool bTransactionOpen = false;
	FVector DragTarget = FVector::ZeroVector;
	FFastLightSurfaceHit DragHit;
	TMap<TWeakObjectPtr<ULightComponent>, FFastLightSurfaceHit> Hits;

	void BeginAimTransaction(ULightComponent* Light);
	void EndAimTransaction();
	void CancelAim();
	void SetHit(const ULightComponent* Light, const FFastLightSurfaceHit& Hit);
	const FFastLightSurfaceHit* FindHit(const ULightComponent* Light) const;
};

namespace FastLightAim
{
	ULightComponent* FindSelectedLight();
	bool TraceScene(UWorld* World, const FVector& Start, const FVector& End, const AActor* IgnoreActor, FHitResult& OutHit);
	void AimLightAt(ULightComponent* Light, const FVector& TargetPoint);
	void AdjustDistance(ULightComponent* Light, float WheelDelta, bool bOpenTransaction);
	FFastLightSurfaceHit MakeHit(const ULightComponent* Light, const FHitResult& Hit);
	float GetTraceDistance(const ULightComponent* Light);
}
