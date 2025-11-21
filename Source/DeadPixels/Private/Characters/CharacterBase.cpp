// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ACharacterBase::ACharacterBase()
{
	GetSprite()->SetWorldRotation(FRotator(0.f,0.f,270.f));
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	HurtBox = CreateDefaultSubobject<UBoxComponent>(FName("HurtBox"));
    HurtBox->SetupAttachment(RootComponent);
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
