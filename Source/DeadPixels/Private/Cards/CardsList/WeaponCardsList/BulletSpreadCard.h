//Maxwell Clement

#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "BulletSpreadCard.generated.h"

UCLASS()
class UBulletSpreadCard : public UCard
{
	GENERATED_BODY()
public:
	UBulletSpreadCard();

	virtual void ApplyCard(AActor* Target) override;
	//virtual void RemoveCard(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
	int BulletSpreadDecrease = 10;
};
