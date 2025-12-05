//Maxwell Clement

#include "WalkSpeedCard.h"
#include "Characters/Player/MainCharacter.h"

UWalkSpeedCard::UWalkSpeedCard()
{
	CardName = "Walkspeed Boost";
	Description = FString::Printf(TEXT("Increases the walk speed of the player by: %.1f"), WalkSpeedIncrease);
	CardType = ECardType::Player;
	Rarity = ECardRarity::Common;
}

void UWalkSpeedCard::ApplyCard(AActor* Target)
{
	if (AMainCharacter* Player = Cast<AMainCharacter>(Target))
	{
		Player->WalkSpeed += WalkSpeedIncrease;
	}
}