// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UNiagaraSystem;

/**
 * Reads / writes Niagara system snapshots.
 *
 * Snapshot (Version 2) semantics:
 *  - The file is self contained: it stores the system settings, user parameters, every emitter with its
 *    renderers / event handlers / simulation stages, the shared script usage ids, and the full graph
 *    text (T3D) plus script variables for every graph.
 *  - Everything the exporter writes is persisted as plain JSON so the file can be inspected and diffed.
 *
 * Restore (Version 2) semantics:
 *  - A brand new Niagara System asset is created from the snapshot alone; the original asset is never
 *    loaded, so importing still works after the source system has been deleted.
 *  - Emitters are created inline (not as separate assets) and their graphs are rebuilt from the stored
 *    graph text, then the system is compiled and saved.
 *  - External dependencies (materials, meshes, data interfaces, ...) are loaded by path. If they are
 *    missing the system is still rebuilt, but the affected properties stay empty and are logged.
 *
 * Legacy (Version 1) snapshots only record node properties and pins, so they cannot rebuild renderers
 * or materials on their own. They keep the old behaviour of duplicating the original system asset and
 * therefore require that asset to still exist.
 */
class FCommonEFXExporter
{
public:
	/** Lets the user pick a Niagara system in the Content Browser and export it. */
	static bool ExportSelectedSystemToFile(FString& OutFile, FString& OutError);

	/** Exports a specific system. Prompts for the destination JSON file. */
	static bool ExportSystemToFileWithDialog(UNiagaraSystem* System, FString& OutFile, FString& OutError);

	/** Exports a specific system to a specific JSON file using the current (v2) format. */
	static bool ExportSystemToFile(UNiagaraSystem* System, const FString& FileName, FString& OutError);

	/** Prompts for a snapshot file and imports it into a new system asset. */
	static bool ImportSystemFromFileWithDialog(FString& OutNewAssetPath, FString& OutError, const FString& DestinationPath = FString());

	/**
	 * Imports a snapshot from a specific file. Version 2 snapshots are rebuilt offline from the JSON;
	 * version 1 snapshots duplicate the original system asset. Returns the newly created system.
	 */
	static UNiagaraSystem* ImportSystemFromFile(const FString& FileName, FString& OutError, const FString& DestinationPath = FString());

	/** Logs what a system really contains (handles, graphs, renderers, compile state). Used to verify rebuilds. */
	static void LogSystemContents(UNiagaraSystem* System, const FString& Label);

	/**
	 * Exports a system, rebuilds it from that snapshot and exports the rebuilt system again so the two JSON
	 * files can be diffed. Used by the CommonEFX.RoundTrip console command.
	 */
	static bool RunRoundTripCheck(const FString& AssetPath, const FString& OutputDirectory, FString& OutSourceFile, FString& OutRebuiltFile, FString& OutError);
};
