// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "Weapons/Weapons.h"

#include "Engine/TimerHandle.h"
#include "Bullet.h"

#include "MainCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class AMainCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	AMainCharacter();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GameplayTags)
	FGameplayTagContainer PlayerTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Directionality;

	UPROPERTY(EditAnywhere, Category = AnimInstance)
	TSubclassOf<UPaperZDAnimInstance> PlayerInstance;
	
	//This is temporary
	//To move to Weapons soon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* WeaponParent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* WeaponFlipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* BulletSpawnPosition;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABullet> BulletActorToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanShoot = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownDuration = 0.3f;

	FTimerHandle CooldownTimer;
	
protected:
	void Movement(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	

private:
	float WalkSpeed = 350.f;
	float RunSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category="Weapons")
	AWeapons* CurrentWeapon;
	
	UPROPERTY(EditAnywhere, Category=Input)
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	//Temporary
	void OnCooldownTimerTimeout();
};
