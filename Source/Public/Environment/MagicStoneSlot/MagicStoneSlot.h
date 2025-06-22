// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Interaction/Focusable.h"
#include "Components/Interaction/IInteractable.h"
#include "GameFramework/Actor.h"
#include "Item System/ItemData.h"
#include "MagicStoneSlot.generated.h"

class UInventoryItemObject;
class UItemDataAsset;
class UInventoryComponent;
class UNavModifierGroupController;
class ANavModifierVolume;
class UBoxComponent;

UCLASS()
class FAITHINABYSS_API AMagicStoneSlot : public AActor, public IInteractable, public IFocusable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMagicStoneSlot();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Magic Stone Slot")
	UBoxComponent* InteractionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Magic Stone Slot")
	UNavModifierGroupController* GroupController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Magic Stone Slot")
	UStaticMeshComponent* SlotMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Magic Stone Slot")
	UStaticMeshComponent* MagicStoneMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Magic Stone Slot")
	UInventoryComponent* Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Magic Stone Slot")
	UItemDataAsset* MagicStoneItemData;

	// ----------------- FUNCTIONS -----------------
	UFUNCTION(BlueprintImplementableEvent, Category="Magic Stone Slot")
	void OnStoneSet(const FItemData& ItemData);

	UFUNCTION(BlueprintImplementableEvent, Category="Magic Stone Slot")
	void OnStoneRemoved();

	UFUNCTION(BlueprintCallable, Category="Magic Stone Slot")
	bool HasStone() const
	{
		return bHasStone;
	}

	bool TrySetStone(UInventoryComponent* InventoryToTakeFrom);
	bool TryRemoveStone(UInventoryComponent* InventoryToPutTo);

	virtual void Activate();
	virtual void Deactivate();

public:
	virtual void Interact_Implementation(AActor* Caller) override;

private:
	bool bIsActive;
	bool bHasStone;
};
