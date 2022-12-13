// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTServices/BTService_SetFocus.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"



UBTService_SetFocus::UBTService_SetFocus()
{
	NodeName = TEXT("Set Focus");

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTService_SetFocus::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (BlackboardComp != nullptr)
	{
		OwnerComp.GetAIOwner()->SetFocus(Cast<AActor>(BlackboardComp->GetValueAsObject(GetSelectedBlackboardKey())));
	}
}

void UBTService_SetFocus::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);
}
