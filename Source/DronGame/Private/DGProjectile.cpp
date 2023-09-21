// Fill out your copyright notice in the Description page of Project Settings.


#include "DGProjectile.h"

// Sets default values
ADGProjectile::ADGProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADGProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADGProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

