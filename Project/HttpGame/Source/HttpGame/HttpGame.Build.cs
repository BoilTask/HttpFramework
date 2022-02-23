// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HttpGame : ModuleRules
{
	public HttpGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core"
			, "CoreUObject"
			, "Engine"
			, "InputCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"Http"
			, "Json"
		});

		PrivateIncludePaths.AddRange(new string[] {
			"HttpGame"
			, "HttpGame/Def"
			, "HttpGame/Net"
			, "HttpGame/Net/Request"
			, "HttpGame/Net/Response"
		});
	}
}
