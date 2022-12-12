// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetFocus.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API UBTService_SetFocus : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_SetFocus();

private:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
