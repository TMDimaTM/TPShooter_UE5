// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTasks/BTTask_FindPatrolLocation.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"



UBTTask_FindPatrolLocation::UBTTask_FindPatrolLocation()
{
	NodeName = TEXT("Find Patrol Location");

	PatrolDistance = 500.0f;
}

EBTNodeResult::Type UBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* SelfPawn = OwnerComp.GetAIOwner()->GetPawn();

	FVector PatrolLocation = (-SelfPawn->GetActorForwardVector()) * PatrolDistance + SelfPawn->GetActorLocation();
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PatrolLocation);

	return EBTNodeResult::Succeeded;
}
