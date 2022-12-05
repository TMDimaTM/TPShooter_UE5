// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ShooterCharacter.h"
#include "Actors/WeaponActor.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Spawn rifle with attaching to Character
	FTransform SocketTransform = GetMesh()->GetSocketTransform("rifle_r");
	AWeaponActor* SpawnedRifle = GetWorld()->SpawnActor<AWeaponActor>(Rifle, SocketTransform);
	SpawnedRifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "rifle_r");
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}