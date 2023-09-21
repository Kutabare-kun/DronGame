// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGPowerUp.h"
#include "DGPowerUp_AmmoUp.generated.h"

/**
 * 
 */
UCLASS()
class DRONGAME_API ADGPowerUp_AmmoUp : public ADGPowerUp
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
	float AmmoUp;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	
	ADGPowerUp_AmmoUp();
	
};
