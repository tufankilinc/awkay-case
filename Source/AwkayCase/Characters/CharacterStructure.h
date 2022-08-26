#pragma once

#include "Engine/DataTable.h"
#include "CharacterStructure.generated.h"

class ACharacterBase;
class USkeletalMesh;

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Player				= 0		UMETA(DisplayName = "Player"),
	NormalNpc			= 1		UMETA(DisplayName = "Normal Npc"),
	BossNpc				= 2		UMETA(DisplayName = "Boss Npc")
};

USTRUCT(BlueprintType)
struct FCharacterProperty
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float BaseValue = 0.f;

	/*UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float ValueToAdd = 0.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float ValueToMultiply = 1.f;*/

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float FinalValue = 0.f;
};

USTRUCT(BlueprintType)
struct FCharacterPropertyData : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		FName PropertiesID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
		FCharacterProperty Health;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
		FCharacterProperty DamageResistance;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
		FCharacterProperty AttackDamage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
		FCharacterProperty AttackSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
		FCharacterProperty MovementSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
		FCharacterProperty JumpHeight;

};

USTRUCT(BlueprintType)
struct FCharacterRewardSetData : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		FName RewardSetID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FName ItemID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float Token = 0.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float Experience = 0.f;

};

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		FName CharacterID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		TSubclassOf<ACharacterBase> CharacterReference;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		ECharacterType CharacterType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Description")
		FText CharacterName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Description")
		FText Description;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Preview")
		TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "References")
		FName PropertiesID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "References")
		FName GearSetID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "References")
		FName RewardSetID;

};