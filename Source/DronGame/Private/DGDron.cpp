#include "DGDron.h"


#include "DGAttributeComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"


ADGDron::ADGDron()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionResponseToAllChannels(ECR_Block);
	SphereComp->SetCollisionProfileName("OverlapAllBlock");
	SphereComp->SetSphereRadius(75.0f);
	RootComponent = SphereComp;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetupAttachment(RootComponent);

	AttributeComp = CreateDefaultSubobject<UDGAttributeComponent>(TEXT("AttributeComp"));
	
	ForwardSpeed = 500.0f;
	UpSpeed = 150.0f;
}


void ADGDron::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ADGDron::OnHealthChanged);
	AttributeComp->OnAmmoChanged.AddDynamic(this, &ADGDron::OnAmmoChanged);
}


void ADGDron::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADGDron::MoveForward);
	PlayerInputComponent->BindAxis("MoveTurn", this, &ADGDron::MoveTurn);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADGDron::MoveUp);

	PlayerInputComponent->BindAxis("LookUp", this, &ADGDron::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ADGDron::LookTurn);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADGDron::Fire);
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


void ADGDron::Fire()
{
	if (ProjectileClass)
	{
		FVector StartLine = CameraComp->GetComponentLocation();
		FRotator CameraRotator = CameraComp->GetComponentRotation();

		FVector EndLine = StartLine + (CameraRotator.Vector() * 1000);

		FCollisionObjectQueryParams CollisionParams;
		CollisionParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		CollisionParams.AddObjectTypesToQuery(ECC_WorldStatic);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FHitResult HitResult;

		GetWorld()->LineTraceSingleByObjectType(HitResult, StartLine, EndLine, CollisionParams, Params);
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;

		FTransform SpawnTransform;
		
		if (HitResult.GetActor())
		{
			FVector Hit = HitResult.ImpactPoint - StartLine;
			Hit.Normalize();
			SpawnTransform = FTransform(Hit.Rotation(), StartLine);
		}
		else
		{
			FVector Hit = EndLine - StartLine;
			Hit.Normalize();
			SpawnTransform = FTransform(Hit.Rotation(), StartLine);
		}
		
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
	}
}


void ADGDron::OnHealthChanged(AActor* InstigatorActor, UDGAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);

		SetLifeSpan(5.0f);
	}
}


void ADGDron::OnAmmoChanged(AActor* InstigatorActor, UDGAttributeComponent* OwningComp, float NewAmmo, float Delta)
{
	if (NewAmmo <= 0.0f && Delta < 0.0f)
	{
		// TODO: Animation, Change Widget via C++ or something else
	}
}


void ADGDron::BeginPlay()
{
	Super::BeginPlay();

	if (HealthWidgetClass && HealthWidget == nullptr)
	{
		HealthWidget = CreateWidget<UUserWidget>(GetWorld(), HealthWidgetClass);
		if (HealthWidget)
		{
			HealthWidget->AddToViewport();
		}
	}
}
