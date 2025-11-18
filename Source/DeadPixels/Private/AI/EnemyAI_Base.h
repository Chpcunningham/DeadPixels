// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI_Base.generated.h"

/**
 * 
 */
UCLASS()
class AEnemyAI_Base : public AAIController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float DistanceToPlayer();

	UPROPERTY(EditAnywhere)
	class AEnemyBase* PossessedEnemy;

	UPROPERTY(EditAnywhere)
	class APawn* PlayerTarget;

private:
	float StopDistance = 10.f;
};
