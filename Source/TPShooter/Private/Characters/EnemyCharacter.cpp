// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"

void AEnemyCharacter::Death_Implementation()
{
	DeathParent();

	UE_LOG(LogTemp, Warning, TEXT("Enemy Death"));
}
