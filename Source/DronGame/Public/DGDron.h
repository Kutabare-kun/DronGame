#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DGDron.generated.h"


class UDGAttributeComponent;
class USphereComponent;
class UCameraComponent;


UCLASS()
class DRONGAME_API ADGDron : public APawn
{
	GENERATED_BODY()

public:

	ADGDron();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthWidgetClass;
	
	UPROPERTY()
	UUserWidget* HealthWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Coponents")
	USphereComponent* SphereComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
	UDGAttributeComponent* AttributeComp;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float ForwardSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float UpSpeed;

	void MoveForward(float Value);

	void MoveTurn(float Value);

	void MoveUp(float Value);

	void LookUp(float Value);

	void LookTurn(float Value);

	void Fire();
	
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UDGAttributeComponent* OwningComp, float NewHealth, float Delta);

	UFUNCTION()
	void OnAmmoChanged(AActor* InstigatorActor, UDGAttributeComponent* OwningComp, float NewAmmo, float Delta);

public:

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
