// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShooterHUD.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API AShooterHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void RemoveHUD();

private:
	UPROPERTY(EditDefaultsOnly, Category = "User Widgets")
	TSubclassOf<class UHUDUserWidget> HUDWidgetClass;

	UHUDUserWidget* HUDWidget;
};
