// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "CharacterBase.generated.h"

class UHealthComponent;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	UHealthComponent* HealthComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* HurtBox;
protected:
	
	virtual void BeginPlay() override;
	

};
