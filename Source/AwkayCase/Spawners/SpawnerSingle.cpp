// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerSingle.h"
#include "AwkayCase/Characters/CharacterNpc.h"
#include "AwkayCase/Characters/CharacterStructure.h"
#include "AwkayCase/Game/AwkayGameInstance.h"
#include "Kismet/GameplayStatics.h"

ASpawnerSingle::ASpawnerSingle()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

}

void ASpawnerSingle::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnNpcMultiplayerHandler();

}

void ASpawnerSingle::SpawnNpcMultiplayerHandler()
{
	if (GetLocalRole() < ROLE_Authority) {
		Server_SpawnNpc();
	}
	else {
		Multi_SpawnNpc();
	}
}


void ASpawnerSingle::SpawnNpc()
{
	TObjectPtr<UAwkayGameInstance> GameInstance = Cast<UAwkayGameInstance>(GetWorld()->GetGameInstance());

	if (!IsValid(GameInstance.Get())) return;

	FCharacterData BaseCharacterData = GameInstance->GetCharacterDataFromList(SpawnableNpcID);

	if (BaseCharacterData.CharacterID != NAME_None) {
		TObjectPtr<ACharacterNpc> Spawned = Cast<ACharacterNpc>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), BaseCharacterData.CharacterReference, GetActorTransform(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
		bool bIdSetted = Spawned->SetCharacterID(BaseCharacterData.CharacterID);
		
		if (bIdSetted) {
			Spawned->InitializeCharacterData(BaseCharacterData.CharacterID);
			UGameplayStatics::FinishSpawningActor(Spawned, GetActorTransform());

			if (IsValid(Spawned.Get())) {
				SpawnedNpc = Spawned;
				bIsSpawned = true;
			}
		}
	}
}

void ASpawnerSingle::Server_SpawnNpc_Implementation()
{
	Multi_SpawnNpc();
}

void ASpawnerSingle::Multi_SpawnNpc_Implementation()
{
	SpawnNpc();
}

void ASpawnerSingle::DestroyNpc()
{
	if (IsValid(SpawnedNpc.Get())) {
		TArray<TObjectPtr<AActor>> Attacheds;
		SpawnedNpc->GetAttachedActors(Attacheds);

		for (int32 i = 0; i < Attacheds.Num(); i++) {
			Attacheds[i]->Destroy();
		}

		SpawnedNpc->Destroy();
		bIsSpawned = false;
	}
}

void ASpawnerSingle::Server_DestroyNpc_Implementation()
{
}

void ASpawnerSingle::Multi_DestroyNpc_Implementation()
{
}