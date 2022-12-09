// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API UBTService_Shoot : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_Shoot();

private:
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float StartFireDelay;

	FTimerHandle FireDelayTimerHandle;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void FireAfterDelay(AEnemyCharacter* SelfCharacter);
};
