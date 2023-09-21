#include "DGDron.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"


ADGDron::ADGDron()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionResponseToAllChannels(ECR_Block);
	SphereComp->SetCollisionProfileName("OverlapAllBlock")
	SphereComp->SetSphereRadius(75.0f);
	RootComponent = SphereComp;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetupAttachment(RootComponent);
	
	ForwardSpeed = 250.0f;
	UpSpeed = 75.0f;
}


void ADGDron::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADGDron::MoveForward);
	PlayerInputComponent->BindAxis("MoveTurn", this, &ADGDron::MoveTurn);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADGDron::MoveUp);

	PlayerInputComponent->BindAxis("LookUp", this, &ADGDron::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ADGDron::LookTurn);
}


void ADGDron::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		FVector ForwardVector = CameraComp->GetForwardVector();
		
		SetActorLocation(GetActorLocation() + (ForwardVector * ForwardSpeed * Value * GetWorld()->GetDeltaSeconds()), true);
	}
}


void ADGDron::MoveTurn(float Value)
{
	if (Value != 0.0f)
	{
		FRotator ControlRot = CameraComp->GetComponentRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;

		FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

		SetActorLocation(GetActorLocation() + (RightVector * ForwardSpeed * Value * GetWorld()->GetDeltaSeconds()), true);
	}
}


void ADGDron::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		FVector UpVector = GetActorUpVector();
		
		SetActorLocation(GetActorLocation() + (UpVector * UpSpeed * Value * GetWorld()->GetDeltaSeconds()), true);
	}
}


void ADGDron::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}


void ADGDron::LookTurn(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}


void ADGDron::BeginPlay()
{
	Super::BeginPlay();
	
}


void ADGDron::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	
}
