// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "CommonCheckerTypes.generated.h"

UENUM(meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class EBitActorCategory : int32
{
	SkeletalMesh	= 1 << 0 UMETA(DisplayName="Skeletal Mesh"),
	StaticMesh		= 1 << 1 UMETA(DisplayName="Static Mesh"),
	Particle		= 1 << 2 UMETA(DisplayName="Particle"),
	Audio			= 1 << 3 UMETA(DisplayName="Audio"),
	Rendering		= 1 << 4 UMETA(DisplayName="Rendering"),
	Volume			= 1 << 5 UMETA(DisplayName="Volume"),
	Geometry		= 1 << 6 UMETA(DisplayName="Geometry"),
	Gameplay		= 1 << 7 UMETA(DisplayName="Gameplay"),
	Other			= 1 << 8 UMETA(DisplayName="Other"),
};

UENUM()
enum class ETextureSize
{
	SizeOver8192	UMETA(DisplayName="Size over 8K"),
	Size4096		UMETA(DisplayName="Size 4K"),
	Size2048		UMETA(DisplayName="Size 2K"),
	Size1024		UMETA(DisplayName="Size 1K"),
	Size512			UMETA(DisplayName="Size 512x512"),
	Size256			UMETA(DisplayName="Size 256x256"),
	Size128			UMETA(DisplayName="Size 128x128"),
	Size64			UMETA(DisplayName="Size 64x64"),
	SizeBelow64		UMETA(DisplayName="Size below 64x64"),
	MAX				UMETA(Hidden)
};

enum class EScore
{
	A,
	B,
	C,
	D,
	F,
	MAX
};

USTRUCT()
struct FIntScoreSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Score Settings", meta=(EditCondition="bAllowHealthCheck"))
	int32 A = 0;

	UPROPERTY(EditAnywhere, Category="Score Settings", meta=(EditCondition="bAllowHealthCheck"))
	int32 B = 0;

	UPROPERTY(EditAnywhere, Category="Score Settings", meta=(EditCondition="bAllowHealthCheck"))
	int32 C = 0;

	UPROPERTY(EditAnywhere, Category="Score Settings", meta=(EditCondition="bAllowHealthCheck"))
	int32 D = 0;

	UPROPERTY(EditAnywhere, Category="Score Settings", meta=(EditCondition="bAllowHealthCheck"))
	float ScoreWeight = 1.f;

	UPROPERTY(EditAnywhere, Category="Score Settings")
	bool bAllowHealthCheck = true;

	int32 operator[] (EScore Score) const
	{
		switch(Score)
		{
		case EScore::A: return A;
		case EScore::B: return B;
		case EScore::C: return B;
		case EScore::D: return B;
		default:
			ensure(false);
			return 0;
		}
	}
};

USTRUCT()
struct FFloatScoreSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Score Settings", meta=(EditCondition="bAllowHealthCheck"))
	float A = 0.f;

	UPROPERTY(EditAnywhere, Category="Score Settings", meta=(EditCondition="bAllowHealthCheck"))
	float B = 0.f;

	UPROPERTY(EditAnywhere, Category="Score Settings", meta=(EditCondition="bAllowHealthCheck"))
	float C = 0.f;

	UPROPERTY(EditAnywhere, Category="Score Settings", meta=(EditCondition="bAllowHealthCheck"))
	float D = 0.f;

	UPROPERTY(EditAnywhere, Category="Score Settings", meta=(EditCondition="bAllowHealthCheck"))
	float ScoreWeight = 1.f;

	UPROPERTY(EditAnywhere, Category="Enabled")
	bool bAllowHealthCheck = true;

	float operator[] (EScore Score) const
	{
		switch(Score)
		{
		case EScore::A: return A;
		case EScore::B: return B;
		case EScore::C: return B;
		case EScore::D: return B;
		default:
			ensure(false);
			return 0.f;
		}
	}
};
