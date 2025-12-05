

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

	UFUNCTION()
	void FlashSpriteVisibility();

	UFUNCTION()
	void HandleSpriteVisibility();

	virtual void HandleHitExtended() override;
	void HandlePlayerDefeated();
	virtual void EndHitStop(ACharacterBase* ActorHitStop) override;
	virtual void OnStunnedOverrideCompleted(bool IsCompleted) override;

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

	UPROPERTY(BlueprintReadWrite)
	float PlayerPoints = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Experience = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons", meta=(AllowPrivateAccess=true))
	AWeapons* CurrentWeapon = nullptr;
	
	float WalkSpeed = 350.f;
	float RunSpeed = 600.f;
	
protected:
	void Movement(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void LevelUp(const FInputActionValue& Value);
	void SwapWeapons(const FInputActionValue& Value);
	void Reload(const FInputActionValue& Value);

private:

	FTimerHandle VisibleHandle;
	FTimerHandle HitHandle;
	FTimerHandle StunnedHandle;
	float StunnedTime = 0.2f;
	float HitStopDuration = 0.1f;
	

	UFUNCTION()
	void OnInvincibilityEnd_DelegateSignature();

	
	
	UPROPERTY(EditAnywhere, Category=Input)
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* SwapWeaponsAction;
	
	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* LevelUpAction;
	
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	
};
