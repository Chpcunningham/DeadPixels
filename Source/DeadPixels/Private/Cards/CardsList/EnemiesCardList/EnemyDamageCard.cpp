#include "EnemyDamageCard.h"
#include "Characters/Enemies/EnemyBase.h"
#include "Characters/Enemies/EnemyStatsData.h"

UEnemyDamageCard::UEnemyDamageCard()
{
	CardName = "Enemy Damage Boost";
	Description = FString::Printf(TEXT("Increases the damage of the enemy by: %.1f"), DamageIncrease);
	CardType = ECardType::Enemy;
	Rarity = ECardRarity::Common;
}

void UEnemyDamageCard::ApplyCard(AActor* Target)
{
	AEnemyBase* EnemyActor = Cast<AEnemyBase>(Target);
	if (!EnemyActor)
		return;
	
	if (UEnemyStatsData* Stats = EnemyActor->Stats)
	{
		Stats->Damage += DamageIncrease;
		
	}
}