#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
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
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	int Ammo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
	bool bIsMelee = false;

	UFUNCTION(BluePrintCallable, Category = "Weapons")
	virtual void Fire();
	
};
/*class Weapons
{
public:
	Weapons();
	~Weapons();
};*/
