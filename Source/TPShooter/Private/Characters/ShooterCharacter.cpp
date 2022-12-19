// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ShooterCharacter.h"
#include "Components/HealthComponent.h"
#include "Actors/WeaponActor.h"
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

	if (WeaponActorClasses.Num() > 0)
	{
		SpawnWeapons();
		SetStartWeapon();
	}
}

void AShooterCharacter::SpawnWeapons()
{
	FTransform SocketTransform = GetMesh()->GetSocketTransform("rifle_r");

	for (int32 i = 0; i < WeaponActorClasses.Num(); i++)
	{
		AWeaponActor* SpawnedWeapon = GetWorld()->SpawnActor<AWeaponActor>(WeaponActorClasses[i], SocketTransform);
		SpawnedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "rifle_r");
		SpawnedWeapon->SetOwner(this);

		UsableWeapons.Add(SpawnedWeapon);
	}
}

void AShooterCharacter::SetStartWeapon()
{
	for (int32 i = 1; i < UsableWeapons.Num(); i++)
	{
		UsableWeapons[i]->SetActorHiddenInGame(true);
	}
	CurrentWeapon = UsableWeapons[0];
}

bool AShooterCharacter::IsSprinting()
{
	return GetVelocity().Length() >= SprintMaxSpeed - 10.0f;
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

void AShooterCharacter::ChangeWeapon()
{
	StopFiring();

	CurrentWeapon->SetActorHiddenInGame(true);

	if (CurrentWeaponIndex >= UsableWeapons.Num() - 1)
	{
		CurrentWeaponIndex = 0;
	}
	else
	{
		CurrentWeaponIndex++;
	}

	CurrentWeapon = UsableWeapons[CurrentWeaponIndex];
	CurrentWeapon->SetActorHiddenInGame(false);
}

void AShooterCharacter::DeathParent()
{
	bIsDead = true;

	StopFiring();
	SetActorEnableCollision(false);
}