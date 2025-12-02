#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "Engine/TimerHandle.h"
class AWeapons;
#include "Bullet.generated.h"

UCLASS()
class ABullet : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* BulletSprite;

	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsLaunched = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DeleteTime = 10.0f;

	UPROPERTY()
	AWeapons* CurrentWeapon;

	FTimerHandle DeleteTimer;

	ABullet();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Launch(FVector2D Direction, float Speed);

	void SetWeapon(AWeapons* Weapon);

	void OnDeleteTimerTimeOut();
};
