#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DGDron.generated.h"


class USphereComponent;
class UCameraComponent;


UCLASS()
class DRONGAME_API ADGDron : public APawn
{
	GENERATED_BODY()

public:

	ADGDron();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Coponents")
	USphereComponent* SphereComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

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
	
	virtual void BeginPlay() override;

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
