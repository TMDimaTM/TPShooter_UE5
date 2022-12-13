// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ShooterCharacter.h"
#include "Actors/RifleActor.h"
#include "Components/HealthComponent.h"
#include "Interfaces/WeaponInterface.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Spawn rifle with attaching to Character
	FTransform SocketTransform = GetMesh()->GetSocketTransform("rifle_r");

	SpawnedRifle = GetWorld()->SpawnActor<ARifleActor>(Rifle, SocketTransform);
	SpawnedRifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "rifle_r");
	SpawnedRifle->SetOwner(this);

	CurrentWeapon = SpawnedRifle;
}

void AShooterCharacter::Fire()
{
	if (IWeaponInterface* Interface = Cast<IWeaponInterface>(CurrentWeapon))
	{
		if (!bIsDead && !IsSprinting())
		{
			Interface->Execute_Fire(CurrentWeapon);
		}
	}
}

void AShooterCharacter::StopFiring()
{
	if (IWeaponInterface* Interface = Cast<IWeaponInterface>(CurrentWeapon))
	{
		Interface->Execute_StopFiring(CurrentWeapon);
	}
}

bool AShooterCharacter::IsSprinting()
{
	return GetVelocity().Length() >= SprintMaxSpeed - 10.0f;
}


void AShooterCharacter::DeathParent()
{
	bIsDead = true;

	StopFiring();
	SetActorEnableCollision(false);
}