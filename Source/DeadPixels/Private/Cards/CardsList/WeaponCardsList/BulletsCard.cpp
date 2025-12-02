#include "BulletsCard.h"
#include "Weapons/Weapons.h"

UBulletsCard::UBulletsCard()
{
	CardName = "Bullets Boost";
	Description = FString::Printf(TEXT("Increases the number of bullets your gun shoots by: %d"), BulletIncrease);
	CardType = ECardType::Weapon;
	Rarity = ECardRarity::Common;
}

void UBulletsCard::ApplyCard(AActor* Target)
{
	if (AWeapons* W = Cast<AWeapons>(Target))
	{
		W->NumOfBullets += BulletIncrease;
	}
}