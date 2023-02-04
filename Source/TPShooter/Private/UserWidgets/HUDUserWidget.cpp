// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/HUDUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/HealthComponent.h"
#include "Characters/PlayerCharacter.h"
#include "GameModes/ShooterGameModeBase.h"



void UHUDUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter != nullptr)
	{
		UHealthComponent* PlayerHealthComp = PlayerCharacter->FindComponentByClass<UHealthComponent>();
		if (PlayerHealthComp != nullptr)
		{
			HealthBar->PercentDelegate.BindUFunction(PlayerHealthComp, "GetCurrentHealth");
			HealthBar->SynchronizeProperties();
		}
	}

	AShooterGameModeBase* GameMode = Cast<AShooterGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode != nullptr)
	{
		EnemyCountText->TextDelegate.BindUFunction(GameMode, "GetAliveEnemiesLeft");
		EnemyCountText->SynchronizeProperties();
	}
}