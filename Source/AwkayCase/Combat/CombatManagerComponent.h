// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatStructure.h"
#include "CombatManagerComponent.generated.h"

class ACharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AWKAYCASE_API UCombatManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatManagerComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
		TObjectPtr<ACharacterBase> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		FNpcCombatableAreaDistances CombatableAreaDistances;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		ECombatMode CurrentCombatMode = ECombatMode::MeleeCombat;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		EHandedWeaponType HandedWeaponType = EHandedWeaponType::NoHandedWeapon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TArray<FCombatMontageStructure> AttackMontages;

	UPROPERTY()
		int32 CurrentAnimationIndex = 0;

public:	
	UFUNCTION()
		void SetOwnerCharacter(ACharacterBase* Character);

	UFUNCTION()
		void SetCombatMode(ECombatMode CombatMode);

	UFUNCTION()
		void SetHandedWeaponType(EHandedWeaponType WeaponType);

	UFUNCTION()
		EHandedWeaponType GetHandedWeaponType() const { return HandedWeaponType; };

	UFUNCTION()
		FNpcCombatableAreaDistances GetCombatableAreaDistances() const { return CombatableAreaDistances; };

	UFUNCTION()
		void SetCombatableAreaDistances(FNpcCombatableAreaDistances AreaDistances);

	UFUNCTION()
		void SetToDefaultCombatableAreaDistances();

	UFUNCTION()
		void HandleAttack(ECombatTriggerClick TriggerType);

	UFUNCTION()
		void PerformAttack();

	UFUNCTION()
		void ManageHitTrace(bool bStartAttack);

	UFUNCTION()
		void ManageComboAttack();

	UFUNCTION()
		void ResetHandlerData();

};
