// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTasks/BTTask_FindPatrolLocation.h"
#include "NavigationSystem.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"



UBTTask_FindPatrolLocation::UBTTask_FindPatrolLocation()
{
	NodeName = TEXT("Find Patrol Location");

	Radius = 2500.0f;
}

EBTNodeResult::Type UBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* SelfPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (SelfPawn != nullptr)
	{
		FVector SelfPawnLocation = SelfPawn->GetActorLocation();
		FVector PatrolLocation = UNavigationSystemV1::GetRandomReachablePointInRadius(this, SelfPawnLocation, Radius);

		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if (BlackboardComp != nullptr)
		{
			BlackboardComp->SetValueAsVector(GetSelectedBlackboardKey(), PatrolLocation);

			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
