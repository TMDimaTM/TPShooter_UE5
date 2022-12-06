// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ShooterCharacter.h"
#include "Interfaces/DeathInterface.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API APlayerCharacter : public AShooterCharacter, public IDeathInterface
{
	GENERATED_BODY()
	
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Death();
	virtual void Death_Implementation();

private:
	// Movement inputs
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
};
