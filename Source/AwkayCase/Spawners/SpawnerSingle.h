// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerStructure.h"
#include "SpawnerSingle.generated.h"

UCLASS()
class AWKAYCASE_API ASpawnerSingle : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnerSingle();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FName SpawnableNpcID;

	UPROPERTY(BlueprintReadOnly)
		TObjectPtr<ACharacterNpc> SpawnedNpc;

	/*UPROPERTY(ReplicatedUsing = OnRep_IsSpawnedChange, BlueprintReadOnly)
		bool bIsSpawned = false;*/

	UPROPERTY(BlueprintReadOnly)
		bool bIsSpawned = false;

public:	
	UFUNCTION()
		bool GetIsSpawnedAlready() const { return bIsSpawned; };

	UFUNCTION()
		void SpawnNpcMultiplayerHandler();

	UFUNCTION()
		void SpawnNpc();

	UFUNCTION(Server, Reliable)
		void Server_SpawnNpc();

	UFUNCTION(NetMulticast, Reliable)
		void Multi_SpawnNpc();

	UFUNCTION()
		void DestroyNpc();

	UFUNCTION(Server, Reliable)
		void Server_DestroyNpc();

	UFUNCTION(NetMulticast, Reliable)
		void Multi_DestroyNpc();

	/*UFUNCTION()
		void OnRep_IsSpawnedChange();*/

};
