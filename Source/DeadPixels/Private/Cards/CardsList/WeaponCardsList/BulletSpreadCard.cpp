//Maxwell Clement

#include "BulletSpreadCard.h"
#include "Weapons/Weapons.h"

UBulletSpreadCard::UBulletSpreadCard()
{
	CardName = "Bullets Spread Boost";
	Description = FString::Printf(TEXT("Decreases the spread of your bullets (If you shoot more than 1 bullet) by: %d"), BulletSpreadDecrease);
	CardType = ECardType::Weapon;
	Rarity = ECardRarity::Common;
}

void UBulletSpreadCard::ApplyCard(AActor* Target)
{
	if (AWeapons* W = Cast<AWeapons>(Target))
	{
		W->BulletSpread -= BulletSpreadDecrease;
	}
}