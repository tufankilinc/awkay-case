// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetAgentSpeed.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AwkayCase/AI/AIStructure.h"

UBTTask_SetAgentSpeed::UBTTask_SetAgentSpeed()
{
	
}

EBTNodeResult::Type UBTTask_SetAgentSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();

	AIController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}