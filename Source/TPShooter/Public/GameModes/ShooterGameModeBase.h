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

public: AShooterGameModeBase();

public:
	void CheckGameCondition(AActor* DeadActor);

	UFUNCTION()
	FText GetEnemiesLeft();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Game Over")
	TSubclassOf<class UGameOverUserWidget> GameOverWidgetClass;
	UGameOverUserWidget* GameOverWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Game Over")
	float RestartLevelTime;

	TArray<AActor*> AliveEnemyActors;

	TArray<AActor*> GetAliveEnemies();

	void GameOver(bool bIsWin);

	void RemoveHUD();
	void CreateGameOverWidget(bool bIsWin);
	void RestartLevel();
};
