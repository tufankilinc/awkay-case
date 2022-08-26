// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AwkayCase/Characters/CharacterStructure.h"
#include "AwkayCase/Inventories/InventoryStructure.h"
#include "AwkayCase/Items/ItemStructure.h"
#include "AwkayGameInstance.generated.h"

class UDataTable;

UCLASS()
class AWKAYCASE_API UAwkayGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Data Tables")
		TSoftObjectPtr<UDataTable> CharacterDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Data Tables")
		TSoftObjectPtr<UDataTable> CharacterPropertyDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Data Tables")
		TSoftObjectPtr<UDataTable> BaseItemDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Data Tables")
		TSoftObjectPtr<UDataTable> WeaponDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Data Tables")
		TSoftObjectPtr<UDataTable> GearSetDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Data Tables")
		TSoftObjectPtr<UDataTable> RewardSetDataTable;

public:
	UFUNCTION(BlueprintCallable)
		FCharacterData GetCharacterDataFromList(FName ID);

	UFUNCTION(BlueprintCallable)
		FCharacterPropertyData GetCharacterPropertyDataFromList(FName ID);

	UFUNCTION(BlueprintCallable)
		FItemStructure GetBaseItemDataFromList(FName ID);

	UFUNCTION(BlueprintCallable)
		FWeaponStructure GetWeaponDataFromList(FName ID);

	UFUNCTION(BlueprintCallable)
		FGearSetData GetGearSetDataFromList(FName ID);

	UFUNCTION(BlueprintCallable)
		FCharacterRewardSetData GetRewardSetDataFromList(FName ID);

};
