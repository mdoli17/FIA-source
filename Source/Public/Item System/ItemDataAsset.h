// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemAction.h"
#include "ItemData.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

class APickupItem;

UCLASS(BlueprintType)
class FAITHINABYSS_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Data")
	FItemData Data;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Action")
	TSubclassOf<UItemAction> ActionAsset;
};
