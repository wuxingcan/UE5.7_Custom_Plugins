// Copyright Epic Games, Inc. All Rights Reserved.

#include "FastLightShared.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/LightComponent.h"
#include "Components/LocalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Editor.h"
#include "Engine/Selection.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "FastLight"

FFastLightAimState& FFastLightAimState::Get()
{
	static FFastLightAimState State;
	return State;
}

void FFastLightAimState::BeginAimTransaction(ULightComponent* Light)
{
	if(bTransactionOpen || !GEditor || !Light)
	{
		return;
	}

	GEditor->BeginTransaction(LOCTEXT("AimLight", "瞄准灯光"));
	Light->Modify();
	if(AActor* Owner = Light->GetOwner())
	{
		Owner->Modify();
	}
	bTransactionOpen = true;
}

void FFastLightAimState::EndAimTransaction()
{
	if(!bTransactionOpen || !GEditor)
	{
		bTransactionOpen = false;
		return;
	}

	GEditor->EndTransaction();
	bTransactionOpen = false;
}

void FFastLightAimState::CancelAim()
{
	EndAimTransaction();
	bDragging = false;
	DraggingLight.Reset();
	DragHit = FFastLightSurfaceHit();
}

void FFastLightAimState::SetHit(const ULightComponent* Light, const FFastLightSurfaceHit& Hit)
{
	if(Light)
	{
		Hits.Add(const_cast<ULightComponent*>(Light), Hit);
	}
}

const FFastLightSurfaceHit* FFastLightAimState::FindHit(const ULightComponent* Light) const
{
	return Light ? Hits.Find(const_cast<ULightComponent*>(Light)) : nullptr;
}

namespace FastLightAim
{
	ULightComponent* FindSelectedLight()
	{
		if(!GEditor)
		{
			return nullptr;
		}

		auto Accept = [](ULightComponent* Light, ULightComponent*& OutLight, int32& Count)
		{
			if(!Light || Light->IsA<USkyLightComponent>())
			{
				return;
			}
			OutLight = Light;
			++Count;
		};

		ULightComponent* Found = nullptr;
		int32 Count = 0;
		if(USelection* SelectedComponents = GEditor->GetSelectedComponents())
		{
			for(FSelectionIterator It(*SelectedComponents); It; ++It)
			{
				Accept(Cast<ULightComponent>(*It), Found, Count);
			}
		}
		if(Count == 1)
		{
			return Found;
		}

		Found = nullptr;
		Count = 0;
		if(USelection* SelectedActors = GEditor->GetSelectedActors())
		{
			for(FSelectionIterator It(*SelectedActors); It; ++It)
			{
				AActor* Actor = Cast<AActor>(*It);
				if(!Actor)
				{
					continue;
				}
				TArray<ULightComponent*> Lights;
				Actor->GetComponents<ULightComponent>(Lights);
				for(ULightComponent* Light : Lights)
				{
					Accept(Light, Found, Count);
				}
			}
		}
		return Count == 1 ? Found : nullptr;
	}

	bool TraceScene(UWorld* World, const FVector& Start, const FVector& End, const AActor* IgnoreActor, FHitResult& OutHit)
	{
		if(!World)
		{
			return false;
		}

		FCollisionQueryParams Params(SCENE_QUERY_STAT(FastLightAim), true, IgnoreActor);
		Params.bTraceComplex = true;

		auto Pick = [&OutHit](const TArray<FHitResult>& Hits)
		{
			for(const FHitResult& Hit : Hits)
			{
				if(Hit.bBlockingHit && Hit.GetComponent() && !Hit.GetComponent()->IsA<ULightComponent>())
				{
					OutHit = Hit;
					return true;
				}
			}
			return false;
		};

		TArray<FHitResult> Hits;
		World->LineTraceMultiByChannel(Hits, Start, End, ECC_Visibility, Params);
		if(Pick(Hits))
		{
			return true;
		}

		FCollisionObjectQueryParams Objects;
		Objects.AddObjectTypesToQuery(ECC_WorldStatic);
		Objects.AddObjectTypesToQuery(ECC_WorldDynamic);
		Objects.AddObjectTypesToQuery(ECC_Pawn);
		Objects.AddObjectTypesToQuery(ECC_PhysicsBody);
		Objects.AddObjectTypesToQuery(ECC_Vehicle);
		Hits.Reset();
		World->LineTraceMultiByObjectType(Hits, Start, End, Objects, Params);
		return Pick(Hits);
	}

	void AimLightAt(ULightComponent* Light, const FVector& TargetPoint)
	{
		if(!Light)
		{
			return;
		}

		const FVector Direction = TargetPoint - Light->GetComponentLocation();
		if(Direction.IsNearlyZero())
		{
			return;
		}

		FRotator NewRotation = Direction.GetSafeNormal().Rotation();
		NewRotation.Roll = Light->GetComponentRotation().Roll;
		Light->SetWorldRotation(NewRotation);
	}

	void AdjustDistance(ULightComponent* Light, float WheelDelta, bool bOpenTransaction)
	{
		if(!Light || FMath::IsNearlyZero(WheelDelta))
		{
			return;
		}

		FFastLightAimState& State = FFastLightAimState::Get();
		FVector Target = Light->GetComponentLocation() + Light->GetDirection() * 400.f;
		if(State.bDragging && State.DraggingLight.Get() == Light)
		{
			Target = State.DragTarget;
		}
		else if(const FFastLightSurfaceHit* Hit = State.FindHit(Light))
		{
			if(Hit->bOnSurface)
			{
				Target = Hit->Location;
			}
		}

		const FVector ToTarget = Target - Light->GetComponentLocation();
		const float Distance = ToTarget.Size();
		const FVector Direction = ToTarget.GetSafeNormal();
		if(Direction.IsNearlyZero())
		{
			return;
		}

		const float Step = FMath::Max(Distance * 0.08f, 15.f) * WheelDelta;
		const float NewDistance = FMath::Clamp(Distance - Step, 20.f, 200000.f);
		const FVector NewLocation = Target - Direction * NewDistance;

		if(bOpenTransaction)
		{
			State.BeginAimTransaction(Light);
		}
		Light->SetWorldLocation(NewLocation);
		AimLightAt(Light, Target);
		if(bOpenTransaction)
		{
			State.EndAimTransaction();
		}
		if(GEditor)
		{
			GEditor->RedrawLevelEditingViewports();
		}
	}

	FFastLightSurfaceHit MakeHit(const ULightComponent* Light, const FHitResult& Hit)
	{
		FFastLightSurfaceHit Result;
		Result.bOnSurface = Hit.bBlockingHit;
		Result.Location = Hit.ImpactPoint;
		Result.Normal = Hit.ImpactNormal.GetSafeNormal();
		Result.Actor = Hit.GetActor();
		Result.Distance = Light ? FVector::Distance(Light->GetComponentLocation(), Hit.ImpactPoint) : Hit.Distance;
		if(AActor* Actor = Hit.GetActor())
		{
			Result.Label = Actor->GetActorLabel();
		}
		if(Result.Normal.IsNearlyZero())
		{
			Result.Normal = FVector::UpVector;
		}
		return Result;
	}

	float GetTraceDistance(const ULightComponent* Light)
	{
		if(const ULocalLightComponent* LocalLight = Cast<ULocalLightComponent>(Light))
		{
			return FMath::Clamp(LocalLight->AttenuationRadius * 4.f, 1500.f, 100000.f);
		}
		if(Light && Light->IsA<UDirectionalLightComponent>())
		{
			return 100000.f;
		}
		return 8000.f;
	}
}

#undef LOCTEXT_NAMESPACE
