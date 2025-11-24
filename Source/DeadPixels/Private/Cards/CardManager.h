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

	UCard* GiveRandomCard(AActor* Target);
	
	ECardRarity ChooseRarity();
	
	TArray<TSubclassOf<UCard>> GetCardsByRarity(ECardRarity Rarity);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UCard>> CardsArray;

	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<UCard>> GetRandomCardChoices(int32 Count);

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
