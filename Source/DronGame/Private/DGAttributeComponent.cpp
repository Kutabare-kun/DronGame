// Fill out your copyright notice in the Description page of Project Settings.


#include "DGAttributeComponent.h"

#include "DGGameMode.h"


UDGAttributeComponent::UDGAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;

	AmmoMax = 64;
	Ammo = AmmoMax;
}


UDGAttributeComponent* UDGAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UDGAttributeComponent>(FromActor->GetComponentByClass(UDGAttributeComponent::StaticClass()));
	}

	return nullptr;
}


bool UDGAttributeComponent::IsActorAlive(AActor* Actor)
{
	UDGAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}


bool UDGAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}


bool UDGAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}


float UDGAttributeComponent::GetHealth() const
{
	return Health;
}


float UDGAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}


bool UDGAttributeComponent::HasAmmo() const
{
	return Ammo > 0.0f;
}


bool UDGAttributeComponent::IsFullAmmo() const
{
	return Ammo == AmmoMax;
}


float UDGAttributeComponent::GetAmmo() const
{
	return Ammo;
}


float UDGAttributeComponent::GetAmmoMax() const
{
	return AmmoMax;
}


bool UDGAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = NewHealth - OldHealth;

	if (ActualDelta != 0.0f)
	{
		Health = NewHealth;
		
		OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);

		if (ActualDelta < 0.0f && Health == 0.0f)
		{
			ADGGameMode* GM = GetWorld()->GetAuthGameMode<ADGGameMode>();
			if (GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor);
			}
		}
	}

	return ActualDelta != 0.0f;
}


bool UDGAttributeComponent::ApplyAmmoChange(AActor* InstigatorActor, float Delta)
{
	if (Delta == 0.0f)
	{
		return false;
	}

	float OldAmmo = Ammo;
	float NewAmmo = FMath::Clamp(Ammo + Delta, 0.0f, AmmoMax);

	float ActualDelta = NewAmmo - OldAmmo;

	if (ActualDelta)
	{
		Ammo = NewAmmo;

		OnAmmoChanged.Broadcast(InstigatorActor, this, NewAmmo, Delta);
	}

	return ActualDelta != 0.0f;
}
