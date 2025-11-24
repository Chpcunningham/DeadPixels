#include "CardManager.h"

ACardManager::ACardManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACardManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACardManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ECardRarity ACardManager::ChooseRarity()
{
	float TotalWeight = CommonWeight + UncommonWeight + RareWeight + EpicWeight + LegendaryWeight;
	float RandomValue = FMath::FRand() * TotalWeight;

	if (RandomValue < CommonWeight)
		return ECardRarity::Common;

	RandomValue -= CommonWeight;
	if (RandomValue < UncommonWeight)
		return ECardRarity::Uncommon;

	RandomValue -= UncommonWeight;
	if (RandomValue < RareWeight)
		return ECardRarity::Rare;

	RandomValue -= RareWeight;
	if (RandomValue < EpicWeight)
		return ECardRarity::Epic;

	return ECardRarity::Legendary;
}

TArray<TSubclassOf<ACard>> ACardManager::GetCardsByRarity(ECardRarity Rarity)
{
	TArray<TSubclassOf<ACard>> Result;
	for (auto CardClass : CardsArray)
	{
		if (!CardClass) continue;
		ACard* DefaultObj = Cast<ACard>(CardClass->GetDefaultObject());
		if (DefaultObj && DefaultObj->Rarity == Rarity)
			Result.Add(CardClass);
	}
	return Result;
}

ACard* ACardManager::GiveRandomCard(AActor* Target)
{
	ECardRarity SelectedRarity = ChooseRarity();
	TArray<TSubclassOf<ACard>> Pool = GetCardsByRarity(SelectedRarity);
	if (Pool.Num() == 0)
		Pool = GetCardsByRarity(ECardRarity::Common);
	if (Pool.Num() == 0) return nullptr;

	int Index = FMath::RandRange(0, Pool.Num() - 1);
	ACard* SpawnedCard = GetWorld()->SpawnActor<ACard>(Pool[Index]);
	if (SpawnedCard)
		SpawnedCard->ApplyCard(Target);

	return SpawnedCard;
}
