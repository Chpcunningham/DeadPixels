// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemyBase.h"

#include "PaperZDAnimationComponent.h"
#include "AI/EnemyAI_Base.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyBase::AEnemyBase()
{
	AIControllerClass = AEnemyAI_Base::StaticClass();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->SetCanBeDamaged(true);

	HurtBox = CreateDefaultSubobject<UBoxComponent>(FName("HurtBox"));
	HurtBox->SetupAttachment(RootComponent);

	
}

void AEnemyBase::MoveEnemy(FVector WorldDirection)
{
	this->AddMovementInput(WorldDirection, 1.f);
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	GetAnimationComponent()->SetAnimInstanceClass(EnemyInstance);
}
