// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class DRONGAME_API ADGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADGProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
