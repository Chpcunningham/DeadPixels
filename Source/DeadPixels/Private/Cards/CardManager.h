#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.h"
#include "CardManager.generated.h"

UCLASS()
class ACardManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACardManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	ACard* GiveRandomCard(AActor* Target);
	
	ECardRarity ChooseRarity();
	
	TArray<TSubclassOf<ACard>> GetCardsByRarity(ECardRarity Rarity);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ACard>> CardsArray;

	UPROPERTY(EditAnywhere, Category="Rarity Weights")
	float CommonWeight = 70.f;

	UPROPERTY(EditAnywhere, Category="Rarity Weights")
	float UncommonWeight = 20.f;

	UPROPERTY(EditAnywhere, Category="Rarity Weights")
	float RareWeight = 7.f;

	UPROPERTY(EditAnywhere, Category="Rarity Weights")
	float EpicWeight = 2.5f;

	UPROPERTY(EditAnywhere, Category="Rarity Weights")
	float LegendaryWeight = 0.5f;
	

};
