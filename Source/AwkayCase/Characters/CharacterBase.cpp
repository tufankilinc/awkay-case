// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "AwkayCase/Combat/HealthComponent.h"
#include "AwkayCase/Combat/CombatManagerComponent.h"
#include "AwkayCase/Inventories/GearsComponent.h"
#include "AwkayCase/States/StateManagerComponent.h"
#include "AwkayCase/Animations/MontageManagerComponent.h"
#include "AwkayCase/Game/AwkayGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	GearsComponent = CreateDefaultSubobject<UGearsComponent>(TEXT("Gears"));

	CombatManager = CreateDefaultSubobject<UCombatManagerComponent>(TEXT("Combat"));

	StateManager = CreateDefaultSubobject<UStateManagerComponent>(TEXT("State Manager"));

	MontageManager = CreateDefaultSubobject<UMontageManagerComponent>(TEXT("Montage Manager"));

	SetReplicates(true);

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeCharacterData(CharacterID);

	HealthComponent->SetOwnerCharacter(this);
	GearsComponent->SetOwnerCharacter(this);
	CombatManager->SetOwnerCharacter(this);
	MontageManager->SetOwnerCharacter(this);

	// Set values from character properties data
	// ------------------------------------------

	GetCharacterMovement()->MaxWalkSpeed = PropertiesData.MovementSpeed.FinalValue;
	GetCharacterMovement()->JumpZVelocity = PropertiesData.JumpHeight.FinalValue;

	HealthComponent->SetMaxHealth(PropertiesData.Health.FinalValue, true);
	
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ACharacterBase, CharacterData, COND_None);
	DOREPLIFETIME_CONDITION(ACharacterBase, PropertiesData, COND_None);
}

bool ACharacterBase::SetCharacterID(FName ID)
{
	UE_LOG(LogTemp, Warning, TEXT("Set character id: %s"), *ID.ToString());
	if (ID != NAME_None) {
		CharacterID = ID;
		UE_LOG(LogTemp, Warning, TEXT("Setted character id: %s"), *CharacterID.ToString());
		return true;
	}

	return false;
}

void ACharacterBase::InitializeCharacterData(FName ID)
{
	if (ID == NAME_None) return;

	UE_LOG(LogTemp, Warning, TEXT("%s"), *CharacterID.ToString());
	TObjectPtr<UAwkayGameInstance> GameInstance = Cast<UAwkayGameInstance>(GetWorld()->GetGameInstance());

	if (IsValid(GameInstance.Get())) {
		CharacterData = GameInstance->GetCharacterDataFromList(CharacterID);
		PropertiesData = GameInstance->GetCharacterPropertyDataFromList(CharacterID);
	}
}

void ACharacterBase::TakeDamage(ACharacterBase* Character, FVector ImpactPoint, float TakenDamage)
{
	UE_LOG(LogTemp, Warning, TEXT("Character Health: %.2f"), PropertiesData.Health.FinalValue);
	UE_LOG(LogTemp, Warning, TEXT("Character Health: %.2f"), GetHealthComponent()->GetHealth());
	HealthComponent->HandleDamage(Character, ImpactPoint, TakenDamage);
}

void ACharacterBase::PerformAttack(ECombatTriggerClick TriggerType)
{
	if (GearsComponent->GetAttachedWeapon()) {
		CombatManager->HandleAttack(TriggerType);
	}
}

void ACharacterBase::PerformJump()
{
	/*bool bIsJumping = StateManager->MovementState == EMovementState::Jumping;

	if (!bIsJumping && ActionProperties.bCanJump) {
		StateManager->MovementState = EMovementState::Jumping;
		ActionProperties.bCanJump = false;
		Jump();
	}*/
}

void ACharacterBase::PerformCrouch()
{
	bool bIsCrouching = StateManager->MovementState == EMovementState::Crouching;

	if (bIsCrouching) {
		UnCrouch();
		StateManager->MovementState = EMovementState::Standing;
	}
	else {
		Crouch();
		StateManager->MovementState = EMovementState::Crouching;
	}
}
