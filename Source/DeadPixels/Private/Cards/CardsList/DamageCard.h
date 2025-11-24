#pragma once

#include "CoreMinimal.h"
#include "Cards/Card.h"
#include "DamageCard.generated.h"

UCLASS()
class ADamageCard : public ACard
{
	GENERATED_BODY()

	public:
		ADamageCard();

		virtual void ApplyCard(AActor* Target) override;
		//virtual void RemoveCard(AActor* Target) override;

	protected:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
		float DamageIncrease = 10.f;
};
