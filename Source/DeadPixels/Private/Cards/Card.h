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

UCLASS()
class ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	ACard();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Card")
	FString CardName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Card")
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Card")
	ECardType CardType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Card")
	ECardRarity Rarity = ECardRarity::Common;

	virtual void ApplyCard(AActor* Target);

	virtual void RemoveCard(AActor* Target);
	
};
