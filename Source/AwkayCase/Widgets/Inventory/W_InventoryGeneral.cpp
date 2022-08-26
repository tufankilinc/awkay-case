// Fill out your copyright notice in the Description page of Project Settings.


#include "W_InventoryGeneral.h"
#include "Engine/Texture2D.h"
#include "AwkayCase/Characters/CharacterPlayer.h"
#include "AwkayCase/Inventories/InventoryComponent.h"
#include "AwkayCase/Inventories/GearsComponent.h"
#include "AwkayCase/Game/AwkayGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

TArray<FInventorySlot> UW_InventoryGeneral::GetInventoryItems()
{
	TArray<FInventorySlot> InventorySlots;

	TObjectPtr<ACharacterPlayer> Player = Cast<ACharacterPlayer>(GetOwningPlayer()->GetCharacter());

	if (IsValid(Player.Get())) {
		InventorySlots = Player->GetInventoryComponent()->GetInventorySlots();
	}

	return InventorySlots;
}

FWidgetInventoryItemWeaponDetails UW_InventoryGeneral::OnHoveredWeaponItem(FName ItemID)
{
	FWidgetInventoryItemWeaponDetails Response;

	TObjectPtr<UAwkayGameInstance> GameInstance = Cast<UAwkayGameInstance>(GetWorld()->GetGameInstance());

	if (IsValid(GameInstance.Get())) {
		TObjectPtr<ACharacterPlayer> Player = Cast<ACharacterPlayer>(GetOwningPlayer()->GetCharacter());

		if (IsValid(Player.Get())) {
			FItemStructure ItemData = GameInstance->GetBaseItemDataFromList(ItemID);
			FWeaponStructure WeaponData = GameInstance->GetWeaponDataFromList(ItemID);

			if (ItemData.ItemID != NAME_None && WeaponData.ItemID != NAME_None) {
				Response.ItemID = ItemData.ItemID;
				Response.ItemName = ItemData.Title;
				Response.ItemDetail = ItemData.Description;
				Response.ItemThumbnail = Cast<UTexture2D>(UKismetSystemLibrary::LoadAsset_Blocking(ItemData.Thumbnail));
				Response.WeaponDamageRange = FText::FromString(FString::Printf(TEXT("%.2f - %.2f"), WeaponData.MinDamage, WeaponData.MaxDamage));
				Response.WeaponAttackSpeed = FText::FromString(FString::Printf(TEXT("%.2f"), WeaponData.AttackSpeed));
				Response.WeaponValue = FText::FromString(FString::Printf(TEXT("%.2f"), ItemData.StoreValue));
			}
		}
	}

	return Response;
}

bool UW_InventoryGeneral::EquipItem(FName ItemID, EItemCategory ItemCategory, int32 SlotIndex)
{
	bool bSuccess = false;

	TObjectPtr<UAwkayGameInstance> GameInstance = Cast<UAwkayGameInstance>(GetWorld()->GetGameInstance());

	if (IsValid(GameInstance.Get())) {
		TObjectPtr<ACharacterPlayer> Player = Cast<ACharacterPlayer>(GetOwningPlayer()->GetCharacter());

		if (IsValid(Player.Get())) {
			switch (ItemCategory)
			{
				case EItemCategory::Weapon:
				{
					FWeaponStructure WeaponData = GameInstance->GetWeaponDataFromList(ItemID);
					if (WeaponData.ItemID != NAME_None) {
						Player->GetGearsComponent()->EquipWeapon(WeaponData, FName("Slot1"));
						bSuccess = true;
					}
					break;
				}
				default:
					break;
			}
		}
	}

	return bSuccess;
}