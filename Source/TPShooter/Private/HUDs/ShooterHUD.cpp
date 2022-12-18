// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDs/ShooterHUD.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgets/HUDUserWidget.h"



void AShooterHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UHUDUserWidget>(GetWorld(), HUDWidgetClass);
		HUDWidget->AddToViewport();
	}
}

void AShooterHUD::RemoveHUD()
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->RemoveFromParent();
	}
}