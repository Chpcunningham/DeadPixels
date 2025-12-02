// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SpawnManager.h"
#include "Characters/Enemies/EnemyBase.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

TArray<AEnemyBase*> ASpawnManager::SpawnEnemies(int32 NumOfEnemies, TArray<TSubclassOf<AEnemyBase>> EnemiesToChooseFrom, AActor* Player)
{
	TArray<AEnemyBase*> NewlySpawnedEnemies;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.Owner = this;
	
	for (int32 i = 0; i < NumOfEnemies; i++)
	{
		
		int32 RandomEnemy = FMath::RandRange(0, EnemiesToChooseFrom.Num() - 1);
		TSubclassOf<AEnemyBase> EnemyToSpawn = EnemiesToChooseFrom[RandomEnemy];
        
		
		AEnemyBase* CurrentEnemySpawn = GetWorld()->SpawnActor<AEnemyBase>(
			EnemyToSpawn,
			GenerateSpawnLocation(Player, 300.f, 600.f),
			FRotator::ZeroRotator,
			SpawnParams
			);

		if (CurrentEnemySpawn)
		{
			NewlySpawnedEnemies.Add(CurrentEnemySpawn);
			LiveEnemies.Add(CurrentEnemySpawn);

			CurrentEnemySpawn->OnEnemyDied.AddDynamic(this, &ASpawnManager::OnEnemyDied_DelegateSignature);
		}
	}

	return NewlySpawnedEnemies;
}

FVector ASpawnManager::GenerateSpawnLocation(AActor* Player, float MinRadius, float MaxRadius)
{
	FVector PlayerLocation = Player->GetActorLocation();

	FVector SpawnDirection = FMath::VRand();
	float DistanceFromPlayer = FMath::FRandRange(MinRadius, MaxRadius);

	FVector SpawnOffset = SpawnDirection * DistanceFromPlayer;
	
	FVector RandomSpawnLocation = PlayerLocation + SpawnOffset;
	RandomSpawnLocation.Z = PlayerLocation.Z + 5.f;

	return RandomSpawnLocation;
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawnManager::OnEnemyDied_DelegateSignature(AEnemyBase* DeadEnemy)
{
	LiveEnemies.Remove(DeadEnemy);

	CheckForNextWave();
}

void ASpawnManager::CheckForNextWave()
{
	if (LiveEnemies.Num() == 0)
	{
		OnAllEnemiesDefeated.Broadcast();
	}
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

