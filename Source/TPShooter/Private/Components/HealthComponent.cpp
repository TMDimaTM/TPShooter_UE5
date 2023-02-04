// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/DeathInterface.h"
#include "AI/AIControllers/EnemyAIController.h"
#include "GameModes/ShooterGameModeBase.h"



// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	TotalHealth = 100.0f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = TotalHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamagedActor != nullptr)
	{
		if (CurrentHealth > 0)
		{
			CurrentHealth -= Damage;
			if (CurrentHealth <= 0)
			{
				if (IDeathInterface* Interface = Cast<IDeathInterface>(DamagedActor))
				{
					Interface->Execute_Death(DamagedActor);

					AShooterGameModeBase* GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
					if (GameMode != nullptr)
					{
						GameMode->CheckGameCondition(DamagedActor);
					}
				}
			}
			else
			{
				AController* PlayerController = Cast<AController>(UGameplayStatics::GetPlayerController(this, 0));
				if (PlayerController != nullptr && InstigatedBy == PlayerController)
				{
					APawn* OwnerPawn = Cast<APawn>(GetOwner());
					if (OwnerPawn != nullptr)
					{
						AEnemyAIController* OwnerAIController = Cast<AEnemyAIController>(OwnerPawn->GetController());
						if (OwnerAIController != nullptr)
						{
							OwnerAIController->SetLastPlayerLocation(PlayerController->GetPawn());
						}
					}
				}
			}
		}
	}
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth / TotalHealth;
}