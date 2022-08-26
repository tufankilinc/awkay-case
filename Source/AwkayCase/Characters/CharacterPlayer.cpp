// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "AwkayCase/Inventories/InventoryComponent.h"
#include "AwkayCase/Inventories/GearsComponent.h"
#include "AwkayCase/Game/AwkayPlayerController.h"

ACharacterPlayer::ACharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterID = FName("ID_C_Player");

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.f, 40.f, 180.f));
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	FollowCamera->bUsePawnControlRotation = false;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Player Inventory"));

}

void ACharacterPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACharacterPlayer::OnInteract);
	PlayerInputComponent->BindAction("MousePrimaryAction", IE_Pressed, this, &ACharacterPlayer::TriggerAttack);
	/*PlayerInputComponent->BindAction("MouseSecondaryAction", IE_Pressed, this, &ACharacterPlayer::OnInteract);*/
	PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &ACharacterPlayer::ToggleBackpack);
	PlayerInputComponent->BindAction("SwitchWeaponNext", IE_Pressed, this, &ACharacterPlayer::SwitchWeaponsNext);
	PlayerInputComponent->BindAction("SwitchWeaponPrev", IE_Pressed, this, &ACharacterPlayer::SwitchWeaponsPrev);
	
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void ACharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// INPUT ACTIONS 

void ACharacterPlayer::OnInteract()
{

}

void ACharacterPlayer::Server_OnInteract_Implementation()
{

}

void ACharacterPlayer::ToggleBackpack()
{
	TObjectPtr<AAwkayPlayerController> PlayerController = Cast<AAwkayPlayerController>(GetController());

	if (IsValid(PlayerController.Get())) {
		PlayerController->ToggleBackpackWidget();
	}
}

void ACharacterPlayer::SwitchWeaponsNext()
{
	GetGearsComponent()->SwitchWeaponsInc();
}

void ACharacterPlayer::SwitchWeaponsPrev()
{
	GetGearsComponent()->SwitchWeaponsDec();
}

void ACharacterPlayer::TriggerAttack()
{
	PerformAttack(ECombatTriggerClick::Press);
}
