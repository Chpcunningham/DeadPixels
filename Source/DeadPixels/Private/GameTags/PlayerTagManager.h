//Connor Cunningham

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsManager.h"
#include "NativeGameplayTags.h"
#include "PlayerTagManager.generated.h"

//MovementTags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_State_Running);
UCLASS()
class UPlayerTagManager : public UGameplayTagsManager
{
	GENERATED_BODY()
public:
	static void InitializeNativeTags();
};
