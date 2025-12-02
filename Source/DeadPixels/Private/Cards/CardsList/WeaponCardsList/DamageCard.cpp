#include "DamageCard.h"
#include "Weapons/Weapons.h"

UDamageCard::UDamageCard()
{
	CardName = "Damage Boost";
	Description = FString::Printf(TEXT("Increases the number of bullets your gun shoots by: %.1f"), DamageIncrease);
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