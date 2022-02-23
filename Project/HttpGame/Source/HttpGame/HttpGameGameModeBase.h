// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HttpGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HTTPGAME_API AHttpGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void InitGameState() override;
	
};
