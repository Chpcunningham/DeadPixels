#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

UENUM(BlueprintType)
enum class ECardType : uint8
{
	Player,
	Weapon,
	Enemy,
	Global
};

UENUM(BlueprintType)
enum class ECardRarity : uint8
{
	Common,
	Uncommon,
	Rare,
	Epic,
	Legendary
};

UCLASS(Blueprintable, BlueprintType)
class DEADPIXELS_API UCard : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Card")
	FString CardName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Card")
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Card")
	ECardType CardType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Card")
	ECardRarity Rarity = ECardRarity::Common;
	
public:	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetCardName() const { return CardName; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetDescription() const { return Description; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ECardType GetCardType() const { return CardType; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ECardRarity GetRarity() const { return Rarity; }
	
	virtual void ApplyCard(AActor* Target);

	virtual void RemoveCard(AActor* Target);
	
};
