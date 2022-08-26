// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AwkayCase/Inventories/InventoryStructure.h"
#include "AwkayCase/Items/ItemStructure.h"
#include "W_InventoryGeneral.generated.h"

class ACharacterPlayer;

UCLASS()
class AWKAYCASE_API UW_InventoryGeneral : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
		TArray<FInventorySlot> GetInventoryItems();

	UFUNCTION(BlueprintCallable)
		FWidgetInventoryItemWeaponDetails OnHoveredWeaponItem(FName ItemID);

	UFUNCTION(BlueprintCallable)
		bool EquipItem(FName ItemID, EItemCategory ItemCategory, int32 SlotIndex);
	
};
