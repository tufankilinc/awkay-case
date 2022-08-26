// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "ItemStructure.h"
#include "Weapon.generated.h"

class ACharacterBase;

/**
 * 
 */
UCLASS()
class AWKAYCASE_API AWeapon : public AItemBase
{
	GENERATED_BODY()

public:
	AWeapon();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		TObjectPtr<ACharacterBase> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Structure")
		FWeaponStructure WeaponData;

	UPROPERTY()
		FTimerHandle AttackTimer;

	UPROPERTY()
		TArray<AActor*> ActorsToIgnore;

	UPROPERTY()
		TArray<FVector> LastLinePoints;

	UPROPERTY()
		bool bDrawLine = false;

public:
	UFUNCTION()
		void DestroyActor();

	UFUNCTION()
		void HandleDetachment();

	UFUNCTION()
		void SetOwnerCharacter(ACharacterBase* Character);

	UFUNCTION()
		void SetWeaponData(FItemStructure ItemStructure, FWeaponStructure WeaponStructure);

	UFUNCTION()
		void StartAttack();

	UFUNCTION(Server, Reliable)
		void Server_StartAttack(ACharacterBase* Character);

	UFUNCTION(NetMulticast, Reliable)
		void Multi_StartAttack(ACharacterBase* Character);

	UFUNCTION()
		void StopAttack();

	UFUNCTION(Server, Reliable)
		void Server_StopAttack(ACharacterBase* Character);

	UFUNCTION(NetMulticast, Reliable)
		void Multi_StopAttack(ACharacterBase* Character);

	UFUNCTION()
		void PerformAttack();

	UFUNCTION()
		void PlayAttackSound();
	
};
