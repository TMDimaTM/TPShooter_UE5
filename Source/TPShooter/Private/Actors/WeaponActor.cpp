// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WeaponActor.h"
#include "Actors/ProjectileActor.h"


// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(Mesh);
}

FTransform AWeaponActor::GetMuzzleTransform()
{
	return Mesh->GetSocketTransform("MuzzleFlashSocket");
}

void AWeaponActor::SpawnProjectile()
{
	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileActor>(Projectile, SpawnProjectileLocation, SpawnProjectileRotation);
	SpawnedProjectile->SetOwner(GetOwner());
}