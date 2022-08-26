#pragma once

#include "Engine/DataTable.h"
#include "AwkayCase/Items/ItemStructure.h"
#include "InventoryStructure.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FGearSetData : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		FName GearSetID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Gears")
		FName Slot1WeaponID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Gears")
		FName Slot2WeaponID;

};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FItemStructure ItemData;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		int32 Quantity;

};

USTRUCT(BlueprintType)
struct FPickupResponse
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FItemStructure ItemData;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		int32 Quantity;

};

USTRUCT(BlueprintType)
struct FStackOperationResponse
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		bool bStackFound = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		int32 Quantity;
};

USTRUCT(BlueprintType)
struct FWidgetInventoryItemWeaponDetails
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FName ItemID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FText ItemName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FText ItemDetail;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TObjectPtr<UTexture2D> ItemThumbnail;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FText WeaponDamageRange;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FText WeaponAttackSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FText WeaponValue;

};