// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemyBase.h"

#include "PaperZDAnimationComponent.h"
#include "AI/EnemyAI_Base.h"
#include "Characters/Player/MainCharacter.h"
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

	HurtBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlapPlayer);

	
}

void AEnemyBase::MoveEnemy(FVector WorldDirection)
{
	this->AddMovementInput(WorldDirection, 1.f);
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
}

void AEnemyBase::OnOverlapPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainCharacter* Player = Cast<AMainCharacter>(OtherActor))
	{
		if (Player->HurtBox != OtherComp)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("Overlapped with player"));
		}
	}
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	GetAnimationComponent()->SetAnimInstanceClass(EnemyInstance);
}
