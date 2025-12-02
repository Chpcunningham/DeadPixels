#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Bullet.h"
#include "PaperFlipbookComponent.h"
#include "Weapons.generated.h"

UCLASS()
class DEADPIXELS_API AWeapons : public AActor
{
	GENERATED_BODY()

	public:
	AWeapons();

	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* WeaponParent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* WeaponFlipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* BulletSpawnPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	bool CanAttack = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	float Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	int Ammo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
    float FireRate = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	int NumOfBullets = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	float BulletSize = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	float BulletSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	float BulletSpread;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	bool bIsMelee = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Experience;

	UFUNCTION(BluePrintCallable, Category = "Weapons")
	virtual void Fire();
	
    FTimerHandle CooldownTimer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABullet> BulletActorToSpawn;
	
	void OnCooldownTimerTimeout();
	
};
/*class Weapons
{
public:
	Weapons();
	~Weapons();
};*/
