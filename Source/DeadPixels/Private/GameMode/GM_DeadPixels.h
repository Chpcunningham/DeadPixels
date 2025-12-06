//Connor Cunningham
//Maxwell Clement --Only global enemy bonuses

#pragma once

#include "CoreMinimal.h"
#include "Characters/Player/MainCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "GM_DeadPixels.generated.h"

/**
 * 
 */
class AMainCharacter;
class ASpawnManager; 
class AEnemyBase;

UCLASS()
class AGM_DeadPixels : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void StartNextWave();

	UFUNCTION()
	void HandleWaveCompletion();

	UPROPERTY()
	ASpawnManager* SpawnManagerInstance;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ASpawnManager> SpawnManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning", BlueprintReadWrite)
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning", BlueprintReadWrite)
	class UUserWidget* MainMenu;
	
	UPROPERTY(EditAnywhere, Category=Enemies)
	TArray<TSubclassOf<class AEnemyBase>> EnemiesForWave;
	
	UPROPERTY(EditAnywhere, Category=Player)
	AMainCharacter* Player;

	UPROPERTY(BlueprintReadWrite)
	float GlobalEnemyHealthBonus = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float GlobalEnemyDamageBonus = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float GlobalEnemyWalkSpeedBonus = 0.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 CurrentWave = 0;

private:
	FTimerHandle WaveTimerHandle;
};
