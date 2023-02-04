// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class TPSHOOTER_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileActor> Projectile;

	FVector SpawnProjectileLocation;
	FRotator SpawnProjectileRotation;

	FTransform GetMuzzleTransform() const;

	void SpawnProjectile() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* Mesh;
};
