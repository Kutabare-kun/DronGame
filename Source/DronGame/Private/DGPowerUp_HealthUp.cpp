#include "DGPowerUp_HealthUp.h"

#include "DGAttributeComponent.h"


ADGPowerUp_HealthUp::ADGPowerUp_HealthUp()
{
	HealthUp = 50.0f;
}


void ADGPowerUp_HealthUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	UDGAttributeComponent* AttributeComp = UDGAttributeComponent::GetAttributes(OtherActor);
	if (AttributeComp)
	{
		AttributeComp->ApplyHealthChange(this, HealthUp);
	}
}
