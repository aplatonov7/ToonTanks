// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Tank Components")
	class USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Tank Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Tank Movement")
	float Speed = 300;

	UPROPERTY(EditAnywhere, Category = "Tank Movement")
	float TurnSpeed = 300;

	void Move(float Value);
	void Turn(float Value);
};
