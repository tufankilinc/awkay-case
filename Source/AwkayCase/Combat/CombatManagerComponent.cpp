// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManagerComponent.h"
#include "AwkayCase/Characters/CharacterBase.h"
#include "AwkayCase/Inventories/GearsComponent.h"
#include "AwkayCase/Items/Weapon.h"
#include "AwkayCase/Animations/MontageManagerComponent.h"
#include "Animation/AnimMontage.h"

UCombatManagerComponent::UCombatManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCombatManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetToDefaultCombatableAreaDistances();

}

void UCombatManagerComponent::SetOwnerCharacter(ACharacterBase* Character)
{
	if (Character != nullptr) {
		OwnerCharacter = Character;
	}
}

void UCombatManagerComponent::SetCombatMode(ECombatMode CombatMode)
{
	CurrentCombatMode = CombatMode;
}

void UCombatManagerComponent::SetHandedWeaponType(EHandedWeaponType WeaponType)
{
	HandedWeaponType = WeaponType;
}

void UCombatManagerComponent::SetCombatableAreaDistances(FNpcCombatableAreaDistances AreaDistances)
{
	CombatableAreaDistances = AreaDistances;
}

void UCombatManagerComponent::SetToDefaultCombatableAreaDistances()
{
	FNpcCombatableAreaDistances AreaDistances;
	AreaDistances.SafeDistance = 2000.f;
	AreaDistances.HoldingDistance = 800.f;
	AreaDistances.CombatDistance = 60.f;
	SetCombatableAreaDistances(AreaDistances);
}

void UCombatManagerComponent::HandleAttack(ECombatTriggerClick TriggerType)
{
	switch (TriggerType)
	{
		case ECombatTriggerClick::Press:
			PerformAttack();
			break;
		default:
			break;
	}
}

void UCombatManagerComponent::PerformAttack()
{
	TObjectPtr<UAnimMontage> AnimMontage = AttackMontages[CurrentAnimationIndex].AnimationMontage;
	float PlayRate = AttackMontages[CurrentAnimationIndex].PlayRate;

	OwnerCharacter->GetMontageManager()->PlayMontage_TakeAction(AnimMontage, PlayRate);
} 

void UCombatManagerComponent::ManageHitTrace(bool bStartAttack)
{
	TObjectPtr<AWeapon> Weapon = OwnerCharacter->GetGearsComponent()->GetAttachedWeapon();

	if (bStartAttack) {
		Weapon->StartAttack();
	}
	else {
		Weapon->StopAttack();
	}
}

void UCombatManagerComponent::ManageComboAttack()
{
}

void UCombatManagerComponent::ResetHandlerData()
{
}
