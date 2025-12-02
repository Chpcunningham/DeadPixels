#include "EnemyHealthCard.h"

#include "Characters/Enemies/EnemyBase.h"
#include "Characters/Enemies/EnemyStatsData.h"
#include "Components/HealthComponent.h"

UEnemyHealthCard::UEnemyHealthCard()
{
	CardName = "Enemy Health Boost";
	Description = FString::Printf(TEXT("Increases the health of the enemy by: %.1f"), HealthIncrease);
	CardType = ECardType::Enemy;
	Rarity = ECardRarity::Common;
}

void UEnemyHealthCard::ApplyCard(AActor* Target)
{
	AEnemyBase* EnemyActor = Cast<AEnemyBase>(Target);
	if (!EnemyActor)
		return;
	
	if (UEnemyStatsData* Stats = EnemyActor->Stats)
	{
		Stats->MaxHealth += HealthIncrease;
	}
}