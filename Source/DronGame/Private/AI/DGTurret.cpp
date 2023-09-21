#include "AI\DGTurret.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "DGAttributeComponent.h"
#include "DGWorldUserWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Perception/PawnSensingComponent.h"


ADGTurret::ADGTurret()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UDGAttributeComponent>(TEXT("AttributeComp"));
	
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	TimeToHitParamName = "TimeToHit";
	TargetActorKey = "TargetActor";
}


void ADGTurret::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ADGTurret::OnHealthChanged);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ADGTurret::OnPawnSeen);
}


void ADGTurret::OnHealthChanged(AActor* InstigatorActor, UDGAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if (Delta < 0.0f)
	{
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		MeshComp->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
		
		if (NewHealth <= 0.0f)
		{
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			SetLifeSpan(2.5f);
		}
	}
}


void ADGTurret::OnPawnSeen(APawn* SeenPawn)
{
	if (GetTargetActor() != SeenPawn)
	{
		SetTargetActor(SeenPawn);

		UDGWorldUserWidget* NewWidget = CreateWidget<UDGWorldUserWidget>(GetWorld(), SpottedWidgetClass);
		if (NewWidget)
		{
			NewWidget->AttachedActor = this;
		
			NewWidget->AddToViewport(10);
		}
	}
}


void ADGTurret::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject(TargetActorKey, NewTarget);
	}
}


AActor* ADGTurret::GetTargetActor() const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorKey));
	}

	return nullptr;
}
