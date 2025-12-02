// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "EnemyBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDied, AEnemyBase*, DiedEnemy);

UCLASS()
class AEnemyBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	AEnemyBase();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEnemyDied OnEnemyDied;

	virtual void Tick(float DeltaTime) override;

	void MoveEnemy(FVector WorldDirection);

	virtual void HandleHitExtended() override;

	virtual void EndHitStop(ACharacterBase* ActorHitStop) override;

	UFUNCTION()
	void OnOverlapPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							   const FHitResult& SweepResult);

	UFUNCTION()
	void OnInvincibilityEnd_DelegateSignature();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D EnemyDirectionality;
protected:
	virtual void BeginPlay() override;

	void SetStun();
	void EndStun();
	void Defeated();
	
	UFUNCTION(BlueprintCallable)
	void HandleDefeat();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TSubclassOf<UPaperZDAnimInstance> EnemyInstance;
private:
	FTimerHandle HitHandle;
	FTimerHandle HandleDefeatTimerHandle;
	FTimerHandle SetStunHandle;
	FTimerHandle DespawnHandle;

	float DeathAnimationDuration = 2.f;
	float HitStopDuration = 0.1f;
	float StunnedDuration = 0.5f;
	float DespawnDuration = 3.f;
};
