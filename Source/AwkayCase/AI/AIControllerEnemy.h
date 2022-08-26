// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "AIStructure.h"
#include "AIControllerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AWKAYCASE_API AAIControllerEnemy : public AAIControllerBase
{
	GENERATED_BODY()

public:
	AAIControllerEnemy();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
		void OnPerception(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY()
		TObjectPtr<AActor> TargetActor;

	UFUNCTION()
		bool TryToSetTarget(AActor* SensedActor, FAIStimulus Stimulus);

	UFUNCTION()
		void SetTargetParameters(AActor* Actor, bool bIsSucceeded);

public:
	UFUNCTION()
		void SetTarget(AActor* Actor);

	UFUNCTION()
		void CheckIsTargetInSight();

	UFUNCTION()
		void CheckDistanceWithTarget();

};
