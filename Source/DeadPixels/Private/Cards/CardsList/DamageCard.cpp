#include "DamageCard.h"
#include "Weapons/Weapons.h"

ADamageCard::ADamageCard()
{
	CardName = "Damage Boost";
	Description = "Increases weapon damage by 10";
	CardType = ECardType::Weapon;
	Rarity = ECardRarity::Common;
}

void ADamageCard::ApplyCard(AActor* Target)
{
	AWeapons* Weapon = Cast<AWeapons>(Target);
	if (!Weapon) return;

	Weapon->Damage += DamageIncrease;
}