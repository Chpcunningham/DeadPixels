// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AxeZombie.h"

#include "Components/BoxComponent.h"

AAxeZombie::AAxeZombie()
{
	HurtBox->SetBoxExtent(FVector(32, 40, 32));
}
