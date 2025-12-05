//Maxwell Clement

#include "HealthCard.h"
#include "Characters/Player/MainCharacter.h"
#include "Components/HealthComponent.h"

UHealthCard::UHealthCard()
{
	CardName = "Health Boost";
	Description = FString::Printf(TEXT("Increases the health of the player by: %.1f"), HealthIncrease);
	CardType = ECardType::Player;
	Rarity = ECardRarity::Common;
}

void UHealthCard::ApplyCard(AActor* Target)
{
	if (AMainCharacter* Player = Cast<AMainCharacter>(Target))
	{
		Player->HealthComp->MaxHealth += HealthIncrease;
		Player->HealthComp->CurrentHealth += HealthIncrease;
	}
}