#include "DamageCard.h"
#include "Weapons/Weapons.h"

UDamageCard::UDamageCard()
{
	CardName = "Damage Boost";
	Description = "Increases your weapon damage by : {DamageIncrease}";
	CardType = ECardType::Weapon;
	Rarity = ECardRarity::Common;
}

void UDamageCard::ApplyCard(AActor* Target)
{
	AWeapons* W = Cast<AWeapons>(Target);
	if (W)
	{
		W->Damage += DamageIncrease;
	}
}