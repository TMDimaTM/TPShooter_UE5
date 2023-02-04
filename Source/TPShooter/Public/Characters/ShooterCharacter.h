// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class TPSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float DefaultMaxSpeed = 375.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintMaxSpeed = 500.0f;

	void Fire();
	void StopFiring();

	void ChangeWeapon();

	void DeathParent();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TArray<TSubclassOf<class AWeaponActor>> WeaponActorClasses;

	UPROPERTY()
	TArray<AWeaponActor*> UsableWeapons;

	UPROPERTY()
	AActor* CurrentWeapon;

	int32 CurrentWeaponIndex;

	bool IsSprinting() const;

	void SpawnWeapons();
	void SetStartWeapon();
};
