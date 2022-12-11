// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API AShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void CheckGameCondition(AActor* DeadActor);

	UFUNCTION()
	FText GetEnemiesLeft();

protected:
	virtual void BeginPlay() override;

private:
	TArray<AActor*> AliveEnemyActors;

	TArray<AActor*> GetAliveEnemies();
};
