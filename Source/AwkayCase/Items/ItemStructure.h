#pragma once

#include "Engine/DataTable.h"
#include "AwkayCase/Combat/CombatStructure.h"
#include "ItemStructure.generated.h"

class UTexture2D;
class UStaticMesh;
class USoundCue;

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Weapon			= 0		UMETA(DisplayName = "Weapon")
};

UENUM(BlueprintType)
enum class EItemMaterial : uint8
{
	Wood			= 0		UMETA(DisplayName = "Wood"),
	Stone			= 1		UMETA(DisplayName = "Stone"),
	Iron			= 2		UMETA(DisplayName = "Iron")
};

UENUM(BlueprintType)
enum class EWeaponCategory : uint8
{
	Sword			= 0		UMETA(DisplayName = "Sword"),
	Axe				= 1		UMETA(DisplayName = "Axe"),
	Bow				= 2		UMETA(DisplayName = "Bow"),
};

UENUM(BlueprintType)
enum class EWeaponHolding : uint8
{
	OneHanded		= 0		UMETA(DisplayName = "One Handed"),
	TwoHanded		= 1		UMETA(DisplayName = "Two Handed")
};

UENUM(BlueprintType)
enum class EWeaponRange : uint8
{
	Melee			= 0		UMETA(DisplayName = "Melee Weapon"),
	Ranged			= 1		UMETA(DisplayName = "Ranged Weapon")
};

UENUM(BlueprintType)
enum class EWeaponDamage : uint8
{
	Blunt			= 0		UMETA(DisplayName = "Blunt"),
	Pierce			= 1		UMETA(DisplayName = "Pierce"),
	Cut				= 2		UMETA(DisplayName = "Cut")
};

UENUM(BlueprintType)
enum class EInventorySlotInteraction : uint8
{
	Equip			= 0		UMETA(DisplayName = "Equip")
};

USTRUCT(BlueprintType)
struct FItemStructure : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		FName ItemID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		EItemCategory ItemCategory;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		EItemMaterial ItemMaterial;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		TSubclassOf<AActor> ActorReference;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Description")
		FText Title;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Description")
		FText Description;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Preview")
		TSoftObjectPtr<UTexture2D> Thumbnail;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Preview")
		TSoftObjectPtr<UStaticMesh> StaticMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Storage")
		int32 MaxStackSize;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Storage")
		float Weight;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Definitions")
		EInventorySlotInteraction InSlotInteraction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Definitions")
		float StoreValue;

};

USTRUCT(BlueprintType)
struct FWeaponStructure : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		FName ItemID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		EWeaponCategory WeaponCategory;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		FName AttachTo;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Definitions")
		EWeaponDamage DamageType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Definitions")
		EWeaponRange WeaponRange;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Definitions")
		EWeaponHolding HoldingType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat")
		FNpcCombatableAreaDistances WeaponRelatedCombatDistances;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat")
		float MinDamage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat")
		float MaxDamage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat")
		float AttackSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effects")
		TSoftObjectPtr<USoundCue> AttackSound;

};