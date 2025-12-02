#include "EnemyStatsManager.h"
#include "Engine/World.h"

UEnemyStatsManager* UEnemyStatsManager::Get(UWorld* World)
{
  static UEnemyStatsManager* Instance = nullptr;

  if (!Instance)
  {
    Instance = NewObject<UEnemyStatsManager>();
    Instance->AddToRoot();
  }

  return Instance;
}