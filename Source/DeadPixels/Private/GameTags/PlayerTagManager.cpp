//Connor Cunningham


#include "GameTags/PlayerTagManager.h"

//Movement Tags Defined
UE_DEFINE_GAMEPLAY_TAG(Movement_State_Running, "Movement.State.Running");
void UPlayerTagManager::InitializeNativeTags()
{
	UGameplayTagsManager& TagsManager = UPlayerTagManager::Get();

	TagsManager.AddNativeGameplayTag("Movement.State.Running");
}
