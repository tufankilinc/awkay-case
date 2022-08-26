// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AwkayCase/Characters/CharacterBase.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	ItemMesh->SetCollisionProfileName(TEXT("Item"));
	RootComponent = ItemMesh;

}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBase::SetItemData(FItemStructure ItemStructure)
{
	if (ItemStructure.ItemID != NAME_None) {
		ItemData = ItemStructure;
	}
}
