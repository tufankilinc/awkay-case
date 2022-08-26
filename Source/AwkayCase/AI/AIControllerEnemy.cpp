// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerEnemy.h"
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
#include "AwkayCase/Combat/CombatStructure.h"
#include "AwkayCase/States/StateManagerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

AAIControllerEnemy::AAIControllerEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAIControllerEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AAIControllerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIControllerEnemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerEnemy::OnPerception);
}

void AAIControllerEnemy::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	if (!bCanPerception) return;

	if (!GetBlackboardComponent()->GetValueAsBool(KBIsTargetValid)) {
		bool bIsSetted = TryToSetTarget(Actor, Stimulus);
	}
}

bool AAIControllerEnemy::TryToSetTarget(AActor* SensedActor, FAIStimulus Stimulus)
{
	if (TargetActor == nullptr) {
		TObjectPtr<ACharacterPlayer> SensedCharacter = Cast<ACharacterPlayer>(SensedActor);

		if (SensedCharacter == nullptr || SensedCharacter->GetStateManager()->CheckIsDead()) {
			SetTargetParameters(SensedCharacter, false);
			return false;
		}
		else {
			if (Stimulus.WasSuccessfullySensed()) {
				SetTargetParameters(SensedCharacter, true);
				return true;
			}
			else {
				SetTargetParameters(SensedCharacter, false);
				return false;
			}
		}
	}

	return false;
}

void AAIControllerEnemy::SetTarget(AActor* Actor)
{
	if (Actor == TargetActor || Actor == nullptr) return;
	SetTargetParameters(Actor, false);
}

void AAIControllerEnemy::SetTargetParameters(AActor* Actor, bool bIsSucceeded)
{
	if (Actor != nullptr && bIsSucceeded) {
		SetTarget(Actor);
		SetFocus(TargetActor);
		GetBlackboardComponent()->SetValueAsObject(KATargetActor, Actor);
		GetBlackboardComponent()->SetValueAsVector(KVTargetLocation, Actor->GetActorLocation());
		GetBlackboardComponent()->SetValueAsBool(KBIsTargetValid, true);
	}
	else {
		SetTarget(nullptr);
		SetFocus(nullptr);
		GetBlackboardComponent()->SetValueAsObject(KATargetActor, nullptr);
		GetBlackboardComponent()->SetValueAsBool(KBIsTargetValid, false);
	}
}

void AAIControllerEnemy::CheckIsTargetInSight()
{
	if (TargetActor != nullptr) {
		FActorPerceptionInfo Info = *GetPerceptionComponent()->GetActorInfo(*TargetActor.Get());
		bool bIsActive = Info.HasAnyCurrentStimulus();
		FVector LastSeenLocation = Info.GetLastStimulusLocation();

		/*if (!bIsActive) {
			GetWorld()->GetTimerManager().ClearTimer(CheckBehavioralSituationsTimer);
			SetTargetParameters(TargetActor, false);
			GetBlackboardComponent()->SetValueAsVector(KVTargetLocation, LastSeenLocation);
		}*/
	}
}

void AAIControllerEnemy::CheckDistanceWithTarget()
{
	if (TargetActor != nullptr) {
		float DistanceBetweenTarget = UKismetMathLibrary::Vector_Distance(Agent->GetActorLocation(), TargetActor->GetActorLocation());

		FNpcCombatableAreaDistances DistanceAreas = GetAgent()->GetCombatManager()->GetCombatableAreaDistances();

		if (DistanceAreas.SafeDistance >= DistanceBetweenTarget && DistanceBetweenTarget >= DistanceAreas.HoldingDistance) {
			GetBlackboardComponent()->SetValueAsEnum(KETargetDistanceState, uint8(EAITargetDistanceState::TargetInSafeDistance));
			UE_LOG(LogTemp, Warning, TEXT("Safe Distance"));
		}
		else if (DistanceAreas.HoldingDistance >= DistanceBetweenTarget && DistanceBetweenTarget >= DistanceAreas.CombatDistance) {
			GetBlackboardComponent()->SetValueAsEnum(KETargetDistanceState, uint8(EAITargetDistanceState::TargetInHoldingDistance));
			UE_LOG(LogTemp, Warning, TEXT("Holding Distance"));
		}
		else if (DistanceBetweenTarget >= DistanceAreas.CombatDistance) {
			GetBlackboardComponent()->SetValueAsEnum(KETargetDistanceState, uint8(EAITargetDistanceState::TargetInCombatDistance));
			UE_LOG(LogTemp, Warning, TEXT("Combat Distance"));
		}
		else {
			GetBlackboardComponent()->SetValueAsEnum(KETargetDistanceState, uint8(EAITargetDistanceState::TargetInSafeDistance));
			UE_LOG(LogTemp, Warning, TEXT("Safe Distance"));
		}
	}
}