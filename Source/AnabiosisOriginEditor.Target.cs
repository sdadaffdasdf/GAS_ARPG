// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AnabiosisOriginEditorTarget : TargetRules
{
    public AnabiosisOriginEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        
        // 设置bOverrideBuildEnvironment=true以解决属性修改冲突问题
        bOverrideBuildEnvironment = true;
        
        ExtraModuleNames.AddRange(new string[] { "AnabiosisOrigin" });
    }
}