//Connor Cunningham

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInvincibiltyEnd);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOnInvincibiltyEnd OnInvincibiltyEndDelegate;
	
	UFUNCTION()
	void DecreaseHealth(float Damage);

	UFUNCTION()
	void StartInvincibility();

	UFUNCTION()
	void EndInvincibility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category="Health")
	bool IsDead = false;

	UPROPERTY(EditAnywhere, Category="Health")
	bool IsInvincible = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FTimerHandle InvincibilityHandle;
	float InvincibilityDuration = 2.f;
};
