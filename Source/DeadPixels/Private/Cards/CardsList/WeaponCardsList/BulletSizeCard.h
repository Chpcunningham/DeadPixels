//Maxwell Clement

#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "BulletSizeCard.generated.h"

UCLASS()
class UBulletSizeCard : public UCard
{
	GENERATED_BODY()
public:
	UBulletSizeCard();

	virtual void ApplyCard(AActor* Target) override;
	//virtual void RemoveCard(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
	float BulletSizeIncrease = 0.5f;
};
