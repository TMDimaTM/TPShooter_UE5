// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RifleActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Actors/ProjectileActor.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"



ARifleActor::ARifleActor()
{
	MuzzleFlash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Muzzle Flash"));
	MuzzleFlash->SetupAttachment(RootComponent);

	FireRate = 0.1f;
}

void ARifleActor::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
}

void ARifleActor::Fire_Implementation()
{
	MuzzleFlash->Activate();

	if (UCameraComponent* Camera = GetOwner()->FindComponentByClass<UCameraComponent>())
	{
		PlayerShot(Camera);

		FTimerDelegate FireTimerDeleagate;
		FireTimerDeleagate.BindUFunction(this, "PlayerShot", Camera);
		GetWorldTimerManager().SetTimer(FireTimerHandle, FireTimerDeleagate, FireRate, true);
	}
	else
	{
		EnemyShot();

		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ARifleActor::EnemyShot, FireRate, true);
	}
}

void ARifleActor::StopFiring_Implementation()
{
	MuzzleFlash->Deactivate();

	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void ARifleActor::PlayerShot(UCameraComponent* Camera)
{
	if (Camera != nullptr)
	{
		FVector StartLocation;
		FVector EndLocation;

		FHitResult HitResult;

		StartLocation = Camera->GetComponentLocation();
		EndLocation = Camera->GetForwardVector() * 99999.0f + StartLocation;

		SpawnProjectileLocation = Mesh->GetSocketTransform("MuzzleFlashSocket").GetLocation();

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);
		if (bHit)
		{
			SpawnProjectileRotation = UKismetMathLibrary::FindLookAtRotation(SpawnProjectileLocation, HitResult.ImpactPoint);
		}
		else
		{
			SpawnProjectileRotation = Camera->GetComponentRotation();
		}

		SpawnProjectile();
	}
}

void ARifleActor::EnemyShot()
{
	SpawnProjectileLocation = Mesh->GetSocketTransform("MuzzleFlashSocket").GetLocation();

	if (PlayerCharacter != nullptr)
	{
		SpawnProjectileRotation = UKismetMathLibrary::FindLookAtRotation(SpawnProjectileLocation, PlayerCharacter->GetActorLocation());
	}

	SpawnProjectile();
}

void ARifleActor::SpawnProjectile()
{
	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileActor>(Projectile, SpawnProjectileLocation, SpawnProjectileRotation);
	SpawnedProjectile->SetOwner(GetOwner());
}