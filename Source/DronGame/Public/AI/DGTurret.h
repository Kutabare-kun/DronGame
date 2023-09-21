#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DGTurret.generated.h"

class UDGWorldUserWidget;
class UDGAttributeComponent;
class UPawnSensingComponent;

UCLASS()
class DRONGAME_API ADGTurret : public APawn
{
	GENERATED_BODY()

public:

	ADGTurret();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UDGWorldUserWidget> SpottedWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UDGAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TargetActorKey;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;
	
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetTargetActor(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category = "AI")
	AActor* GetTargetActor() const;
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UDGAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	virtual void PostInitializeComponents() override;
	
};
