// Fill out your copyright notice in the Description page of Project Settings.


#include "StateManagerComponent.h"

UStateManagerComponent::UStateManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	ArmedStatus = EArmedStatus::Unarmed;
	LivingStatus = ELivingStatus::Alive;
	MovementState = EMovementState::Standing;
	CombatActionState = ECombatActionState::None;

}

void UStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

}

bool UStateManagerComponent::CheckIsDead()
{
	if (LivingStatus == ELivingStatus::Dead) {
		return true;
	}

	return false;
}
