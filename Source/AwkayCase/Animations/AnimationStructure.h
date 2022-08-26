#pragma once

#include "AwkayCase/Combat/CombatStructure.h"
#include "AnimationStructure.generated.h"

USTRUCT(BlueprintType)
struct FAnimationMovementData
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		bool bIsFalling;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		bool bIsFlying;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float BlendspaceSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float MovementDirection;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float BlendspaceDirection;

};

USTRUCT(BlueprintType)
struct FAnimationCharacterStateData
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		bool bIsArmed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		bool bIsJumped;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		EHandedWeaponType HandedWeapon;

};

//USTRUCT(BlueprintType)
//struct FMontageManagerActionProperties
//{
//	GENERATED_BODY();
//
//};