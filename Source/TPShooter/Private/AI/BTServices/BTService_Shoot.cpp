// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTServices/BTService_Shoot.h"
#include "AIController.h"
#include "TimerManager.h"
#include "Characters/EnemyCharacter.h"



UBTService_Shoot::UBTService_Shoot()
{
	NodeName = TEXT("Shoot");

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;

	StartFireDelay = 1.0f;
}

void UBTService_Shoot::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* SelfController = OwnerComp.GetAIOwner();
	AEnemyCharacter* SelfCharacter = Cast<AEnemyCharacter>(SelfController->GetPawn());

	if (SelfCharacter != nullptr)
	{
		FTimerDelegate FireDelayTimerDelegate;

		FireDelayTimerDelegate.BindUFunction(this, "FireAfterDelay", SelfCharacter);
		SelfCharacter->GetWorldTimerManager().SetTimer(FireDelayTimerHandle, FireDelayTimerDelegate, StartFireDelay, false);
	}
}

void UBTService_Shoot::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* SelfController = OwnerComp.GetAIOwner();
	AEnemyCharacter* SelfCharacter = Cast<AEnemyCharacter>(SelfController->GetPawn());

	if (SelfCharacter != nullptr)
	{
		SelfCharacter->GetWorldTimerManager().ClearTimer(FireDelayTimerHandle);
		SelfCharacter->StopFiring();
	}
}

void UBTService_Shoot::FireAfterDelay(AEnemyCharacter* SelfCharacter)
{
	SelfCharacter->Fire();
}