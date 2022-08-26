// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UInventoryComponent::AddItemToInventory(FItemStructure ItemData, int32 Quantity)
{
	int32 PickupQuantity = Quantity;

	if (ItemData.MaxStackSize != 1) {
		for (int32 i = 0; i < Slots.Num(); i++) {
			if (Slots[i].ItemData.ItemID == ItemData.ItemID) {
				if (Slots[i].Quantity < Slots[i].ItemData.MaxStackSize) {
					if (Slots[i].Quantity + PickupQuantity >= Slots[i].ItemData.MaxStackSize) {
						PickupQuantity = Slots[i].Quantity + PickupQuantity - Slots[i].ItemData.MaxStackSize;
						Slots[i].Quantity = Slots[i].ItemData.MaxStackSize;

						if (PickupQuantity <= 0) break;
					}
					else {
						Slots[i].Quantity += PickupQuantity;
						PickupQuantity = 0;
						break;
					}
				}
			}
		}
	}

	if (PickupQuantity > 0) {
		FInventorySlot Slot;

		Slot.ItemData = ItemData;
		Slot.Quantity = PickupQuantity;

		Slots.Add(Slot);
	}
}

bool UInventoryComponent::RemoveItemFromInventory(FName ItemID, int32 Quantity)
{
	bool bSuccess = false;
	int32 DescentCount = Quantity;

	for (int32 i = 0; i < Slots.Num(); i++) {
		if (Slots[i].ItemData.ItemID == ItemID) {
			if (Slots[i].Quantity - DescentCount > 0) {
				Slots[i].Quantity -= DescentCount;
				bSuccess = true;
				break;
			}
			else if (Slots[i].Quantity - DescentCount < 0) {
				DescentCount = DescentCount - Slots[i].Quantity;
				Slots.RemoveAt(i);
			}
			else if (Slots[i].Quantity - DescentCount == 0) {
				DescentCount = 0;
				Slots.RemoveAt(i);
				bSuccess = true;
				break;
			}
		}
	}

	return bSuccess;
}

int32 UInventoryComponent::FindItemQuantity(FName ItemID)
{
	int32 Total = 0;

	for (int32 i = 0; i < Slots.Num(); i++) {
		if (Slots[i].ItemData.ItemID == ItemID) {
			Total += Slots[i].Quantity;
		}
	}

	return Total;
}
