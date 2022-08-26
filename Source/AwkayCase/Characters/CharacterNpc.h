// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CharacterNpc.generated.h"

class AAIControllerEnemy;

UCLASS()
class AWKAYCASE_API ACharacterNpc : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	ACharacterNpc();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
		TObjectPtr<AAIControllerEnemy> EnemyAIController;

public:
	UFUNCTION()
		AAIControllerEnemy* GetAIController() const { return EnemyAIController; };

};
