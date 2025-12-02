#include "EnemyHealthCard.h"

#include "Characters/Enemies/EnemyBase.h"
#include "Characters/Enemies/EnemyStatsData.h"
#include "Components/HealthComponent.h"
#include "GameMode/GM_DeadPixels.h"

UEnemyHealthCard::UEnemyHealthCard()
{
	CardName = "Enemy Health Boost";
	Description = FString::Printf(TEXT("Increases the health of the enemy by: %.1f"), HealthIncrease);
	CardType = ECardType::Enemy;
	Rarity = ECardRarity::Common;
}


void UEnemyHealthCard::ApplyCard(AActor* Target)
{
	if (UWorld* World = Target->GetWorld())
	{
		AGM_DeadPixels* GM = Cast<AGM_DeadPixels>(World->GetAuthGameMode());
		if (GM)
		{
			GM->GlobalEnemyHealthBonus += HealthIncrease;
		}
	}
}

/*
void UEnemyHealthCard::ApplyEnemyCard(UDataAsset* Target)
{
	
	if (UEnemyStatsData* Stats = Cast<UEnemyStatsData>(Target))
	{
		Stats->MaxHealth += HealthIncrease;
	}
}
*/

