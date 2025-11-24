#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Card.h"
#include "CardWidget.generated.h"

UCLASS()
class DEADPIXELS_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	TSubclassOf<UCard> CardClass;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	UCard* CardInstance;

	UFUNCTION(BlueprintCallable)
	void OnCardClicked();
	
};
