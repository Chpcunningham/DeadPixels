#include "DamageCard.h"
#include "Weapons/Weapons.h"

ADamageCard::ADamageCard()
{
	CardName = "Damage Boost";
	Description = "Increases your weapon damage.";
	CardType = ECardType::Weapon;
	Rarity = ECardRarity::Rare;
}

void ADamageCard::ApplyCard(AActor* Target)
{
	AWeapons* W = Cast<AWeapons>(Target);
	if (W)
	{
		W->Damage += DamageIncrease;
	}
}