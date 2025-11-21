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

	HurtBox->SetGenerateOverlapEvents(true);
	HurtBox->UpdateOverlaps();
	
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
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Blue, FString(TEXT("OverlappingPLayer")));
	}
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	GetAnimationComponent()->SetAnimInstanceClass(EnemyInstance);

	// Debug: Print collision settings
	if (HurtBox)
	{
		FString CollisionObjectType = UEnum::GetValueAsString(HurtBox->GetCollisionObjectType());
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, 
			FString::Printf(TEXT("HurtBox ObjectType: %s"), *CollisionObjectType));
        
		// Check if overlap events are enabled
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, 
			FString::Printf(TEXT("HurtBox GenerateOverlapEvents: %s"), 
			HurtBox->GetGenerateOverlapEvents() ? TEXT("True") : TEXT("False")));

		// Make HurtBox visible for debugging
		HurtBox->SetHiddenInGame(false);
		HurtBox->ShapeColor = FColor::Red;
	}
}
