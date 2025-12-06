//Connor Cunningham

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemyBase.h"
#include "SmallZombie.generated.h"

/**
 * 
 */
UCLASS()
class ASmallZombie : public AEnemyBase
{
	GENERATED_BODY()
public:
	ASmallZombie();

	UPROPERTY(EditAnywhere)
	UPaperZDAnimInstance* SmallZombieInstance;
};
