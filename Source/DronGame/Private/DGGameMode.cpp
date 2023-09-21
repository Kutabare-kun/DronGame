// Fill out your copyright notice in the Description page of Project Settings.


#include "DGGameMode.h"

#include "DGDron.h"

void ADGGameMode::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();

		RestartPlayer(Controller);
	}
}


void ADGGameMode::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	ADGDron* Player = Cast<ADGDron>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());

		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}

	// TODO: Player kill turret do some logic
}
