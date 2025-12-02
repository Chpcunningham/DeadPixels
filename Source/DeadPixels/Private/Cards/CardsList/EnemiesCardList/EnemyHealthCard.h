#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "EnemyHealthCard.generated.h"

UCLASS()
class DEADPIXELS_API UEnemyHealthCard : public UCard
{
	GENERATED_BODY()
public:
	UEnemyHealthCard();

	virtual void ApplyCard(AActor* Target) override;
	//virtual void RemoveCard(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
	float HealthIncrease = 20;
};
