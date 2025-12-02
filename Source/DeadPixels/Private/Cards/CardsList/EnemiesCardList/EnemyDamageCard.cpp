#include "EnemyDamageCard.h"
#include "Characters/Enemies/EnemyBase.h"
#include "Characters/Enemies/EnemyStatsData.h"
#include "GameMode/GM_DeadPixels.h"

UEnemyDamageCard::UEnemyDamageCard() {
  CardName = "Enemy Damage Boost";
  Description = FString::Printf(
      TEXT("Increases the damage of the enemy by: %.1f"), DamageIncrease);
  CardType = ECardType::Enemy;
  Rarity = ECardRarity::Common;
}
/*
void UEnemyDamageCard::ApplyEnemyCard(UDataAsset *Target)
{
  UE_LOG(LogTemp, Warning, TEXT("ApplyEnemyCard called with DataAsset: %s"),
        Target ? *Target->GetName() : TEXT("NULL"));
  
    if (UEnemyStatsData *Stats = Cast<UEnemyStatsData>(Target))
    {
      Stats->Damage += DamageIncrease;
    }
}
*/
void UEnemyDamageCard::ApplyCard(AActor* Target)
{
  if (UWorld* World = Target->GetWorld())
  {
    AGM_DeadPixels* GM = Cast<AGM_DeadPixels>(World->GetAuthGameMode());
    if (GM)
    {
      GM->GlobalEnemyDamageBonus += DamageIncrease;
    }
  }
}