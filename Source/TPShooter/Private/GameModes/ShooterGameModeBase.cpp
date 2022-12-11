// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/EnemyCharacter.h"



void AShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetAliveEnemies();
}

void AShooterGameModeBase::CheckGameCondition(AActor* DeadActor)
{
	if (Cast<APlayerCharacter>(DeadActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Lose"));
	}
	else
	{
		if (GetAliveEnemies().Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Win"));
		}
	}
}

TArray<AActor*> AShooterGameModeBase::GetAliveEnemies()
{
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemyCharacter::StaticClass(), EnemyActors);

	AliveEnemyActors.Empty();
	for (AActor* Actor : EnemyActors)
	{
		if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Actor))
		{
			if (!EnemyCharacter->bIsDead)
			{
				AliveEnemyActors.Add(EnemyCharacter);
			}
		}
	}
	return AliveEnemyActors;
}

FText AShooterGameModeBase::GetEnemiesLeft()
{
	return FText::AsNumber(AliveEnemyActors.Num());
}