// Fill out your copyright notice in the Description page of Project Settings.


#include "DGPowerUp_AmmoUp.h"

#include "DGAttributeComponent.h"


ADGPowerUp_AmmoUp::ADGPowerUp_AmmoUp()
{
	AmmoUp = 24.0f;
}


void ADGPowerUp_AmmoUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UDGAttributeComponent* AttributeComp = UDGAttributeComponent::GetAttributes(OtherActor);
	if (AttributeComp && AttributeComp->ApplyAmmoChange(this, AmmoUp))
	{
		Destroy();
	}
}

