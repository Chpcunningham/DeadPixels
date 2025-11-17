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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FireRate = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumOfBullets = 1;
    
    FTimerHandle CooldownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanAttack = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	int Ammo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	bool bIsMelee = false;

	UFUNCTION(BluePrintCallable, Category = "Weapons")
	virtual void Fire();

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
