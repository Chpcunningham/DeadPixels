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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapons")
	USceneComponent* WeaponParent;

	void SetEquippedWeapon(AWeapons* NewWeapon);
	AWeapons* GetEquippedWeapon() const;
	
protected:
	void Movement(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void LevelUp(const FInputActionValue& Value);
	void SwapWeapons(const FInputActionValue& Value);

private:
	float WalkSpeed = 350.f;
	float RunSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons", meta=(AllowPrivateAccess=true))
	AWeapons* CurrentWeapon = nullptr;
	
	UPROPERTY(EditAnywhere, Category=Input)
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* SwapWeaponsAction;
	
	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* LevelUpAction;
	
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	
};
