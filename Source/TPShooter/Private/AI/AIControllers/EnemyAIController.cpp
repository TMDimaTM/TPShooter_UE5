// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIControllers/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Characters/PlayerCharacter.h"



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

	RunBehaviorTree(BehaviorTree);

	AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::PerceptionUpdate);
}

void AEnemyAIController::PerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if (APlayerCharacter * PlayerCharacter = Cast<APlayerCharacter>(Actor))
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();

		if (Stimulus.WasSuccessfullySensed())
		{
			BlackboardComp->SetValueAsObject("Player", PlayerCharacter);
		}
		else
		{
			BlackboardComp->ClearValue("Player");
			BlackboardComp->SetValueAsVector("LastPlayerLocation", PlayerCharacter->GetActorLocation());
		}
	}
}