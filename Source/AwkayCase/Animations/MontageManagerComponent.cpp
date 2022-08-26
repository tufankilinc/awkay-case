// Fill out your copyright notice in the Description page of Project Settings.


#include "MontageManagerComponent.h"
#include "AwkayCase/Characters/CharacterBase.h"
#include "AwkayCase/States/StateManagerComponent.h"
#include "AwkayCase/Combat/HealthComponent.h"
#include "AwkayCase/Combat/CombatManagerComponent.h"
#include "AwkayCase/Inventories/GearsComponent.h"
#include "AwkayCase/Items/Weapon.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Net/UnrealNetwork.h"

UMontageManagerComponent::UMontageManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UMontageManagerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UMontageManagerComponent::SetOwnerCharacter(ACharacterBase* Character)
{
	if (Character != nullptr) {
		OwnerCharacter = Character;

		if (!bRelationsAreSetted) {
			SetAnimInstanceRelations();
		}
	}
}

void UMontageManagerComponent::SetAnimInstanceRelations()
{
	TObjectPtr<UAnimInstance> AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	/*AnimInstance->OnMontageStarted.AddDynamic(this, &UMontageManagerComponent::LockCharacterToPlayMontage);
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &UMontageManagerComponent::UnlockCharacterAtMontagePlayed);*/
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UMontageManagerComponent::OnMontageNotifyBegin);

	bRelationsAreSetted = true;
}

void UMontageManagerComponent::LockCharacterToPlayMontage(UAnimMontage* Montage)
{
	/*OwnerCharacter->ActionProperties.bCanDodge = false;
	OwnerCharacter->ActionProperties.bCanJump = false;
	OwnerCharacter->ActionProperties.bRotateCharacter = false;
	OwnerCharacter->ActionProperties.bTurnInPlace = false;*/
}

void UMontageManagerComponent::UnlockCharacterAtMontagePlayed(UAnimMontage* Montage, bool bInterrupted)
{
	/*OwnerCharacter->ActionProperties.bCanDodge = true;
	OwnerCharacter->ActionProperties.bCanJump = true;
	OwnerCharacter->ActionProperties.bRotateCharacter = true;
	OwnerCharacter->ActionProperties.bTurnInPlace = true;*/
}

void UMontageManagerComponent::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == FName("StartAttack")) {
		OwnerCharacter->GetCombatManager()->ManageHitTrace(true);
		//OwnerCharacter->GetCombatManager()->ManageComboAttack(true, false, false);
	}

	if (NotifyName == FName("StopAttack")) {
		OwnerCharacter->GetCombatManager()->ManageHitTrace(false);
	}

	if (NotifyName == FName("PerformRequestedAttack")) {
		//OwnerCharacter->GetCombatManager()->ManageComboAttack(false, true, false);
	}

	if (NotifyName == FName("Reset")) {
		//OwnerCharacter->GetCombatManager()->ManageComboAttack(false, false, true);
	}

	if (NotifyName == FName("PerformDead")) {
		if (OwnerCharacter->GetStateManager()->CheckIsDead()) {
			OwnerCharacter->GetHealthComponent()->PerformDead();
		}
	}
}

void UMontageManagerComponent::PlayMontage_TakeAction(UAnimMontage* MontageToPlay, float PlayRate)
{
	TObjectPtr<UAnimInstance> AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(MontageToPlay, PlayRate);

	if (!OwnerCharacter->HasAuthority()) {
		Server_PlayMontage_TakeAction(OwnerCharacter, MontageToPlay, PlayRate);
	}
	else {
		Multi_PlayMontage_TakeAction(OwnerCharacter, MontageToPlay, PlayRate);
	}
}

void UMontageManagerComponent::Server_PlayMontage_TakeAction_Implementation(ACharacterBase* Character, UAnimMontage* MontageToPlay, float PlayRate)
{
	Multi_PlayMontage_TakeAction(Character, MontageToPlay, PlayRate);
}

void UMontageManagerComponent::Multi_PlayMontage_TakeAction_Implementation(ACharacterBase* Character, UAnimMontage* MontageToPlay, float PlayRate)
{
	if (!OwnerCharacter->IsLocallyControlled()) {
		TObjectPtr<UAnimInstance> AnimInstance = Character->GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(MontageToPlay, PlayRate);
	}
}
