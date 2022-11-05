// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(
		TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(
		TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;

	bool Hit = PlayerControllerRef->GetHitResultUnderCursor(
		ECollisionChannel::ECC_Visibility,
		false,
		HitResult);

	if (Hit)
	{
		RotateTurret(HitResult.ImpactPoint);
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed,this, &ATank::Fire);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(const float Value)
{
	const FVector Direction = FVector(Value, 0, 0);
	const double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(Direction * Speed * DeltaTime, true);
}

void ATank::Turn(const float Value)
{
	const FRotator Rotator = FRotator(0, Value, 0);
	const double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(Rotator * DeltaTime * TurnSpeed, true);
}
