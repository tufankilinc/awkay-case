// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CheckTargetDistance.generated.h"

/**
 * 
 */
UCLASS()
class AWKAYCASE_API UBTTask_CheckTargetDistance : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_CheckTargetDistance();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
