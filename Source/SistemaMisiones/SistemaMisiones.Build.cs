// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SistemaMisiones : ModuleRules
{
	public SistemaMisiones(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"SlateCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"SistemaMisiones",
			"SistemaMisiones/Variant_Platforming",
			"SistemaMisiones/Variant_Platforming/Animation",
			"SistemaMisiones/Variant_Combat",
			"SistemaMisiones/Variant_Combat/AI",
			"SistemaMisiones/Variant_Combat/Animation",
			"SistemaMisiones/Variant_Combat/Gameplay",
			"SistemaMisiones/Variant_Combat/Interfaces",
			"SistemaMisiones/Variant_Combat/UI",
			"SistemaMisiones/Variant_SideScrolling",
			"SistemaMisiones/Variant_SideScrolling/AI",
			"SistemaMisiones/Variant_SideScrolling/Gameplay",
			"SistemaMisiones/Variant_SideScrolling/Interfaces",
			"SistemaMisiones/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
