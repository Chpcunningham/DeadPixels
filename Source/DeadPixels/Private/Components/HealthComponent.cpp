// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Characters/Player/MainCharacter.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 50.f;
}

void UHealthComponent::DecreaseHealth(float Damage)
{
	CurrentHealth -= Damage;
	CurrentHealth = FMath::Max(CurrentHealth, 0.f);
	if (CurrentHealth <= 0.f)
	{
		IsDead = true;
	}
}

void UHealthComponent::StartInvincibility()
{
	IsInvincible = true;
	if (AMainCharacter* Player = Cast<AMainCharacter>(GetOwner()))
	{
		Player->GetWorldTimerManager().SetTimer(
			InvincibilityHandle,
			FTimerDelegate::CreateUObject(
				this,
				&UHealthComponent::EndInvincibility),
				InvincibilityDuration,
				false);
	}
}

void UHealthComponent::EndInvincibility()
{
	IsInvincible = false;
	OnInvincibiltyEndDelegate.Broadcast();
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

