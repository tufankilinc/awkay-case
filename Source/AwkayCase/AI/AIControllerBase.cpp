// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AwkayCase/Characters/CharacterPlayer.h"
#include "AwkayCase/Characters/CharacterNpc.h"
#include "AwkayCase/Characters/CharacterStructure.h"
#include "AwkayCase/Combat/CombatManagerComponent.h"
#include "AwkayCase/Combat/HealthComponent.h"
#include "AwkayCase/States/StateManagerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

AAIControllerBase::AAIControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Blackboards
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

	// Sight perception
	AISightPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Sight Perception"));

	SenseSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SenseSight->SightRadius = 3000.f;
	SenseSight->LoseSightRadius = SenseSight->SightRadius + 400.f;
	SenseSight->PeripheralVisionAngleDegrees = 90.f;
	SenseSight->DetectionByAffiliation.bDetectNeutrals = true;

	AISightPerceptionComponent->ConfigureSense(*SenseSight.Get());
	AISightPerceptionComponent->SetDominantSense(SenseSight->GetSenseImplementation());
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BehaviorTree.Get())) {
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}

}

void AAIControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(BehaviorTree.Get()) && IsValid(Blackboard.Get())) {
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
	}

	SetPerceptionComponent(*AISightPerceptionComponent.Get());
}

void AAIControllerBase::SetOwnerCharacter(ACharacterNpc* NpcBaseReference)
{
	if (NpcBaseReference != nullptr) {
		Agent = NpcBaseReference;
	}
}

void AAIControllerBase::SetCanPerception(bool bAcceptPerception)
{
	bCanPerception = bAcceptPerception;
}
