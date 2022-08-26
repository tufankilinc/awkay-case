// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetAgentSpeed.generated.h"

/**
 * 
 */
UCLASS()
class AWKAYCASE_API UBTTask_SetAgentSpeed : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties", meta = (AllowPrivateAccess = "true"))
		float WalkSpeed;
	
public:
	UBTTask_SetAgentSpeed();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
