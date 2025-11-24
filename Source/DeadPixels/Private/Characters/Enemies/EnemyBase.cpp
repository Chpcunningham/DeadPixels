// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemyBase.h"

#include "PaperZDAnimationComponent.h"
#include "AI/EnemyAI_Base.h"
#include "Characters/Player/MainCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
	if (!HealthComp->IsDead)
	{
		this->AddMovementInput(WorldDirection, 1.f);
		GetCharacterMovement()->MaxWalkSpeed = 250.f;
	}
}

void AEnemyBase::HandleHitExtended()
{
	if (HealthComp->IsDead)
	{
		HandleDefeat();
	}
	else
	{
		if (ACharacterBase* Enemy = Cast<ACharacterBase>(this))
		{
			Enemy->CustomTimeDilation = 0.f;
			GetWorldTimerManager().SetTimer(
				HitHandle,
				FTimerDelegate::CreateUObject(
					this,
					&AEnemyBase::EndHitStop, Enemy),
				this->HitStopDuration,
				false);
		}
	}
}

void AEnemyBase::EndHitStop(ACharacterBase* ActorHitStop)
{
	if (!HealthComp->IsDead)
	{
		Super::EndHitStop(ActorHitStop);
		SetStun();
	}
	else
	{
		HandleDefeat();
	}
}

void AEnemyBase::OnOverlapPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if (AMainCharacter* Player = Cast<AMainCharacter>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(Player, 1.f, this->GetController(), this, UDamageType::StaticClass());
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
		                                                 HurtBox->GetGenerateOverlapEvents()
			                                                 ? TEXT("True")
			                                                 : TEXT("False")));


		HurtBox->SetHiddenInGame(false);
		HurtBox->ShapeColor = FColor::Red;
	}
}

void AEnemyBase::SetStun()
{
	this->IsStunned = true;
	GetWorldTimerManager().SetTimer(
		SetStunHandle,
		FTimerDelegate::CreateUObject(
			this,
			&AEnemyBase::EndStun),
		StunnedDuration,
		false);
}

void AEnemyBase::EndStun()
{
	this->IsStunned = false;
}

void AEnemyBase::HandleDefeat()
{
	HurtBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorldTimerManager().SetTimer(
		DespawnHandle,
		FTimerDelegate::CreateUObject(
			this,
			&AEnemyBase::Defeated),
		DespawnDuration,
		false);
}

void AEnemyBase::Defeated()
{
	this->Destroy();
}
