//Maxwell Clement

#include "FireRateCard.h"
#include "Weapons/Weapons.h"

UFireRateCard::UFireRateCard()
{
	CardName = "Fire rate Boost";
	Description = FString::Printf(TEXT("Increases your weapon's attack speed by: %.1f"), FireRateIncrease);
	CardType = ECardType::Weapon;
	Rarity = ECardRarity::Common;
}

void UFireRateCard::ApplyCard(AActor* Target)
{
	if (AWeapons* W = Cast<AWeapons>(Target))
	{
		W->FireRate -= FireRateIncrease;
	}
}