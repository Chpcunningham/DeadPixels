//Maxwell Clement

#include "ReloadSpeedCard.h"
#include "Weapons/Weapons.h"

UReloadSpeedCard::UReloadSpeedCard()
{
	CardName = "Reload Speed Boost";
	Description = FString::Printf(TEXT("Increases your weapon's reload speed by: %.1f"), ReloadSpeedIncrease);
	CardType = ECardType::Weapon;
	Rarity = ECardRarity::Common;
}

void UReloadSpeedCard::ApplyCard(AActor* Target)
{
	if (AWeapons* W = Cast<AWeapons>(Target))
	{
		W->ReloadRate -= ReloadSpeedIncrease;
	}
}