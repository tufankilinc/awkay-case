#pragma once

#include "AIStructure.generated.h"

UENUM(BlueprintType)
enum class EAIBehaviorTreeState : uint8
{
	Standing					= 0			UMETA(DisplayName = "Standing"),
	Searching					= 1			UMETA(DisplayName = "Searching"),
	InCombat					= 2			UMETA(DisplayName = "In Combat")
};

UENUM(BlueprintType)
enum class EAITargetDistanceState : uint8
{
	TargetInSafeDistance		= 0			UMETA(DisplayName = "Target In Safe Distance"),
	TargetInHoldingDistance		= 1			UMETA(DisplayName = "Target In Holding Distance"),
	TargetInCombatDistance		= 2			UMETA(DisplayName = "Target In Combat Distance"),
	TargetIsDead				= 3			UMETA(DisplayName = "Target Is Dead")
};



// Blackboard Keys Definitions
const FName KATargetActor				= FName("TargetActor");
const FName KVTargetLocation			= FName("TargetLocation");
const FName KVMoveToLocation			= FName("MoveToLocation");
const FName KETargetDistanceState		= FName("TargetDistanceState");
const FName KBIsTargetValid				= FName("IsTargetValid");
const FName KESelfActorBTState			= FName("SelfActorBTState");
const FName KBChangeLocation			= FName("ChangeLocation");
const FName KBGoBack					= FName("GoBack");