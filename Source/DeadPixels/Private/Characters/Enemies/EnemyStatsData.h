#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyStatsData.generated.h"

UCLASS()
class DEADPIXELS_API UEnemyStatsData : public UDataAsset
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 3.f;
};
