#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "DamageCard.generated.h"

UCLASS()
class ADamageCard : public ACard
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
	float DamageIncrease = 10.f;

	virtual void ApplyCard(AActor* Target) override;
};
