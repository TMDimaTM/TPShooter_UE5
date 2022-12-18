// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTasks/BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp != nullptr)
	{
		BlackboardComp->ClearValue(GetSelectedBlackboardKey());

		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}