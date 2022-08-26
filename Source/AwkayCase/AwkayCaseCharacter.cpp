// Copyright Epic Games, Inc. All Rights Reserved.

#include "AwkayCaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

AAwkayCaseCharacter::AAwkayCaseCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetIsReplicated(true);

	TurnRateGamepad = 50.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MinAnalogWalkSpeed = 5.f;
	GetCharacterMovement()->AirControl = 0.1f;
	GetCharacterMovement()->MaxAcceleration = 1024.f;

	CharactersFrontLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("FrontLocation"));
	CharactersFrontLocation->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	CharactersFrontLocation->SetRelativeLocation(FVector(0.f, 300.f, 90.f));
	CharactersFrontLocation->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CharactersFrontLocation->SetupAttachment(GetMesh());

	CharactersBackLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("BackLocation"));
	CharactersBackLocation->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	CharactersBackLocation->SetRelativeLocation(FVector(0.f, -300.f, 90.f));
	CharactersBackLocation->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CharactersBackLocation->SetupAttachment(GetMesh());

	CharactersLeftLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftLocation"));
	CharactersLeftLocation->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	CharactersLeftLocation->SetRelativeLocation(FVector(300.f, 0.f, 90.f));
	CharactersLeftLocation->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CharactersLeftLocation->SetupAttachment(GetMesh());

	CharactersRightLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("RightLocation"));
	CharactersRightLocation->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	CharactersRightLocation->SetRelativeLocation(FVector(-300.f, 0.f, 90.f));
	CharactersRightLocation->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CharactersRightLocation->SetupAttachment(GetMesh());

	SetReplicates(true);
	bAlwaysRelevant = true;

}

void AAwkayCaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AAwkayCaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AAwkayCaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AAwkayCaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AAwkayCaseCharacter::LookUpAtRate);

}

void AAwkayCaseCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AAwkayCaseCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AAwkayCaseCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAwkayCaseCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
