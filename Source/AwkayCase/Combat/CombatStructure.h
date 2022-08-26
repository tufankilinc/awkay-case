#pragma once

#include "CombatStructure.generated.h"

UENUM(BlueprintType)
enum class ECombatMode : uint8
{
	MeleeCombat				= 0		UMETA(DisplayName = "Melee Combat"),
	RangedCombat			= 1		UMETA(DisplayName = "Ranged Combat")
};

UENUM(BlueprintType)
enum class ECombatTriggerClick : uint8
{
	Press					= 0		UMETA(DisplayName = "Press"),
	Pulse					= 1		UMETA(DisplayName = "Pulse"),
	Hold					= 2		UMETA(DisplayName = "Hold")
};

USTRUCT(BlueprintType)
struct FCombatMontageStructure
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		TObjectPtr<UAnimMontage> AnimationMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Properties")
		float PlayRate;

};

USTRUCT(BlueprintType)
struct FNpcCombatableAreaDistances
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float SafeDistance;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float HoldingDistance;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float CombatDistance;

};

UENUM(BlueprintType)
enum class EHandedWeaponType : uint8
{
	OneHandedSword			= 0		UMETA(DisplayName = "One Handed Sword"),
	TwoHandedSword			= 1		UMETA(DisplayName = "Two Handed Sword"),
	NoHandedWeapon			= 2		UMETA(DisplayName = "No Handed Weapon")
};

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Front					= 0		UMETA(DisplayName = "Front"),
	Back					= 1		UMETA(DisplayName = "Back"),
	Left					= 2		UMETA(DisplayName = "Left"),
	Right					= 3		UMETA(DisplayName = "Right")
};