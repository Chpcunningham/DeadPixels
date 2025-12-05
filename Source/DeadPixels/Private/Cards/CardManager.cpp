//Maxwell Clement

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
TArray<TSubclassOf<UCard>> ACardManager::GetRandomCardChoices(int32 Count, ECardType FilterType)
{
	TArray<TSubclassOf<UCard>> Results;

	TArray<TSubclassOf<UCard>> AllowedCards;

	for (auto CardClass : CardsArray)
	{
		if (!CardClass) continue;

		UCard* DefaultObj = Cast<UCard>(CardClass->GetDefaultObject());
		if (DefaultObj && DefaultObj->GetCardType() == FilterType)
		{
			AllowedCards.Add(CardClass);
		}
	}
	
	if (AllowedCards.Num() == 0) { return Results; }

	for (int i = 0; i < Count; i++)
	{
		ECardRarity Rarity = ChooseRarity();

		TArray<TSubclassOf<UCard>> RarityPool;
		for (auto CardClass : AllowedCards)
		{
			UCard* DefaultObj = Cast<UCard>(CardClass->GetDefaultObject());
			if (DefaultObj && DefaultObj->GetRarity() == Rarity)
			{
				RarityPool.Add(CardClass);
			}
		}

		if (RarityPool.Num() == 0) { RarityPool = AllowedCards; }
		
		int Index = FMath::RandRange(0, RarityPool.Num() - 1);
		Results.Add(RarityPool[Index]);
	}

	return Results;
}
