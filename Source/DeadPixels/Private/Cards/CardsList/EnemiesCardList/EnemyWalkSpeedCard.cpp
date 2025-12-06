//Maxwell Clement

#include "EnemyWalkSpeedCard.h"

#include "GameMode/GM_DeadPixels.h"

UEnemyWalkSpeedCard::UEnemyWalkSpeedCard()
{
  CardName = "Enemy Walk Speed Boost";
  Description = FString::Printf(TEXT("Increases the walk speed of enemies by: %.1f"), WalkSpeedIncrease);
  CardType = ECardType::Enemy;
  Rarity = ECardRarity::Common;
}


void UEnemyWalkSpeedCard::ApplyCard(AActor* Target)
{
  if (UWorld* World = Target->GetWorld())
  {
    AGM_DeadPixels* GM = Cast<AGM_DeadPixels>(World->GetAuthGameMode());
    if (GM)
    {
      GM->GlobalEnemyWalkSpeedBonus += WalkSpeedIncrease;
    }
  }
}
