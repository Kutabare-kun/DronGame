// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DRONGAME_API ADGGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	
	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);
	
public:

	UFUNCTION()
	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);
	
};
