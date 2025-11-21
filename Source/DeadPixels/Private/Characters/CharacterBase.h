// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "CharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	ACharacterBase();
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UBoxComponent* HurtBox;
};
