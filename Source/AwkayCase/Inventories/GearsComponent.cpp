// Fill out your copyright notice in the Description page of Project Settings.


#include "GearsComponent.h"
#include "AwkayCase/Characters/CharacterBase.h"
#include "AwkayCase/Characters/CharacterPlayer.h"
#include "AwkayCase/Items/Weapon.h"
#include "AwkayCase/States/StateManagerComponent.h"
#include "AwkayCase/Combat/CombatManagerComponent.h"
#include "AwkayCase/Game/AwkayGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UGearsComponent::UGearsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UGearsComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

//void UGearsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME_CONDITION_NOTIFY(UGearsComponent, bAttachedWeaponChanged, COND_SkipOwner, REPNOTIFY_Always);
//}

void UGearsComponent::SetOwnerCharacter(ACharacterBase* Character)
{
	if (Character != nullptr) {
		OwnerCharacter = Character;
	}
}

void UGearsComponent::EquipWeapon(FWeaponStructure WeaponData, FName WeaponSlot)
{
	if (WeaponData.ItemID != NAME_None) {
		if (WeaponSlot == "Slot1") {
			WeaponSlot1 = WeaponData;
		}
		else if (WeaponSlot == "Slot2") {
			WeaponSlot2 = WeaponData;
		}
	}
}

void UGearsComponent::AttachToHand(FWeaponStructure WeaponData)
{
	if (OwnerCharacter->GetLocalRole() < ROLE_Authority) {
		Server_AttachToHand(WeaponData);
	}
	else {
		Multi_AttachToHand(WeaponData);
	}
}

void UGearsComponent::Server_AttachToHand_Implementation(FWeaponStructure WeaponData)
{
	Multi_AttachToHand(WeaponData);
}

void UGearsComponent::Multi_AttachToHand_Implementation(FWeaponStructure WeaponData)
{
	if (WeaponData.ItemID != NAME_None) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		TObjectPtr<UAwkayGameInstance> GameInstance = Cast<UAwkayGameInstance>(GetWorld()->GetGameInstance());

		if (!IsValid(GameInstance.Get())) return;

		FItemStructure ItemData = GameInstance->GetBaseItemDataFromList(WeaponData.ItemID);

		TObjectPtr<AWeapon> Weapon = GetWorld()->SpawnActor<AWeapon>(ItemData.ActorReference, OwnerCharacter->GetActorLocation(), OwnerCharacter->GetActorRotation(), SpawnParams);

		AttachedWeapon = Weapon;

		if (IsValid(Weapon.Get())) {
			Weapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponData.AttachTo);
			Weapon->SetWeaponData(ItemData, WeaponData);
			Weapon->SetOwnerCharacter(OwnerCharacter);

			OwnerCharacter->GetStateManager()->ArmedStatus = EArmedStatus::Armed;
			OwnerCharacter->GetCombatManager()->SetCombatableAreaDistances(WeaponData.WeaponRelatedCombatDistances);

			EHandedWeaponType HandedWeaponType = WeaponData.HoldingType == EWeaponHolding::OneHanded ? EHandedWeaponType::OneHandedSword : EHandedWeaponType::TwoHandedSword;
			OwnerCharacter->GetCombatManager()->SetHandedWeaponType(HandedWeaponType);
		}
	}
}

void UGearsComponent::DetachFromHand()
{
	if (AttachedWeapon) {
		AttachedWeapon->DestroyActor();
	}
}

void UGearsComponent::ChooseWeapon(int32 SlotIndex)
{
	DetachFromHand();
	OwnerCharacter->GetStateManager()->ArmedStatus = EArmedStatus::Unarmed;
	OwnerCharacter->GetCombatManager()->SetHandedWeaponType(EHandedWeaponType::NoHandedWeapon);
	OwnerCharacter->GetCombatManager()->SetToDefaultCombatableAreaDistances();

	switch (SlotIndex)
	{
		case 0:
			break;
		case 1:
			AttachToHand(WeaponSlot1);
			break;
		case 2:
			AttachToHand(WeaponSlot2);
			break;
		default:
			break;
	}
}

void UGearsComponent::SwitchWeaponsInc()
{
	if (CurrentWeaponSlotIndex + 1 > 2) {
		CurrentWeaponSlotIndex = 0;
	}
	else {
		CurrentWeaponSlotIndex += 1;
	}

	ChooseWeapon(CurrentWeaponSlotIndex);
}

void UGearsComponent::SwitchWeaponsDec()
{
	if (CurrentWeaponSlotIndex - 1 < 0) {
		CurrentWeaponSlotIndex = 2;
	}
	else {
		CurrentWeaponSlotIndex -= 1;
	}

	ChooseWeapon(CurrentWeaponSlotIndex);
}