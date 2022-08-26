// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInventoryComponent;

UCLASS()
class AWKAYCASE_API ACharacterPlayer : public ACharacterBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInventoryComponent> InventoryComponent;

public:
	ACharacterPlayer();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// INPUT ACTIONS

	UFUNCTION()
		void OnInteract();

	UFUNCTION(Server, Reliable)
		void Server_OnInteract();

	UFUNCTION()
		void ToggleBackpack();

	UFUNCTION()
		void SwitchWeaponsNext();

	UFUNCTION()
		void SwitchWeaponsPrev();

	UFUNCTION()
		void TriggerAttack();

public:
	UFUNCTION()
		UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; };

};
