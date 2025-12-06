//Connor Cunningham

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

class AEnemyBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveCleared);

UCLASS()
class ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

	TArray<AEnemyBase*> SpawnEnemies(int32 NumOfEnemies, TArray<TSubclassOf<AEnemyBase>> EnemiesToChooseFrom, AActor* Player);

	FVector GenerateSpawnLocation(AActor* Player, float MinRadius, float MaxRadius);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWaveCleared OnAllEnemiesDefeated;
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AEnemyBase*> LiveEnemies;

	UFUNCTION()
	void OnEnemyDied_DelegateSignature(AEnemyBase* DeadEnemy);

	void CheckForNextWave();

public:	
	virtual void Tick(float DeltaTime) override;

};
