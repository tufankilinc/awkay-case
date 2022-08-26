// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "AwkayCaseCharacter.generated.h"

class UBoxComponent;

UCLASS(config=Game)
class AAwkayCaseCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Reaction Helper", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> CharactersFrontLocation;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Reaction Helper", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> CharactersBackLocation;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Reaction Helper", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> CharactersLeftLocation;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Reaction Helper", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> CharactersRightLocation;

public:
	AAwkayCaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);


protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION()
		FVector GetCharactersFrontLocation() const { return CharactersFrontLocation->GetComponentLocation(); };

	UFUNCTION()
		FVector GetCharactersBackLocation() const { return CharactersBackLocation->GetComponentLocation(); };

	UFUNCTION()
		FVector GetCharactersLeftLocation() const { return CharactersLeftLocation->GetComponentLocation(); };

	UFUNCTION()
		FVector GetCharactersRightLocation() const { return CharactersRightLocation->GetComponentLocation(); };

};

