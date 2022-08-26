// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ILivingThing.h"
#include "CharacterStructure.h"
#include "AwkayCase/AwkayCaseCharacter.h"
#include "AwkayCase/Combat/CombatStructure.h"
#include "CharacterBase.generated.h"

class UAnimMontage;
class UCameraShakeBase;

class UHealthComponent;
class UGearsComponent;
class UCombatManagerComponent;
class UMontageManagerComponent;
class UStateManagerComponent;

UCLASS()
class AWKAYCASE_API ACharacterBase : public AAwkayCaseCharacter, public IILivingThing
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStateManagerComponent> StateManager;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UGearsComponent> GearsComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCombatManagerComponent> CombatManager;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UMontageManagerComponent> MontageManager;

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FName CharacterID;

	UPROPERTY(Replicated, BlueprintReadOnly)
		FCharacterData CharacterData;

	UPROPERTY(Replicated, BlueprintReadOnly)
		FCharacterPropertyData PropertiesData;

public:	
	virtual void TakeDamage(ACharacterBase* Character, FVector ImpactPoint, float TakenDamage) override;

	UFUNCTION()
		UHealthComponent* GetHealthComponent() const { return HealthComponent; };

	UFUNCTION() 
		UStateManagerComponent* GetStateManager() const { return StateManager; };

	UFUNCTION() 
		UGearsComponent* GetGearsComponent() const { return GearsComponent; };

	UFUNCTION() 
		UCombatManagerComponent* GetCombatManager() const { return CombatManager; };

	UFUNCTION() 
		UMontageManagerComponent* GetMontageManager() const { return MontageManager; };

	UFUNCTION()
		bool SetCharacterID(FName ID);

	UFUNCTION()
		void InitializeCharacterData(FName ID);

	UFUNCTION(BlueprintPure)
		FCharacterData GetCharacterData() const { return CharacterData; };

	UFUNCTION(BlueprintPure)
		FCharacterPropertyData GetPropertiesData() const { return PropertiesData; };

	UFUNCTION()
		void SetPropertiesData(FCharacterPropertyData Properties) { PropertiesData = Properties; };

	UFUNCTION()
		void PerformAttack(ECombatTriggerClick TriggerType);

	UFUNCTION()
		void PerformJump();

	UFUNCTION()
		void PerformCrouch();

};
