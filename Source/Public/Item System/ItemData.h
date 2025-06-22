#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Data")
	FName Id;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Data")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Data")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Data")
	float Weight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Data")
	TObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Data")
	FGameplayTagContainer GrantingTags;
};
