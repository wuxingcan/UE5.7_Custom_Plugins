// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FastLight : ModuleRules
{
	public FastLight(ReadOnlyTargetRules Target) : base(Target)
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
				"InputCore",
				"Slate",
				"SlateCore",
				"AppFramework",
				"UnrealEd",
				"EditorFramework",
				"LevelEditor",
				"Projects"
			}
		);
	}
}
