// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/GameOverUserWidget.h"
#include "Components/TextBlock.h"



void UGameOverUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (bIsWin)
	{
		GameOverText->SetText(FText::FromString("Nice job!"));
	}
	else
	{
		GameOverText->SetText(FText::FromString("Try again!"));
	}
}