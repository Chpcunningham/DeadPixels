//Maxwell Clement

#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "FireRateCard.generated.h"

UCLASS()
class UFireRateCard : public UCard
{
	GENERATED_BODY()
public:
	UFireRateCard();

	virtual void ApplyCard(AActor* Target) override;
	//virtual void RemoveCard(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Card")
	float FireRateIncrease = 0.2;
};
