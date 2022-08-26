// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AwkayPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AWKAYCASE_API AAwkayPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
		bool bIsBackpackDisplaying = false;

	UFUNCTION(BlueprintImplementableEvent)
		void ToggleBackpack_Implementation();

public:
	UFUNCTION()
		void ToggleBackpackWidget();

};
