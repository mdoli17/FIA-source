// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/MagicStoneSlot/MagicStoneSlot.h"

#include "Components/BoxComponent.h"
#include "Components/Navigation/NavModifierGroupController.h"
#include "Item System/InventoryComponent.h"


// Sets default values
AMagicStoneSlot::AMagicStoneSlot()
{
	bIsActive = false;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	GroupController = CreateDefaultSubobject<UNavModifierGroupController>(TEXT("Nav Modifier Group Controller"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	SlotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot Mesh"));
	MagicStoneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magic Stone Mesh"));

	InteractionBox->SetupAttachment(RootComponent);
	SlotMesh->SetupAttachment(InteractionBox);
	MagicStoneMesh->SetupAttachment(SlotMesh);
}

void AMagicStoneSlot::Interact_Implementation(AActor* Caller)
{
	UInventoryComponent* CallerInventory;
	if (CallerInventory = Caller->GetComponentByClass<UInventoryComponent>(); CallerInventory == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Caller doesn't have inventory component"));
		return;
	}

	if (!bIsActive)
	{
		if (!TrySetStone(CallerInventory)) return;

		Activate();
	}
	else
	{
		if (!TryRemoveStone(CallerInventory)) return;

		Deactivate();
	}
}

bool AMagicStoneSlot::TrySetStone(UInventoryComponent* InventoryToTakeFrom)
{
	// TODO: Other function for checking item availability maybe better.
	if (!InventoryToTakeFrom->HasItem(MagicStoneItemData->Data.Id))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Caller doesn't necessary item in inventory"));

		return false;
	}

	const UInventoryItemObject* InventoryItemObject = InventoryToTakeFrom->TryMoveItemWithId(MagicStoneItemData->Data.Id, Inventory);

	if (!InventoryItemObject)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Couldn't move necessary item"));

		return false;
	}

	bHasStone = true;

	OnStoneSet(InventoryItemObject->GetItemData());

	return true;
}

bool AMagicStoneSlot::TryRemoveStone(UInventoryComponent* InventoryToPutTo)
{
	const UInventoryItemObject* InventoryItemObject = Inventory->TryMoveItemWithId(MagicStoneItemData->Data.Id, InventoryToPutTo);
	if (!InventoryItemObject)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Couldn't move necessary item"));
		return false;
	}


	bHasStone = false;

	OnStoneRemoved();

	return true;
}


void AMagicStoneSlot::Activate()
{
	if (bIsActive) return;

	GroupController->ActivateModifiers();
	bIsActive = true;
}

void AMagicStoneSlot::Deactivate()
{
	if (!bIsActive) return;

	GroupController->DeactivateModifiers();
	bIsActive = false;
}
