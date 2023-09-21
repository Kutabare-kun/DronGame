// Fill out your copyright notice in the Description page of Project Settings.


#include "DGProjectile.h"

#include "DGAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ADGProjectile::ADGProjectile()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("OverlapAllDynamic");
	SphereComp->SetSphereRadius(64.0f);
	SphereComp->SetupAttachment(RootComponent);
	
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->InitialSpeed = 2500;

	InitialLifeSpan = 5.0f;
	DamageAmount = 5.0f;
}


void ADGProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor != GetInstigator())
	{
		UDGAttributeComponent* AttributeComp = UDGAttributeComponent::GetAttributes(OtherActor);
		if (AttributeComp)
		{
			if (AttributeComp->IsAlive() && AttributeComp->ApplyHealthChange(GetInstigator(), -DamageAmount))
			{
				Destroy();
			}
		}
	}
}
