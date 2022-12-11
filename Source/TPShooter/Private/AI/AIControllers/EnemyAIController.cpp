// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIControllers/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/EnemyCharacter.h"



AEnemyAIController::AEnemyAIController()
{
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComp->ConfigureSense(*SightConfig);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AEnemyCharacter>(GetPawn());

	RunBehaviorTree(BehaviorTree);

	AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::PerceptionUpdate);
}

void AEnemyAIController::PerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Actor))
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();

		if (Stimulus.WasSuccessfullySensed())
		{
			BlackboardComp->SetValueAsObject("Player", PlayerCharacter);

			Character->bUseControllerRotationYaw = true;
		}
		else
		{
			BlackboardComp->ClearValue("Player");
			SetLastPlayerLocation(PlayerCharacter);

			Character->bUseControllerRotationYaw = false;
		}
	}
}

void AEnemyAIController::SetLastPlayerLocation(AActor* PlayerActor)
{
	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();

	BlackboardComp->SetValueAsVector("LastPlayerLocation", PlayerActor->GetActorLocation());
}
