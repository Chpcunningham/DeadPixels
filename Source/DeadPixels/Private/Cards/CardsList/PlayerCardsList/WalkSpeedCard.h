//Maxwell Clement

#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "WalkSpeedCard.generated.h"

UCLASS()
class UWalkSpeedCard : public UCard
{
	GENERATED_BODY()
public:
	UWalkSpeedCard();

	virtual void ApplyCard(AActor* Target) override;
	//virtual void RemoveCard(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
	float WalkSpeedIncrease = 50;
};
