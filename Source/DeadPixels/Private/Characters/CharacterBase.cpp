// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

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
}

void ACharacterBase::AnyDamageTaken(AActor* DamagedActor, float DamageAmount, const class UDamageType* DamageType,
                                    class AController* InstigatedBy, AActor* DamageCauser)
{
	UGameplayStatics::ApplyDamage(DamagedActor, DamageAmount, this->GetController(), DamageCauser, UDamageType::StaticClass());
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	HealthComp->CurrentHealth = HealthComp->MaxHealth;
}
