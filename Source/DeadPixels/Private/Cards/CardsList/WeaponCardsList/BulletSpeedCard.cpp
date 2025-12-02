#include "BulletSpeedCard.h"
#include "Weapons/Weapons.h"

UBulletSpeedCard::UBulletSpeedCard()
{
	CardName = "Bullet Speed Boost";
	Description = FString::Printf(TEXT("Increases the speed of your bullets by: %d"), BulletSpeedIncrease);
	CardType = ECardType::Weapon;
	Rarity = ECardRarity::Common;
}

void UBulletSpeedCard::ApplyCard(AActor* Target)
{
	if (AWeapons* W = Cast<AWeapons>(Target))
	{
		W->BulletSpeed += BulletSpeedIncrease;
	}
}