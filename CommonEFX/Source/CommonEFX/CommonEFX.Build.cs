// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CommonEFX : ModuleRules
{
	public CommonEFX(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
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
				"ToolMenus",
				"ContentBrowser",
				"ContentBrowserData",
				"AssetRegistry",
				"AssetTools",
				"DesktopPlatform",
				"Projects",
				"Json",
				"JsonUtilities",
				"Niagara",
				"NiagaraCore",
				"NiagaraEditor",
			}
			);
	}
}
