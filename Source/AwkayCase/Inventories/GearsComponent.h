// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AwkayCase/Items/ItemStructure.h"
#include "GearsComponent.generated.h"

class ACharacterBase;
class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AWKAYCASE_API UGearsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGearsComponent();

protected:
	virtual void BeginPlay() override;

	//virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		TObjectPtr<ACharacterBase> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		TObjectPtr<AWeapon> AttachedWeapon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon Slot")
		FWeaponStructure WeaponSlot1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon Slot")
		FWeaponStructure WeaponSlot2;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Slot")
		int32 CurrentWeaponSlotIndex = 0;

public:	
	UFUNCTION()
		void SetOwnerCharacter(ACharacterBase* Character);

	UFUNCTION()
		void EquipWeapon(FWeaponStructure WeaponData, FName WeaponSlot);

	UFUNCTION()
		void AttachToHand(FWeaponStructure WeaponData);

	UFUNCTION(Server, Reliable)
		void Server_AttachToHand(FWeaponStructure WeaponData);

	UFUNCTION(NetMulticast, Reliable)
		void Multi_AttachToHand(FWeaponStructure WeaponData);

	UFUNCTION()
		AWeapon* GetAttachedWeapon() const { return AttachedWeapon; };

	UFUNCTION()
		void DetachFromHand();

	UFUNCTION()
		void ChooseWeapon(int32 SlotIndex);

	UFUNCTION()
		void SwitchWeaponsInc();

	UFUNCTION()
		void SwitchWeaponsDec();

};
