// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDs/ShooterHUD.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgets/HUDUserWidget.h"



void AShooterHUD::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget<UHUDUserWidget>(GetWorld(), HUDWidgetClass);
	HUDWidget->AddToViewport();
}
