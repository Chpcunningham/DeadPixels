#include "FireRateCard.h"
#include "Weapons/Weapons.h"

UFireRateCard::UFireRateCard()
{
	CardName = "Fire rate Boost";
	Description = "Increases your weapon's attack speed.";
	CardType = ECardType::Weapon;
	Rarity = ECardRarity::Rare;
}

void UFireRateCard::ApplyCard(AActor* Target)
{
	if (AWeapons* W = Cast<AWeapons>(Target))
	{
		W->FireRate -= FireRateIncrease;
	}
}