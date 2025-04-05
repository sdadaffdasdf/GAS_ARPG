// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AnabiosisOrigin : ModuleRules
{
	public AnabiosisOrigin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] {
			"AnabiosisOrigin/Public"
		});

		PrivateIncludePaths.AddRange(new string[] {
			"AnabiosisOrigin/Private"
		});

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay",
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}