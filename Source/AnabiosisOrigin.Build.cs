// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AnabiosisOrigin : ModuleRules
{
    public AnabiosisOrigin(ReadOnlyTargetRules Target) : base(Target)
    {
        bEnforceIWYU = true;
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

        bUseUnity = false;  // 禁用Unity构建以更精确地控制哪些文件被编译
    }
}