// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIStructure.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIControllerBase.generated.h"

class ACharacterNpc;
class UAIPerceptionComponent;
class UBehaviorTreeComponent;
class UAISenseConfig_Sight;

UCLASS()
class AWKAYCASE_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBlackboardComponent> BlackboardComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Sight Perception", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UAIPerceptionComponent> AISightPerceptionComponent;

public:
	AAIControllerBase();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(BlueprintReadOnly, Category = "Sight Perception")
		TObjectPtr<UAISenseConfig_Sight> SenseSight;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		TObjectPtr<ACharacterNpc> Agent;

	UPROPERTY()
		bool bCanPerception = true;

public:
	UFUNCTION()
		void SetOwnerCharacter(ACharacterNpc* NpcBaseReference);

	UFUNCTION()
		ACharacterNpc* GetAgent() const { return Agent; };

	UFUNCTION()
		UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; };

	UFUNCTION()
		void SetCanPerception(bool bAcceptPerception);

};
