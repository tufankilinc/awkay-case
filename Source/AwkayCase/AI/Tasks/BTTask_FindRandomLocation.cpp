// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AwkayCase/AI/AIStructure.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();

	FNavLocation NavLocation;
	FVector TargetLocation = AIController->GetBlackboardComponent()->GetValueAsVector(KVTargetLocation);

	TObjectPtr<UNavigationSystemV1> NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (IsValid(NavSystem.Get()) && NavSystem->GetRandomPointInNavigableRadius(TargetLocation, SearchRadius, NavLocation)) {
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, NavLocation.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}