#include "DGPowerUp.h"

#include "Components/SphereComponent.h"

ADGPowerUp::ADGPowerUp()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetSphereRadius(64.0f);
	SphereComp->SetupAttachment(RootComponent);
	RootComponent = SphereComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetupAttachment(RootComponent);
}
