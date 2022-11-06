// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsTankInFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(
		UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true);
}

bool ATower::IsTankInFireRange() const
{
	if (Tank == nullptr || !Tank->bAlive)
	{
		return false;
	}

	const float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

	return Distance <= FireRange;
}

void ATower::CheckFireCondition()
{
	if (IsTankInFireRange())
	{
		Fire();
	}
}


