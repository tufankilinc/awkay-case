// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(InteractableMesh);

	InteractableSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	InteractableSphere->SetupAttachment(RootComponent);

	InteractableSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractableBase::BeginOverlap);
	InteractableSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractableBase::EndOverlap);

}

void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

}

//void AInteractableBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(AInteractableBase, CurrentProgression);
//}

void AInteractableBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (IILivingThing* LivingThing = Cast<IILivingThing>(OtherActor)) {
		LivingThing->UpdateInteractableReference(this, true);
	}*/
}

void AInteractableBase::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*if (IILivingThing* LivingThing = Cast<IILivingThing>(OtherActor)) {
		LivingThing->UpdateInteractableReference(this, false);
	}*/
}

void AInteractableBase::StartInteraction(ACharacterBase* Interactor)
{
	
}

void AInteractableBase::PerformLongInteraction()
{
	
}

void AInteractableBase::EndInteraction(ACharacterBase* Interactor)
{
	
}

void AInteractableBase::ClearInteractionTimer()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(InteractionTimer)) {
		GetWorld()->GetTimerManager().ClearTimer(InteractionTimer);
	}
}