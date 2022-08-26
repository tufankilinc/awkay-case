// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStructure.h"
#include "ItemBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class AWKAYCASE_API AItemBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> ItemMesh;
	
public:	
	AItemBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Structure")
		FItemStructure ItemData;

public:	
	UFUNCTION()
		UStaticMeshComponent* GetMesh() const { return ItemMesh; };

	UFUNCTION()
		void SetItemData(FItemStructure ItemStructure);

};
