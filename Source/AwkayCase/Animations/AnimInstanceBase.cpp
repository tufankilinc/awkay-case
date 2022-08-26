// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceBase.h"
#include "AwkayCase/Characters/CharacterBase.h"
#include "AwkayCase/States/StateManagerComponent.h"
#include "AwkayCase/Combat/CombatManagerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (TryGetPawnOwner()) {
		ACharacterBase* Character = Cast<ACharacterBase>(TryGetPawnOwner());
		if (Character != nullptr) {
			OwnerCharacter = Character;
		}
	}
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerCharacter != nullptr) {
		CalculateVerticalLooking();

		AnimationMovementData = CalculateAnimationMovementData();
		AnimationCharacterStateData = CalculateAnimationCharacterStateData();
	}
}

FAnimationMovementData UAnimInstanceBase::CalculateAnimationMovementData()
{
	float MovementDirection;
	float BlendspaceDirection;
	float BlendspaceSpeed;

	FVector ActorVelocity = OwnerCharacter->GetVelocity();
	FRotator ActorRotation = OwnerCharacter->GetActorRotation();

	MovementDirection = UKismetAnimationLibrary::CalculateDirection(ActorVelocity, ActorRotation);
	
	if (UKismetMathLibrary::InRange_FloatFloat(MovementDirection, -180.f, -175.f, true, true) ||
		UKismetMathLibrary::InRange_FloatFloat(MovementDirection, 175.f, 180.f, true, true)) {
		BlendspaceDirection = 0.f;
	}
	else {
		BlendspaceDirection = MovementDirection;
	}

	if (UKismetMathLibrary::InRange_FloatFloat(MovementDirection, -100.f, 100.f, true, true)) {
		BlendspaceSpeed = ActorVelocity.Size();
	}
	else {
		BlendspaceSpeed = ActorVelocity.Size() * -1.f;
	}

	FAnimationMovementData MovementData;
	MovementData.MovementDirection = MovementDirection;
	MovementData.BlendspaceDirection = BlendspaceDirection;
	MovementData.Speed = ActorVelocity.Size();
	MovementData.BlendspaceSpeed = BlendspaceSpeed;
	MovementData.bIsFalling = OwnerCharacter->GetMovementComponent()->IsFalling();
	MovementData.bIsFlying = OwnerCharacter->GetMovementComponent()->IsFlying();

	if (!MovementData.bIsFalling && !MovementData.bIsFlying) {
		if (OwnerCharacter->GetStateManager()->MovementState == EMovementState::Jumping) OwnerCharacter->GetStateManager()->MovementState = EMovementState::Standing;
	}

	return MovementData;
}

FAnimationCharacterStateData UAnimInstanceBase::CalculateAnimationCharacterStateData()
{
	bool bIsArmed;
	if (OwnerCharacter->GetStateManager()->ArmedStatus == EArmedStatus::Armed) bIsArmed = true; else bIsArmed = false;

	bool bIsJumped = false;
	if (OwnerCharacter->GetStateManager()->MovementState == EMovementState::Jumping) bIsJumped = true;

	FAnimationCharacterStateData States;
	States.bIsJumped = bIsJumped;
	States.bIsArmed = bIsArmed;
	States.HandedWeapon = OwnerCharacter->GetCombatManager()->GetHandedWeaponType();

	return States;
}

void UAnimInstanceBase::CalculateVerticalLooking()
{
	float VectorY = OwnerCharacter->GetBaseAimRotation().Pitch;

	if (VectorY >= 180) {
		VerticalLooking = VectorY - 360;
	}
	else {
		VerticalLooking = VectorY;
	}
}