// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"

void AEnemyCharacter::Fire()
{
	Super::Fire();
}

void AEnemyCharacter::StopFiring()
{
	Super::StopFiring();
}

void AEnemyCharacter::Death_Implementation()
{
	DeathParent();

	DetachFromControllerPendingDestroy();
}
