// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AwkayCase/Characters/CharacterBase.h"
#include "Kismet/Gameplaystatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundCue.h"
#include "Net/UnrealNetwork.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon::DestroyActor()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Destroy();
}

void AWeapon::HandleDetachment()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetMassOverrideInKg(NAME_None, 100.f);
}

void AWeapon::SetOwnerCharacter(ACharacterBase* Character)
{
	if (Character != nullptr) {
		OwnerCharacter = Character;
		ActorsToIgnore.Add(OwnerCharacter);
		ActorsToIgnore.Add(this);
	};
}

void AWeapon::SetWeaponData(FItemStructure ItemStructure, FWeaponStructure WeaponStructure)
{
	if (ItemStructure.ItemID != NAME_None && WeaponStructure.ItemID != NAME_None) {
		SetItemData(ItemStructure);
		WeaponData = WeaponStructure;

		UStaticMesh* Mesh = Cast<UStaticMesh>(UKismetSystemLibrary::LoadAsset_Blocking(ItemData.StaticMesh));

		if (Mesh) {
			GetMesh()->SetStaticMesh(Mesh);
		}
	};
}

void AWeapon::PerformAttack()
{
	TArray<FName> AttachedSockets = GetMesh()->GetAllSocketNames();

	for (int32 i = 0; i < AttachedSockets.Num(); i++) {
		FHitResult OutHit;
		FVector DrawAtLocation = GetMesh()->GetSocketLocation(AttachedSockets[i]);

		bool bHit;

		//We're create lines each tick and fill the holes

		if (bDrawLine) {
			bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), LastLinePoints[i], DrawAtLocation, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false, ActorsToIgnore, EDrawDebugTrace::None, OutHit, true, FColor::Purple, FLinearColor::Blue, 1.f);
			LastLinePoints[i] = DrawAtLocation;
		}
		else {
			bHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), DrawAtLocation, DrawAtLocation, 2.f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false, ActorsToIgnore, EDrawDebugTrace::None, OutHit, true, FColor::Red, FLinearColor::Blue, 1.f);
		}

		LastLinePoints.Add(DrawAtLocation);

		if (bHit) {
			if (IILivingThing* LivingThing = Cast<IILivingThing>(OutHit.GetActor())) {
				float Damage = UKismetMathLibrary::RandomFloatInRange(WeaponData.MinDamage, WeaponData.MaxDamage);
				LivingThing->TakeDamage(OwnerCharacter, OutHit.ImpactPoint, Damage);
				ActorsToIgnore.Add(OutHit.GetActor());
			}
		}
	}

	bDrawLine = true;
}

// TODO: Multicast
void AWeapon::PlayAttackSound()
{
	float Multiplier = OwnerCharacter->IsLocallyControlled() ? 0.5f : 0.25f;
	//UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponData.AttackSound, GetActorLocation(), Multiplier);
}

void AWeapon::StartAttack()
{
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AWeapon::PerformAttack, 0.01f, true, 0.f);

	if (!OwnerCharacter->HasAuthority()) {
		Server_StartAttack(OwnerCharacter);
	}
	else {
		Multi_StartAttack(OwnerCharacter);
	}
}

void AWeapon::Server_StartAttack_Implementation(ACharacterBase* Character)
{
	Multi_StartAttack(Character);
}

void AWeapon::Multi_StartAttack_Implementation(ACharacterBase* Character)
{
	if (!Character->IsLocallyControlled()) {
		//PlayAttackSound();
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AWeapon::PerformAttack, 0.01f, true, 0.f);
	}
}

void AWeapon::StopAttack()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackTimer);

	ActorsToIgnore.Empty();
	ActorsToIgnore.Add(OwnerCharacter);
	ActorsToIgnore.Add(this);

	bDrawLine = false;
	LastLinePoints.Empty();

	if (!OwnerCharacter->HasAuthority()) {
		Server_StopAttack(OwnerCharacter);
	}
	else {
		Multi_StopAttack(OwnerCharacter);
	}
}

void AWeapon::Server_StopAttack_Implementation(ACharacterBase* Character)
{
	Multi_StopAttack(Character);
}

void AWeapon::Multi_StopAttack_Implementation(ACharacterBase* Character)
{
	if (!Character->IsLocallyControlled()) {
		GetWorld()->GetTimerManager().ClearTimer(AttackTimer);

		ActorsToIgnore.Empty();
		ActorsToIgnore.Add(Character);
		ActorsToIgnore.Add(this);

		bDrawLine = false;
		LastLinePoints.Empty();
	}
}
