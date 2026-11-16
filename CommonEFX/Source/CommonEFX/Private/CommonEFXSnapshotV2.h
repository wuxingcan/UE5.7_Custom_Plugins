// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"

class UNiagaraSystem;

/**
 * Version 2 snapshots are self contained: they store enough data to rebuild a Niagara System without
 * loading the original asset.
 */
class FCommonEFXSnapshotV2
{
public:
	static constexpr int32 Version = 2;

	/** Writes the system, its emitters, renderers, event handlers, simulation stages and graphs to JSON. */
	static bool Export(UNiagaraSystem* System, const FString& FileName, FString& OutError);

	/** Rebuilds a brand new system asset from a v2 snapshot. The original asset is never loaded. */
	static UNiagaraSystem* Import(const TSharedPtr<FJsonObject>& RootObject, FString& OutError, const FString& DestinationPath = FString());
};
