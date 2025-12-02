#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "BulletSpeedCard.generated.h"

UCLASS()
class UBulletSpeedCard : public UCard
{
	GENERATED_BODY()
public:
	UBulletSpeedCard();

	virtual void ApplyCard(AActor* Target) override;
	//virtual void RemoveCard(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
	int BulletSpeedIncrease = 50;
};
