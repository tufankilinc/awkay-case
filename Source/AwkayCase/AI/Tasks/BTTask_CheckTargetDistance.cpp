// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckTargetDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AwkayCase/AI/AIControllerEnemy.h"
#include "AwkayCase/AI/AIStructure.h"

UBTTask_CheckTargetDistance::UBTTask_CheckTargetDistance()
{
	
}

EBTNodeResult::Type UBTTask_CheckTargetDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<AAIControllerEnemy> AIController = Cast<AAIControllerEnemy>(OwnerComp.GetAIOwner());

	AIController->CheckDistanceWithTarget();

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}