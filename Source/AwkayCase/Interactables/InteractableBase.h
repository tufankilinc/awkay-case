// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableStructure.h"
#include "InteractableBase.generated.h"

class ACharacterBase;

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class AWKAYCASE_API AInteractableBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> InteractableMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USphereComponent> InteractableSphere;
	
public:	
	AInteractableBase();

protected:
	virtual void BeginPlay() override;

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Assets")
		FInteractableStructure InteractableData;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
		FTimerHandle InteractionTimer; // For holding related actions

public:	
	UFUNCTION(BlueprintGetter)
		FInteractableStructure GetInteractableData() const { return InteractableData; };

	UFUNCTION()
		void StartInteraction(ACharacterBase* Interactor);

	UFUNCTION()
		void PerformLongInteraction();

	UFUNCTION()
		void EndInteraction(ACharacterBase* Interactor);

	UFUNCTION()
		void ClearInteractionTimer();

};
