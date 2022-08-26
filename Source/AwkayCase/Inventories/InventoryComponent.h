// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryStructure.h"
#include "AwkayCase/Items/ItemStructure.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AWKAYCASE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TArray<FInventorySlot> Slots;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float AcceptableWeight = 30.f;

public:
	UFUNCTION()
		TArray<FInventorySlot> GetInventorySlots() const { return Slots; };

	UFUNCTION()
		void AddItemToInventory(FItemStructure ItemData, int32 Quantity);

	UFUNCTION()
		bool RemoveItemFromInventory(FName ItemID, int32 Quantity);

	UFUNCTION()
		int32 FindItemQuantity(FName ItemID);

};
