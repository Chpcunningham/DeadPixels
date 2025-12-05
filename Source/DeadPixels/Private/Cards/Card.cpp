//Maxwell Clement

#include "Card.h"

void UCard::ApplyCard(AActor* Target)
{
	//This does nothing, the children override this
}

void UCard::ApplyEnemyCard(UDataAsset* Target) 
{
	//This is for the enemy class
}

void UCard::RemoveCard(AActor* Target)
{
	//Optional (In case we want to have the ability to remove a card)
}

