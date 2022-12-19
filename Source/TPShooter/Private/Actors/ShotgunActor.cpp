// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ShotgunActor.h"
#include "Kismet/GameplayStatics.h"



void AShotgunActor::Fire_Implementation()
{
	if (MuzzleFlash != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, GetMuzzleTransform());
	}

	// Shot multiple projectiles in the different directions
}
