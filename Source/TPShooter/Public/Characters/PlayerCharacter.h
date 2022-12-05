// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ShooterCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API APlayerCharacter : public AShooterCharacter
{
	GENERATED_BODY()
	
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Movement inputs
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
};
