// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;

public:
	void SetLastPlayerLocation(AActor* PlayerActor);

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAIPerceptionComponent* AIPerceptionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Trees")
	UBehaviorTree* BehaviorTree;

	UPROPERTY()
	class AEnemyCharacter* SelfCharacter;

	UFUNCTION()
	void PerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
};