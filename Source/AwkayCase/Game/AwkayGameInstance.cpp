// Fill out your copyright notice in the Description page of Project Settings.


#include "AwkayGameInstance.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetSystemLibrary.h"

FCharacterData UAwkayGameInstance::GetCharacterDataFromList(FName ID)
{
	FCharacterData CharacterData;

	if (ID != NAME_None) {
		TObjectPtr<UDataTable> LoadedDataTable = Cast<UDataTable>(UKismetSystemLibrary::LoadAsset_Blocking(CharacterDataTable));
		if (IsValid(LoadedDataTable)) {
			CharacterData = *LoadedDataTable->FindRow<FCharacterData>(ID, "");
		}
	}

	return CharacterData;
}

FCharacterPropertyData UAwkayGameInstance::GetCharacterPropertyDataFromList(FName ID)
{
	FCharacterPropertyData CharacterPropertyData;

	if (ID != NAME_None) {
		TObjectPtr<UDataTable> LoadedDataTable = Cast<UDataTable>(UKismetSystemLibrary::LoadAsset_Blocking(CharacterPropertyDataTable));
		if (IsValid(LoadedDataTable)) {
			CharacterPropertyData = *LoadedDataTable->FindRow<FCharacterPropertyData>(ID, "");

			CharacterPropertyData.Health.FinalValue = CharacterPropertyData.Health.BaseValue;
			CharacterPropertyData.AttackDamage.FinalValue = CharacterPropertyData.AttackDamage.BaseValue;
			CharacterPropertyData.AttackSpeed.FinalValue = CharacterPropertyData.AttackSpeed.BaseValue;
			CharacterPropertyData.DamageResistance.FinalValue = CharacterPropertyData.DamageResistance.BaseValue;
			CharacterPropertyData.MovementSpeed.FinalValue = CharacterPropertyData.MovementSpeed.BaseValue;
			CharacterPropertyData.JumpHeight.FinalValue = CharacterPropertyData.JumpHeight.BaseValue;
		}
	}

	return CharacterPropertyData;
}

FItemStructure UAwkayGameInstance::GetBaseItemDataFromList(FName ID)
{
	FItemStructure ItemData;

	if (ID != NAME_None) {
		TObjectPtr<UDataTable> LoadedDataTable = Cast<UDataTable>(UKismetSystemLibrary::LoadAsset_Blocking(BaseItemDataTable));
		if (IsValid(LoadedDataTable)) {
			ItemData = *LoadedDataTable->FindRow<FItemStructure>(ID, "");
		}
	}

	return ItemData;
}

FWeaponStructure UAwkayGameInstance::GetWeaponDataFromList(FName ID)
{
	FWeaponStructure WeaponData;

	if (ID != NAME_None) {
		TObjectPtr<UDataTable> LoadedDataTable = Cast<UDataTable>(UKismetSystemLibrary::LoadAsset_Blocking(WeaponDataTable));
		if (IsValid(LoadedDataTable)) {
			WeaponData = *LoadedDataTable->FindRow<FWeaponStructure>(ID, "");
		}
	}

	return WeaponData;
}

FGearSetData UAwkayGameInstance::GetGearSetDataFromList(FName ID)
{
	FGearSetData GearSetData;

	if (ID != NAME_None) {
		TObjectPtr<UDataTable> LoadedDataTable = Cast<UDataTable>(UKismetSystemLibrary::LoadAsset_Blocking(GearSetDataTable));
		if (IsValid(LoadedDataTable)) {
			GearSetData = *LoadedDataTable->FindRow<FGearSetData>(ID, "");
		}
	}

	return GearSetData;
}

FCharacterRewardSetData UAwkayGameInstance::GetRewardSetDataFromList(FName ID)
{
	FCharacterRewardSetData RewardSetData;

	if (ID != NAME_None) {
		TObjectPtr<UDataTable> LoadedDataTable = Cast<UDataTable>(UKismetSystemLibrary::LoadAsset_Blocking(RewardSetDataTable));
		if (IsValid(LoadedDataTable)) {
			RewardSetData = *LoadedDataTable->FindRow<FCharacterRewardSetData>(ID, "");
		}
	}

	return RewardSetData;
}
