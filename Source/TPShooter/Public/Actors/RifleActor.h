// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/WeaponActor.h"
#include "Interfaces/WeaponInterface.h"
#include "RifleActor.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API ARifleActor : public AWeaponActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:
	ARifleActor();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Fire();
	virtual void Fire_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopFiring();
	virtual void StopFiring_Implementation();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* MuzzleFlash;

	ACharacter* PlayerCharacter;

	FTimerHandle FireTimerHandle;

	FVector SpawnProjectileLocation;
	FRotator SpawnProjectileRotation;

	UFUNCTION()
	void PlayerShot(UCameraComponent* Camera);
	void EnemyShot();

	void SpawnProjectile();
};
