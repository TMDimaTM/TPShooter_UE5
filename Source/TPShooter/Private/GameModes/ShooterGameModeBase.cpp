// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/EnemyCharacter.h"
#include "HUDs/ShooterHUD.h"
#include "UserWidgets/GameOverUserWidget.h"



AShooterGameModeBase::AShooterGameModeBase()
{
	RestartLevelTime = 3.0f;
}

void AShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetAliveEnemies();
}

void AShooterGameModeBase::CheckGameCondition(AActor* DeadActor)
{
	if (Cast<APlayerCharacter>(DeadActor))
	{
		GameOver(false);
	}
	else
	{
		if (GetAliveEnemies().Num() <= 0)
		{
			GameOver(true);
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

FText AShooterGameModeBase::GetAliveEnemiesLeft() const
{
	return FText::AsNumber(AliveEnemyActors.Num());
}

void AShooterGameModeBase::GameOver(bool bIsWin)
{
	RemoveHUD();
	CreateGameOverWidget(bIsWin);

	FTimerHandle RestartLevelTimerHandle;
	GetWorldTimerManager().SetTimer(RestartLevelTimerHandle, this, &ThisClass::RestartLevel, RestartLevelTime, false);
}

void AShooterGameModeBase::RemoveHUD() const
{
	AShooterHUD* HUD = Cast<AShooterHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD != nullptr)
	{
		HUD->RemoveHUD();
	}
}

void AShooterGameModeBase::CreateGameOverWidget(bool bIsWin)
{
	if (GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UGameOverUserWidget>(GetWorld(), GameOverWidgetClass);
		GameOverWidget->bIsWin = bIsWin;
		GameOverWidget->AddToViewport();
	}
}

void AShooterGameModeBase::RestartLevel() const
{
	FString CurrentMapName = GetWorld()->GetMapName();
	CurrentMapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	UGameplayStatics::OpenLevel(this, FName(CurrentMapName));
}