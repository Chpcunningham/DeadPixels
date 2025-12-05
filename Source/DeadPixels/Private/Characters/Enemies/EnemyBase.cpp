// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemyBase.h"

#include "AI/EnemyAI_Base.h"
#include "Characters/CharacterBase.h"
#include "Characters/Player/MainCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameMode/GM_DeadPixels.h"
#include "Kismet/GameplayStatics.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDAnimationComponent.h"

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

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::MoveEnemy(FVector WorldDirection)
{
	if (!HealthComp->IsDead)
	{
		this->AddMovementInput(WorldDirection, 1.f);
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
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
		SetStun();
	}
}

void AEnemyBase::EndHitStop(ACharacterBase* ActorHitStop)
{
	Super::EndHitStop(ActorHitStop);
}

void AEnemyBase::OnOverlapPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if (AMainCharacter* Player = Cast<AMainCharacter>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(Player, Damage, this->GetController(), this, UDamageType::StaticClass());
	}
}

void AEnemyBase::OnInvincibilityEnd_DelegateSignature()
{
	GetSprite()->SetVisibility(true);
	HurtBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	GetAnimationComponent()->SetAnimInstanceClass(EnemyInstance);

	AGM_DeadPixels* GM = Cast<AGM_DeadPixels>(GetWorld()->GetAuthGameMode());

	float BonusHealth = GM ? GM->GlobalEnemyHealthBonus : 0.f;
	float BonusDamage = GM ? GM->GlobalEnemyDamageBonus : 0.f;
	float BonusWalkSpeed = GM ? GM->GlobalEnemyWalkSpeedBonus : 0.f;

	HealthComp->MaxHealth += BonusHealth;
	HealthComp->CurrentHealth += BonusHealth;
	Damage += BonusDamage;
	WalkSpeed += BonusWalkSpeed;

	if (HurtBox)
	{
		HurtBox->SetHiddenInGame(false);
		HurtBox->ShapeColor = FColor::Red;
	}
	HealthComp->OnInvincibiltyEndDelegate.AddDynamic(this,
	                                                 &AEnemyBase::OnInvincibilityEnd_DelegateSignature);
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
	AMainCharacter* Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	Player->PlayerPoints += 10;
	Player->CurrentWeapon->Experience += 10.f;
	
	HurtBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	int32 DeathChoice = FMath::RandRange(0, 1);
	if (UPaperZDAnimInstance* EnemyAnimInstance = GetAnimationComponent()->GetAnimInstance())
	{
		GEngine->AddOnScreenDebugMessage(1, 4.f, FColor::Red, FString(TEXT("Attempting to play death animation")));
		switch (DeathChoice)
		{
		case 0: EnemyAnimInstance->JumpToNode(FName("DeathJump"));
			GEngine->AddOnScreenDebugMessage(1, 4.f, FColor::Red, FString(TEXT("Playing Death")));
			break;
		case 1: EnemyAnimInstance->JumpToNode(FName("Death2Jump"));
			GEngine->AddOnScreenDebugMessage(1, 4.f, FColor::Red, FString(TEXT("Playing Death2")));
			break;
		default: EnemyAnimInstance->JumpToNode(FName("DeathJump"));
			GEngine->AddOnScreenDebugMessage(1, 4.f, FColor::Red, FString(TEXT("Playing Default Death")));
		}
			
	}
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
	OnEnemyDied.Broadcast(this);
	this->Destroy();
}
