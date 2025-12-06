//Connor Cunningham


#include "Characters/CharacterBase.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/MainCharacter.h"

ACharacterBase::ACharacterBase()
{
	GetSprite()->SetWorldRotation(FRotator(0.f, 0.f, 270.f));
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	HurtBox = CreateDefaultSubobject<UBoxComponent>(FName("HurtBox"));
	HurtBox->SetupAttachment(RootComponent);
	HurtBox->SetGenerateOverlapEvents(true);
	HurtBox->UpdateOverlaps();
	HurtBox->SetCollisionProfileName(TEXT("HitDetection"));

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	OnTakeAnyDamage.AddDynamic(this, &ACharacterBase::AnyDamageTaken);

	KnockbackTimeline = CreateDefaultSubobject<UTimelineComponent>(FName("KnockbackTimeline"));
}

void ACharacterBase::AnyDamageTaken(AActor* DamagedActor, float DamageAmount, const class UDamageType* DamageType,
                                    class AController* InstigatedBy, AActor* DamageCauser)
{
	this->HealthComp->DecreaseHealth(DamageAmount);
	GetKnockback(DamageCauser);

	GetSprite()->SetSpriteColor(FColor::Red);
	GetWorldTimerManager().SetTimer(
		FlashSpriteHandle,
		this,
		&ACharacterBase::SpriteToWhite,
		0.2f,
		false);

	if (ACharacterBase* HitActor = Cast<ACharacterBase>(DamagedActor))
	{
		if (ACharacterBase* ActorHitStop = Cast<ACharacterBase>(DamageCauser))
		{
			ActorHitStop->CustomTimeDilation = 0.f;
			GetWorldTimerManager().SetTimer(
				HitStopHandle,
				FTimerDelegate::CreateUObject(this, &ACharacterBase::EndHitStop, ActorHitStop),
				HitStopDuration,
				false);
			
		}
		HitActor->HandleHitExtended();
	}
	IsStunned = true;
	GetWorldTimerManager().SetTimer(
		StunnedHandle,
		FTimerDelegate::CreateUObject(
			this,
			&ACharacterBase::OnStunnedOverrideCompleted,
			true),
		StunnedTime,
		false);


	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow,
	                                 FString::Printf(
		                                 TEXT("Took %f damage! Health: %f"), DamageAmount, HealthComp->CurrentHealth));
}

void ACharacterBase::GetKnockback(AActor* Actor)
{
	FVector DamageCauser = Actor->GetActorLocation();
	FVector DamagedActor = this->GetActorLocation();

	FRotator Direction = UKismetMathLibrary::FindLookAtRotation(DamageCauser, DamagedActor);

	KnockbackDirection = UKismetMathLibrary::GetForwardVector(Direction);

	KnockbackTimeline->SetPlayRate(5.f);
	KnockbackTimeline->PlayFromStart();
}

void ACharacterBase::SpriteToWhite()
{
	GetSprite()->SetSpriteColor(FColor::White);
}

void ACharacterBase::EndHitStop(ACharacterBase* ActorHitStop)
{
	ActorHitStop->CustomTimeDilation = 1.f;
}

void ACharacterBase::KnockbackTimelineUpdate(float Value)
{
	FVector TotalKnockback = UKismetMathLibrary::Multiply_VectorFloat(KnockbackDirection, KnockbackStrength);
	this->GetCharacterMovement()->Velocity = TotalKnockback;
}

void ACharacterBase::OnStunnedOverrideCompleted(bool IsCompleted)
{
	IsStunned = false;

	// if (this->HealthComp->IsDead)
	// {
	// 	//Play Death Animation
	// }

	if (AMainCharacter* Player = Cast<AMainCharacter>(this))
	{
		Player->HandleSpriteVisibility();
	}
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	HealthComp->CurrentHealth = HealthComp->MaxHealth;

	if (KnockbackTimeline)
	{
		KnockbackCurve = NewObject<UCurveFloat>(this, TEXT("KnockbackCurve"));

		if (KnockbackCurve)
		{
			KnockbackCurve->FloatCurve.AddKey(0.f, 1.f);
			KnockbackCurve->FloatCurve.AddKey(1.f, 0.f);

			KnockbackUpdateFunction.BindUFunction(this, FName("KnockbackTimelineUpdate"));
			KnockbackTimeline->AddInterpFloat(KnockbackCurve, KnockbackUpdateFunction);
			KnockbackTimeline->SetTimelineLength(1.f);
		}
	}
}
