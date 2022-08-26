// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatStructure.h"
#include "HealthComponent.generated.h"

class ACharacterBase;
class UMaterialInterface;
class UParticleSystem;
class UAnimMontage;
class USoundCue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AWKAYCASE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
		TObjectPtr<ACharacterBase> OwnerCharacter;

	UPROPERTY()
		float MaxHealth = 0.f;

	/*UPROPERTY(ReplicatedUsing = OnRep_HealthChange)
		float Health = 0.f;*/

	UPROPERTY()
		float Health = 0.f;

	UPROPERTY(BlueprintReadOnly)
		EHitDirection LastRecordedHitDirection;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effects | Bloods")
		TObjectPtr<UParticleSystem> DefaultHitBlood;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effects | Bloods")
		TArray<TObjectPtr<UMaterialInterface>> DeadBloods;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effects | Bloods")
		TArray<TObjectPtr<UAnimMontage>> TakeHitResponses;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effects | Sounds")
		TObjectPtr<USoundCue> LowHealthSound;

	UPROPERTY(BlueprintReadOnly, Category = "Effects | Sounds")
		bool bLowHealthSoundIsPlaying = false;

public:	
	UFUNCTION()
		void SetOwnerCharacter(ACharacterBase* Character);

	/*UFUNCTION(Server, Reliable)
		void SetHealth(float Value);*/

	UFUNCTION()
		void SetMaxHealth(float Value, bool bUpdateHealth);

	UFUNCTION()
		void SetHealth(float Value);

	UFUNCTION()
		float GetHealth() const { return Health; };

	/*UFUNCTION()
		void OnRep_HealthChange();*/

	UFUNCTION()
		void HandleDamage(ACharacterBase* Attacker, FVector ImpactPoint, float DamageValue);

	UFUNCTION()
		void HandleDamage_TakeDamage(ACharacterBase* Attacker, EHitDirection HitDirection, FVector ImpactPoint, float DamageValue);

	/*UFUNCTION()
		void HandleDamage_BlockDamage(ACharacterBase* Attacker, EHitDirection HitDirection, FVector ImpactPoint, float DamageValue);*/

	UFUNCTION()
		EHitDirection CalculateHitDirection(FVector AttackerLocation);

	UFUNCTION()
		FVector CalculateOnDeadVelocity();

	UFUNCTION()
		void PerformDead();

	UFUNCTION()
		void OnCharacterDead();

	UFUNCTION(Server, Reliable)
		void Server_PerformDead();

	UFUNCTION(NetMulticast, Reliable)
		void Multi_PerformDead();

	UFUNCTION()
		void DecreaseHealth(ACharacterBase* Attacker, float DamageValue);

	UFUNCTION()
		void SpawnBloodSplash(FVector ImpactPoint);

	UFUNCTION()
		void SpawnDeadBlood();

	UPROPERTY()
		TObjectPtr<ACharacterBase> LastAttacker;

};
