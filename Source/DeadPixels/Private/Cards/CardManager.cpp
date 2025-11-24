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

TArray<TSubclassOf<UCard>> ACardManager::GetCardsByRarity(ECardRarity Rarity)
{
	TArray<TSubclassOf<UCard>> Result;
	for (auto CardClass : CardsArray)
	{
		if (!CardClass) continue;
		UCard* DefaultObj = Cast<UCard>(CardClass->GetDefaultObject());
		
		if (DefaultObj && DefaultObj->GetRarity() == Rarity)
			Result.Add(CardClass);
	}
	return Result;
}
TArray<TSubclassOf<UCard>> ACardManager::GetRandomCardChoices(int32 Count)
{
	TArray<TSubclassOf<UCard>> Results;

	for (int i = 0; i < Count; i++)
	{
		ECardRarity Rarity = ChooseRarity();
		TArray<TSubclassOf<UCard>> Pool = GetCardsByRarity(Rarity);

		if (Pool.Num() == 0)
			Pool = CardsArray;

		int Index = FMath::RandRange(0, Pool.Num() - 1);
		Results.Add(Pool[Index]);
	}

	return Results;
}

/*
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
}*/
