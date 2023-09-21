// Fill out your copyright notice in the Description page of Project Settings.


#include "DGBTTaskNode_AttackRange.h"

#include "AIController.h"
#include "DGAttributeComponent.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"


UDGBTTaskNode_AttackRange::UDGBTTaskNode_AttackRange()
{
	MaxBulletSpread = 2.5f;
}


EBTNodeResult::Type UDGBTTaskNode_AttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();

	if (ensure(MyController))
	{
		APawn* MyPawn = MyController->GetPawn();
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector From = MyPawn->GetActorLocation();

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		if (!UDGAttributeComponent::IsActorAlive(TargetActor))
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = TargetActor->GetActorLocation() - From;
		FRotator DirectionRotation = Direction.Rotation();

		DrawDebugLine(GetWorld(), From, Direction * 100.0f, FColor::Red, true, 5);
		
		DirectionRotation.Pitch += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);
		DirectionRotation.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = MyPawn;

		AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, From, DirectionRotation, Params);

		return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
