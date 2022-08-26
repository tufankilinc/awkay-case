#pragma once

#include "SpawnerStructure.generated.h"

class ACharacterNpc;

// DEPRECATED
USTRUCT(BlueprintType)
struct FSpawnableNpcData
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FName NpcID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TSubclassOf<ACharacterNpc> ActorReference;

};