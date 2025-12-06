//Maxwell Clement

#pragma once

#include "Cards/Card.h"
#include "CoreMinimal.h"
#include "EnemyWalkSpeedCard.generated.h"

UCLASS()
class DEADPIXELS_API UEnemyWalkSpeedCard : public UCard {
  GENERATED_BODY()

public:
  UEnemyWalkSpeedCard();

  virtual void ApplyCard(AActor* Target) override;

protected:
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card")
  float WalkSpeedIncrease = 20;
};
