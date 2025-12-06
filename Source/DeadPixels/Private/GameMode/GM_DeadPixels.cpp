//Connor Cunningham


#include "GameMode/GM_DeadPixels.h"

#include "Blueprint/UserWidget.h"
#include "GameMode/SpawnManager.h"
#include "Characters/Player/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

void AGM_DeadPixels::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	TArray<AActor*> SpawnManagersFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnManager::StaticClass(), SpawnManagersFound);
	if (SpawnManagersFound.Num() > 0)
	{
		SpawnManagerInstance = Cast<ASpawnManager>(SpawnManagersFound[0]);
	}
	if (SpawnManagerInstance == nullptr && SpawnManagerClass != nullptr)
	{
		SpawnManagerInstance = GetWorld()->SpawnActor<ASpawnManager>(SpawnManagerClass);
	}
	if (SpawnManagerInstance)
	{
		SpawnManagerInstance->OnAllEnemiesDefeated.AddDynamic(this, &AGM_DeadPixels::HandleWaveCompletion);
		if (MainMenuClass)
		{
			MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuClass);
			MainMenu->AddToViewport(50);
		}
	}
}

void AGM_DeadPixels::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGM_DeadPixels::StartNextWave()
{
	CurrentWave++;
	int32 NumOfEnemies = CurrentWave * 2;

	if (SpawnManagerInstance && Player && EnemiesForWave.Num() > 0)
	{
		SpawnManagerInstance->SpawnEnemies(
			NumOfEnemies, 
			EnemiesForWave, 
			Player
		);
	}
}

void AGM_DeadPixels::HandleWaveCompletion()
{

	GetWorldTimerManager().SetTimer(
		WaveTimerHandle, 
		this, 
		&AGM_DeadPixels::StartNextWave, 
		5.0f, 
		false 
	);
}
