// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ShooterCharacter.h"
#include "Interfaces/DeathInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API AEnemyCharacter : public AShooterCharacter, public IDeathInterface
{
	GENERATED_BODY()

public:

	void Fire();
	void StopFiring();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Death();
	virtual void Death_Implementation();
};
