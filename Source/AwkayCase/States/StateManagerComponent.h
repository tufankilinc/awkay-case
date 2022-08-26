// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateStructure.h"
#include "StateManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AWKAYCASE_API UStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateManagerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadOnly, Category = "States")
		EArmedStatus ArmedStatus;

	UPROPERTY(BlueprintReadOnly, Category = "States")
		ELivingStatus LivingStatus;

	UPROPERTY(BlueprintReadOnly, Category = "States")
		EMovementState MovementState;

	UPROPERTY(BlueprintReadOnly, Category = "States")
		ECombatActionState CombatActionState;

	UFUNCTION()
		bool CheckIsDead();

};
