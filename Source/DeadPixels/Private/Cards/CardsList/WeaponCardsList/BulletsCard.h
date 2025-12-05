//Maxwell Clement

#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "BulletsCard.generated.h"

UCLASS()
class UBulletsCard : public UCard
{
	GENERATED_BODY()
public:
	UBulletsCard();

	virtual void ApplyCard(AActor* Target) override;
	//virtual void RemoveCard(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
	int BulletIncrease = 2;
};
