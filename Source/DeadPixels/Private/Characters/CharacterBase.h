// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Components/TimelineComponent.h"
#include "CharacterBase.generated.h"

class UHealthComponent;
class UTimelineComponent;
/**
 * 
 */
UCLASS()
class ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	ACharacterBase();

	UFUNCTION()
	void AnyDamageTaken(AActor* DamagedActor, float DamageAmount, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	virtual void HandleHitExtended(){}

	UFUNCTION()
	void GetKnockback(AActor* Actor);

	UFUNCTION()
	void SpriteToWhite();

	UFUNCTION()
	virtual void EndHitStop(ACharacterBase* ActorHitStop);

	UFUNCTION()
	void KnockbackTimelineUpdate(float Value);

	UFUNCTION()
	virtual void OnStunnedOverrideCompleted(bool IsCompleted);
	
	UPROPERTY(EditAnywhere)
	bool IsStunned;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	UHealthComponent* HealthComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* HurtBox;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Knockback")
	UTimelineComponent* KnockbackTimeline;

	UPROPERTY(EditAnywhere, Category = "Knockback")
	float KnockbackStrength = 500.f;

	UPROPERTY(EditAnywhere, Category = "Knockback")
	FVector KnockbackDirection;

	UPROPERTY(EditAnywhere, Category = "Knockback")
	class UCurveFloat* KnockbackCurve;

private:
	FOnTimelineFloat KnockbackUpdateFunction;
	FTimerHandle HitStopHandle;
	FTimerHandle FlashSpriteHandle;
	FTimerHandle StunnedHandle;
	float StunnedTime = 0.2f;

	float HitStopDuration = 0.1f;
	

};
