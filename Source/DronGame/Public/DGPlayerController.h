// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DGPlayerController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChanged, APawn*, NewPawn);


UCLASS()
class DRONGAME_API ADGPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnPawnChanged OnPawnChanged;

	virtual void SetPawn(APawn* InPawn) override;
	
};
