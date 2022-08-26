// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MontageManagerComponent.generated.h"

class ACharacterBase;
class UAnimMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AWKAYCASE_API UMontageManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMontageManagerComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
		TObjectPtr<ACharacterBase> OwnerCharacter;

	UPROPERTY()
		TObjectPtr<UAnimMontage> PlayingMontage;

	UPROPERTY()
		TObjectPtr<UAnimMontage> LastPlayedMontage;

	UPROPERTY()
		bool bRelationsAreSetted = false;

	UFUNCTION()
		void SetAnimInstanceRelations();

	UFUNCTION()
		void LockCharacterToPlayMontage(UAnimMontage* Montage);

	UFUNCTION()
		void UnlockCharacterAtMontagePlayed(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
		void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

public:
	UFUNCTION()
		void SetOwnerCharacter(ACharacterBase* Character);

	UFUNCTION()
		void PlayMontage_TakeAction(UAnimMontage* MontageToPlay, float PlayRate);

	UFUNCTION(Server, Reliable)
		void Server_PlayMontage_TakeAction(ACharacterBase* Character, UAnimMontage* MontageToPlay, float PlayRate);

	UFUNCTION(NetMulticast, Reliable)
		void Multi_PlayMontage_TakeAction(ACharacterBase* Character, UAnimMontage* MontageToPlay, float PlayRate);

};
