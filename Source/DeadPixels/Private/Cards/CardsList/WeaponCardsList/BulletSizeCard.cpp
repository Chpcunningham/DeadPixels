//Maxwell Clement

#include "BulletSizeCard.h"
#include "Weapons/Weapons.h"

UBulletSizeCard::UBulletSizeCard()
{
	CardName = "Bullet Size Boost";
	Description = FString::Printf(TEXT("Increases the size of your bullets  by: %.1f"), BulletSizeIncrease);
	CardType = ECardType::Weapon;
	Rarity = ECardRarity::Common;
}

void UBulletSizeCard::ApplyCard(AActor* Target)
{
	if (AWeapons* W = Cast<AWeapons>(Target))
	{
		W->BulletSize += BulletSizeIncrease;
	}
}