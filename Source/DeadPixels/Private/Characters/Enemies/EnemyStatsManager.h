#pragma once

#include "CoreMinimal.h"
#include "EnemyStatsData.h"
#include "UObject/Object.h"
#include "EnemyStatsManager.generated.h"

UCLASS(Blueprintable)
class DEADPIXELS_API UEnemyStatsManager : public UObject {
  GENERATED_BODY()

  public:
  static UEnemyStatsManager* Get(UWorld* World);

  float GlobalEnemyHealthBonus = 0.f;
  float GlobalEnemyDamageBonus = 0.f;

  void ApplyHealthBonus(float Amount)
  {
    GlobalEnemyHealthBonus += Amount;
  }

  void ApplyDamageBonus(float Amount)
  {
    GlobalEnemyDamageBonus += Amount;
  }
};
