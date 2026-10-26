// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BatchScreenShot : ModuleRules
{
	public BatchScreenShot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"InputCore",
				"UnrealEd",
				"EditorFramework",
				"LevelEditor",
				"ToolMenus",
				"ContentBrowser",
				"ContentBrowserData",
				"AssetRegistry",
				"Projects",
				"LevelSequence",
				"LevelSequenceEditor",
				"MovieScene",
				"MovieSceneTracks",
				"Sequencer",
				"EditorSubsystem"
			}
		);
	}
}
