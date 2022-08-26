// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AwkayCase/Characters/CharacterBase.h"
#include "AwkayCase/Characters/CharacterNpc.h"
#include "AwkayCase/Characters/CharacterPlayer.h"
#include "AwkayCase/States/StateManagerComponent.h"
#include "AwkayCase/Animations/MontageManagerComponent.h"
#include "AwkayCase/Inventories/GearsComponent.h"
#include "AwkayCase/Combat/CombatManagerComponent.h"
#include "AwkayCase/AI/AIControllerEnemy.h"
#include "AwkayCase/Items/Weapon.h"
#include "Materials/MaterialInterface.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "Sound/SoundCue.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UHealthComponent::SetOwnerCharacter(ACharacterBase* Character)
{
	if (Character != nullptr) {
		OwnerCharacter = Character;
	}
}

void UHealthComponent::SetMaxHealth(float Value, bool bUpdateHealth)
{
	MaxHealth = Value;
	if (bUpdateHealth) Health = MaxHealth;
}

void UHealthComponent::SetHealth(float Value)
{
	Health = Value;
}

//void UHealthComponent::SetHealth_Implementation(float Value)
//{
//}

//void UHealthComponent::OnRep_HealthChange_Implementation()
//{
//}

void UHealthComponent::HandleDamage(ACharacterBase* Attacker, FVector ImpactPoint, float DamageValue)
{
	/*if (Attacker->GetMembershipID() == OwnerCharacter->GetMembershipID() || OwnerCharacter->ActorHasTag("Dead")) {
		return;
	}*/

	LastAttacker = Attacker;

	LastRecordedHitDirection = CalculateHitDirection(Attacker->GetActorLocation());

	HandleDamage_TakeDamage(Attacker, LastRecordedHitDirection, ImpactPoint, DamageValue);

	OwnerCharacter->GetStateManager()->CombatActionState = ECombatActionState::None;

	/*if (!OwnerCharacter->IsPlayerControlled()) {
		OwnerCharacter->GetAIController()->SetTarget(Attacker);
	}*/
}

void UHealthComponent::HandleDamage_TakeDamage(ACharacterBase* Attacker, EHitDirection HitDirection, FVector ImpactPoint, float DamageValue)
{
	OwnerCharacter->GetStateManager()->CombatActionState = ECombatActionState::TakeDamage;

	OwnerCharacter->GetCharacterMovement()->StopMovementImmediately();

	if (OwnerCharacter->GetGearsComponent()->GetAttachedWeapon()) {
		OwnerCharacter->GetGearsComponent()->GetAttachedWeapon()->StopAttack();
	}

	OwnerCharacter->GetCombatManager()->ResetHandlerData();

	DecreaseHealth(Attacker, DamageValue);
	SpawnBloodSplash(ImpactPoint);

	/*if (!OwnerCharacter->IsPlayerControlled() && IsValid(OwnerCharacter->GetAIController().Get())) {
		float Cooldown = bIsHeavy ? FMath::FRandRange(1.f, 1.5f) : FMath::FRandRange(0.5f, 1.f);
		OwnerCharacter->GetAIController()->AddCooldownToAIController(Cooldown);
		OwnerCharacter->GetAIController()->IncreaseConsutativeTakeDamageCount();
	}*/

	int32 MontageIndex = 0;

	switch (HitDirection)
	{
	case EHitDirection::Front:
		MontageIndex = 0;
		break;
	case EHitDirection::Right:
		MontageIndex = 1;
		break;
	case EHitDirection::Back:
		MontageIndex = 2;
		break;
	case EHitDirection::Left:
		MontageIndex = 3;
		break;
	default:
		break;
	}

	bool bIsDead = OwnerCharacter->GetStateManager()->CheckIsDead();

	TObjectPtr<UAnimMontage> RelatedHitMontage = TakeHitResponses[MontageIndex];
	OwnerCharacter->GetMontageManager()->PlayMontage_TakeAction(RelatedHitMontage, 1.f);

	if (bIsDead) {
		//Attacker->GetCombatManager()->PlayCameraShake(1.f);
	}
	else if (UKismetMathLibrary::RandomInteger(3) >= 1) {
		//Attacker->GetCombatManager()->PlayCameraShake(0.5f);
		SpawnDeadBlood();
	}
	else {
		//Attacker->GetCombatManager()->PlayCameraShake(0.5f);
	}
}

EHitDirection UHealthComponent::CalculateHitDirection(FVector AttackerLocation)
{
	FRotator RotationBetweenHitAndCharacter = UKismetMathLibrary::FindLookAtRotation(AttackerLocation, OwnerCharacter->GetActorLocation());
	FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(OwnerCharacter->GetActorRotation(), RotationBetweenHitAndCharacter);

	bool bIsBack = UKismetMathLibrary::InRange_FloatFloat(DeltaRotator.Yaw, -45.f, 45.f, true, true);
	bool bIsLeft = UKismetMathLibrary::InRange_FloatFloat(DeltaRotator.Yaw, -135.f, -45.f, false, false);
	bool bIsRight = UKismetMathLibrary::InRange_FloatFloat(DeltaRotator.Yaw, 135.f, 45.f, true, false);

	if (bIsBack) return EHitDirection::Back;
	else if (bIsLeft) return EHitDirection::Left;
	else if (bIsRight) return EHitDirection::Right;
	else return EHitDirection::Front;
}

void UHealthComponent::DecreaseHealth(ACharacterBase* Attacker, float DamageValue)
{
	float Damage = DamageValue / FMath::Exp2(10 / DamageValue);
	Health -= Damage;

	//OwnerCharacter->HealthUpdateOnWidget_Implementable(Health);

	if (Health <= 0) {
		OwnerCharacter->GetStateManager()->LivingStatus = ELivingStatus::Dead;
		OwnerCharacter->Tags.Add("Dead");
	}
	else if (Health <= MaxHealth * 10 / 100 && !bLowHealthSoundIsPlaying) {
		UGameplayStatics::PlaySound2D(GetWorld(), LowHealthSound);
		bLowHealthSoundIsPlaying = true;
	}
}

void UHealthComponent::SpawnBloodSplash(FVector ImpactPoint)
{
	FRotator CharacterRotation = OwnerCharacter->GetActorRotation();

	FRotator ImpactRotation = FRotator(CharacterRotation.Pitch - FMath::FRandRange(-75.f, -105.f), CharacterRotation.Yaw, CharacterRotation.Roll);
	FVector BloodScale = FVector(UKismetMathLibrary::RandomFloatInRange(2.5f, 10.f), UKismetMathLibrary::RandomFloatInRange(2.5f, 10.f), UKismetMathLibrary::RandomFloatInRange(2.5f, 10.f));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultHitBlood, ImpactPoint, ImpactRotation, BloodScale, true, EPSCPoolMethod::AutoRelease, true);
}

void UHealthComponent::SpawnDeadBlood()
{
	FHitResult WorldSplashHitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerCharacter);

	FVector HeadLocation = OwnerCharacter->GetMesh()->GetSocketLocation(FName("neck_01"));
	FVector SplashEndLocation = FVector(HeadLocation.X, HeadLocation.Y, HeadLocation.Z - 300.f);

	bool bWorldSplashHit = GetWorld()->LineTraceSingleByChannel(WorldSplashHitResult, HeadLocation, SplashEndLocation, ECollisionChannel::ECC_Visibility, QueryParams);

	if (bWorldSplashHit) {
		TObjectPtr<UMaterialInterface> WorldSplashBlood = DeadBloods[UKismetMathLibrary::RandomInteger(DeadBloods.Num())];

		FVector DecalSize = FVector(1.f, UKismetMathLibrary::RandomFloatInRange(38.f, 64.f), UKismetMathLibrary::RandomFloatInRange(38.f, 64.f));

		FRotator WorldSplashHitNormal = UKismetMathLibrary::MakeRotFromX(WorldSplashHitResult.Normal);

		FRotator DecalRotation = FRotator(WorldSplashHitNormal.Pitch - 180.f, WorldSplashHitNormal.Yaw, WorldSplashHitNormal.Roll);

		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), WorldSplashBlood, DecalSize, WorldSplashHitResult.ImpactPoint, DecalRotation, 120.f);
	}
}

FVector UHealthComponent::CalculateOnDeadVelocity()
{
	FVector DeadVelocity;

	if (LastRecordedHitDirection == EHitDirection::Back) {
		DeadVelocity = UKismetMathLibrary::Subtract_VectorVector(OwnerCharacter->GetCharactersFrontLocation(), OwnerCharacter->GetActorLocation()) * FMath::FRandRange(6.f, 12.f);
	}
	else if (LastRecordedHitDirection == EHitDirection::Left) {
		DeadVelocity = UKismetMathLibrary::Subtract_VectorVector(OwnerCharacter->GetCharactersRightLocation(), OwnerCharacter->GetActorLocation()) * FMath::FRandRange(6.f, 12.f);
	}
	else if (LastRecordedHitDirection == EHitDirection::Right) {
		DeadVelocity = UKismetMathLibrary::Subtract_VectorVector(OwnerCharacter->GetCharactersLeftLocation(), OwnerCharacter->GetActorLocation()) * FMath::FRandRange(6.f, 12.f);
	}
	else {
		DeadVelocity = UKismetMathLibrary::Subtract_VectorVector(OwnerCharacter->GetCharactersBackLocation(), OwnerCharacter->GetActorLocation()) * FMath::FRandRange(6.f, 12.f);
	}

	return DeadVelocity;
}


void UHealthComponent::PerformDead()
{
	OnCharacterDead();

	if (OwnerCharacter->HasAuthority()) {
		Multi_PerformDead();
	}
	else {
		Server_PerformDead();
	}
}

void UHealthComponent::OnCharacterDead()
{
	if (OwnerCharacter->GetGearsComponent()->GetAttachedWeapon()) {
		OwnerCharacter->GetGearsComponent()->GetAttachedWeapon()->StopAttack();
		OwnerCharacter->GetGearsComponent()->GetAttachedWeapon()->HandleDetachment();
	}

	OwnerCharacter->GetCapsuleComponent()->SetCollisionProfileName(FName("NoCollision"));
	OwnerCharacter->GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	OwnerCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	OwnerCharacter->GetMesh()->SetAllBodiesBelowSimulatePhysics(FName("pelvis"), true, true);

	FVector DeadVelocity = CalculateOnDeadVelocity();

	OwnerCharacter->GetMesh()->AddImpulse(DeadVelocity, FName("neck_01"), true);

	SpawnDeadBlood();
}

void UHealthComponent::Server_PerformDead_Implementation()
{
	Multi_PerformDead();
}

void UHealthComponent::Multi_PerformDead_Implementation()
{
	if (!OwnerCharacter->IsLocallyControlled()) {
		OnCharacterDead();
	}
}
