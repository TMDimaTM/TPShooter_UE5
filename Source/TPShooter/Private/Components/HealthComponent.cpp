// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Interfaces/DeathInterface.h"

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


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentHealth > 0)
	{
		CurrentHealth -= Damage;
		if (CurrentHealth <= 0)
		{
			if (IDeathInterface* Interface = Cast<IDeathInterface>(DamagedActor))
			{
				Interface->Execute_Death(DamagedActor);
			}
		}
	}
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth / TotalHealth;
}

