// Fill out your copyright notice in the Description page of Project Settings.


#include "DGPlayerController.h"

void ADGPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnPawnChanged.Broadcast(InPawn);
}
