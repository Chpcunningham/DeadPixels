#include "Card.h"

ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACard::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACard::ApplyCard(AActor* Target)
{
	//This does nothing, the children override this
}

void ACard::RemoveCard(AActor* Target)
{
	//Optional (In case we want to have the ability to remove a card)
}

