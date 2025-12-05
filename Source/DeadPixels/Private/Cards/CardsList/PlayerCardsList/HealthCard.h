//Maxwell Clement

#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "HealthCard.generated.h"

UCLASS()
class UHealthCard : public UCard
{
	GENERATED_BODY()
public:
	UHealthCard();

	virtual void ApplyCard(AActor* Target) override;
	//virtual void RemoveCard(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
	float HealthIncrease = 50;
};
