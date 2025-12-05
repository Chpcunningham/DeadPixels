//Maxwell Clement

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Card")
	FString CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Card")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Card")
	ECardType CardType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Card")
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

	UFUNCTION(BlueprintCallable)
	virtual void ApplyCard(AActor* Target);

	UFUNCTION(BlueprintCallable)
	virtual void ApplyEnemyCard(UDataAsset* Target);

	UFUNCTION(BlueprintCallable)
	virtual void RemoveCard(AActor* Target);
	
};
