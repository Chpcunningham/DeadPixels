// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemyBase.h"
#include "SmallZombie.generated.h"

/**
 * 
 */
UCLASS()
class ASmallZombie : public AEnemyBase
{
	GENERATED_BODY()
public:
	ASmallZombie();

	UPROPERTY(EditAnywhere)
	UPaperZDAnimInstance* SmallZombieInstance;
};
