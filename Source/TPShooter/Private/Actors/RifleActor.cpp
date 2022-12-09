// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RifleActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Actors/ProjectileActor.h"
#include "TimerManager.h"



ARifleActor::ARifleActor()
{
	MuzzleFlash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Muzzle Flash"));
	MuzzleFlash->SetupAttachment(RootComponent);

	FireRate = 0.1f;
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
	}
}

void ARifleActor::StopFiring_Implementation()
{
	MuzzleFlash->Deactivate();

	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void ARifleActor::PlayerShot(UCameraComponent* Camera)
{
	FVector StartLocation;
	FVector EndLocation;

	FVector SpawnLocation;
	FRotator SpawnRotation;

	FHitResult HitResult;

	FTransform MuzzleSocketTransform = Mesh->GetSocketTransform("MuzzleFlashSocket");

	StartLocation = Camera->GetComponentLocation();
	EndLocation = Camera->GetForwardVector() * 99999.0f + StartLocation;

	SpawnLocation = MuzzleSocketTransform.GetLocation();

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);
	if (bHit)
	{
		SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, HitResult.ImpactPoint);
	}
	else
	{
		SpawnRotation = Camera->GetComponentRotation();
	}
	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileActor>(Projectile, SpawnLocation, SpawnRotation);
	SpawnedProjectile->SetOwner(GetOwner());
}

void ARifleActor::EnemyShot()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}
