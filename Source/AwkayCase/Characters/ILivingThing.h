// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ILivingThing.generated.h"

class ACharacterBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UILivingThing : public UInterface
{
	GENERATED_BODY()
};

class AWKAYCASE_API IILivingThing
{
	GENERATED_BODY()

public:
	virtual void TakeDamage(ACharacterBase* Character, FVector ImpactPoint, float TakenDamage);

};
