// Fill out your copyright notice in the Description page of Project Settings.


#include "AwkayPlayerController.h"

void AAwkayPlayerController::ToggleBackpackWidget()
{
	ToggleBackpack_Implementation();
	bIsBackpackDisplaying = !bIsBackpackDisplaying;
}
