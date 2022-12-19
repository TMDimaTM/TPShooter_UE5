// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/WeaponActor.h"
#include "Interfaces/WeaponInterface.h"
#include "ShotgunActor.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API AShotgunActor : public AWeaponActor, public IWeaponInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Fire();
	virtual void Fire_Implementation();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* MuzzleFlash;
};
