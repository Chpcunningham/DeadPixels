// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

#include "Kismet/KismetMathLibrary.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 5.f;
}

void UHealthComponent::DecreaseHealth(float Damage)
{
	CurrentHealth -= Damage;
	if (!UKismetMathLibrary::Max(CurrentHealth, 0.0f))
	{
		IsDead = true;
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

