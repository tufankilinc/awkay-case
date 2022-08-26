#pragma once

#include "InteractableStructure.generated.h"

UENUM(BlueprintType)
enum class EInteractableCategory : uint8
{
	None			= 0		UMETA(DisplayName = "None"),
	Pickupable		= 1		UMETA(DisplayName = "Pickupable")
};

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	None			= 0		UMETA(DisplayName = "None"),
	Pickup			= 1		UMETA(DisplayName = "Pickup"),
	Trigger			= 2		UMETA(DisplayName = "Trigger")
};

UENUM(BlueprintType)
enum class EInteractionMethod : uint8
{
	Press			= 0		UMETA(DisplayName = "Press"),
	Hold			= 1		UMETA(DisplayName = "Hold")
};

USTRUCT(BlueprintType)
struct FInteractableStructure
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		FName InteractableID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Identifier")
		EInteractableCategory InteractableCategory;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Editor Related | Details")
		FText Name;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Editor Related | Details")
		FText Description;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Preview")
		TSoftObjectPtr<UStaticMesh> StaticMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Actions")
		EInteractionMethod InteractionMethod;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Actions")
		EInteractionType InteractionType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Definitions")
		FName RelatedItemID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Definitions")
		float SphereRadius = 100.f;

};