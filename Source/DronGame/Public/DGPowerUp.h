// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGPowerUp.generated.h"

class USphereComponent;

UCLASS(ABSTRACT)
class DRONGAME_API ADGPowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADGPowerUp();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

};
