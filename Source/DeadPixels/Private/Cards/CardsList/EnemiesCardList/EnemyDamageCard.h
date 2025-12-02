#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "EnemyDamageCard.generated.h"

UCLASS()
class DEADPIXELS_API UEnemyDamageCard : public UCard
{
	GENERATED_BODY()
public:
	UEnemyDamageCard();

	//virtual void ApplyEnemyCard(UDataAsset* Target) override;
	//virtual void RemoveCard(AActor* Target) override;
	virtual void ApplyCard(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
	float DamageIncrease = 2;
};
