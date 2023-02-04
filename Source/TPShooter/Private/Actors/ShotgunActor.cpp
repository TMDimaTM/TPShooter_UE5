// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ShotgunActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"


AShotgunActor::AShotgunActor()
{
	BulletsPerShot = 5;

	RandomBulletAngle = 2.0f;
}

void AShotgunActor::Fire_Implementation()
{
	if (MuzzleFlash != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, GetMuzzleTransform());
	}

	for (int32 i = 0; i < BulletsPerShot; i++)
	{
		SetRandomBulletDirection();
		SpawnProjectile();
	}
}

void AShotgunActor::SetRandomBulletDirection()
{
	if (UCameraComponent* Camera = GetOwner()->FindComponentByClass<UCameraComponent>())
	{
		SpawnProjectileLocation = GetMuzzleTransform().GetLocation();

		FVector Direction = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(Camera->GetForwardVector(), RandomBulletAngle);
		SpawnProjectileRotation = Direction.Rotation();
	}
}