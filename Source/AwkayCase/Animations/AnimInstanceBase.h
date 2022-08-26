// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimationStructure.h"
#include "AnimInstanceBase.generated.h"

class ACharacterBase;

UCLASS()
class AWKAYCASE_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Component")
		TObjectPtr<ACharacterBase> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		FAnimationMovementData AnimationMovementData;

	UPROPERTY(BlueprintReadOnly)
		FAnimationCharacterStateData AnimationCharacterStateData;

	UPROPERTY(BlueprintReadOnly)
		float VerticalLooking;

public:
	UFUNCTION()
		FAnimationMovementData GetAnimationMovementData() const { return AnimationMovementData; };

	UFUNCTION()
		FAnimationCharacterStateData GetAnimationCharacterStateData() const { return AnimationCharacterStateData; };

	UFUNCTION()
		FAnimationMovementData CalculateAnimationMovementData();

	UFUNCTION()
		FAnimationCharacterStateData CalculateAnimationCharacterStateData();

	UFUNCTION()
		void CalculateVerticalLooking();

};
