// Copyright Epic Games, Inc. All Rights Reserved.

#include "AwkayCaseGameMode.h"
#include "AwkayCaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAwkayCaseGameMode::AAwkayCaseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
