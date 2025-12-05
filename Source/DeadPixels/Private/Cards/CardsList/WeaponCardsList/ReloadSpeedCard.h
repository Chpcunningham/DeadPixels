//Maxwell Clement

#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "ReloadSpeedCard.generated.h"

UCLASS()
class UReloadSpeedCard : public UCard
{
	GENERATED_BODY()
public:
	UReloadSpeedCard();

	virtual void ApplyCard(AActor* Target) override;
	//virtual void RemoveCard(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Card")
	float ReloadSpeedIncrease = 0.1;
};
