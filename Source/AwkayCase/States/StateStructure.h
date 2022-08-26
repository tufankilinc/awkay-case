#pragma once

#include "StateStructure.generated.h"

UENUM(BlueprintType)
enum class EArmedStatus : uint8
{
	Unarmed				= 0		UMETA(DisplayName = "Unarmed"),
	Armed				= 1		UMETA(DisplayName = "Armed"),
	Aiming				= 2		UMETA(DisplayName = "Aiming")
};

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Standing			= 0		UMETA(DisplayName = "Standing"),
	Walking				= 1		UMETA(DisplayName = "Walking"),
	Running				= 2		UMETA(DisplayName = "Running"),
	Crouching			= 3		UMETA(DisplayName = "Crouching"),
	Jumping				= 4		UMETA(DisplayName = "Jumping")
};

UENUM(BlueprintType)
enum class ECombatActionState : uint8
{
	None				= 0		UMETA(DisplayName = "None"),
	Attacking			= 1		UMETA(DisplayName = "Attacking"),
	Blocking			= 2		UMETA(DisplayName = "Blocking"),
	TakeDamage			= 3		UMETA(DisplayName = "TakeDamage"),
};

UENUM(BlueprintType)
enum class ELivingStatus : uint8
{
	Alive				= 0		UMETA(DisplayName = "Alive"),
	Dead				= 1		UMETA(DisplayName = "Dead")
};
