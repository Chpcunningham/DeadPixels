// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"
#include "PaperZDAnimInstance.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"

ACharacterBase::ACharacterBase()
{
	GetSprite()->SetWorldRotation(FRotator(0.f,0.f,270.f));
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
