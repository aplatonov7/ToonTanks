// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly, Category = "Tower Combat")
	float FireRange = 800;

	UPROPERTY(EditDefaultsOnly, Category = "Tower Combat")
	float FireRate = 2;
	
	FTimerHandle FireRateTimerHandle;

	bool IsTankInFireRange() const;
	void CheckFireCondition();
};
