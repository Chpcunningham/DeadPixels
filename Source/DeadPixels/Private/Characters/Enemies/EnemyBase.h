// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class AEnemyBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	AEnemyBase();

	void MoveEnemy(FVector WorldDirection);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* HurtBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TSubclassOf<UPaperZDAnimInstance> EnemyInstance;
	
};
