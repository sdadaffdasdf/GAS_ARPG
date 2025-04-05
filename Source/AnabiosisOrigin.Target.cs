// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AnabiosisOriginTarget : TargetRules
{
    public AnabiosisOriginTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        
        ExtraModuleNames.AddRange(new string[] { "AnabiosisOrigin" });
    }
}