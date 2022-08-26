// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AwkayCase : ModuleRules
{
	public AwkayCase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Niagara", "AnimGraphRuntime" });

		PublicDependencyModuleNames.AddRange(new string[] { "GameplayTasks", "AIModule", "NavigationSystem" });
	}
}
