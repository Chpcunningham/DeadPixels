// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/BigZombie.h"

#include "Components/BoxComponent.h"

ABigZombie::ABigZombie()
{
	HurtBox->SetBoxExtent(FVector(32.f, 38.f, 32.f));
}
