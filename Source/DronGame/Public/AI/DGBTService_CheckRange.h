// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DGBTService_CheckRange.generated.h"

/**
 * 
 */
UCLASS()
class DRONGAME_API UDGBTService_CheckRange : public UBTService
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;
	
	UPROPERTY(EditAnywhere, Category = "Range")
	float TurretRange;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
