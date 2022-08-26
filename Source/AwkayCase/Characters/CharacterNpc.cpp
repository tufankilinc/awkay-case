// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterNpc.h"
#include "AwkayCase/AI/AIControllerEnemy.h"

ACharacterNpc::ACharacterNpc()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIControllerEnemy::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void ACharacterNpc::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<AAIControllerEnemy> AIController = Cast<AAIControllerEnemy>(GetController());

	if (IsValid(AIController.Get())) {
		AIController->SetOwnerCharacter(this);
		EnemyAIController = AIController;
	}

}

void ACharacterNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}