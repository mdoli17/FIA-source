// Fill out your copyright notice in the Description page of Project Settings.


#include "Item System/InventoryComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

#pragma region Public Functions
bool UInventoryComponent::TryAddItem(const APickupItem* PickupItem)
{
	check(PickupItem);

	const UItemDataAsset* ItemDataAsset = PickupItem->GetItemDataAsset();
	const FItemData ItemData = ItemDataAsset->Data;

	if (!ItemCanBeAdded(ItemData)) return false;

	if (Inventory.Contains(ItemData.Id))
		IncreaseItemCount(ItemData);
	else
	{
		UInventoryItemObject* InventoryItemObject = UInventoryItemObject::Create(PickupItem);
		AddNewItem(InventoryItemObject);
	}

	return true;
}

bool UInventoryComponent::TryMoveItem(UInventoryItemObject* ItemObjectToMove, UInventoryComponent* OtherInventory)
{
	check(ItemObjectToMove);
	check(OtherInventory);

	const FItemData ItemData = ItemObjectToMove->GetItemData();

	// If item doesn't exist in our inventory, return false
	if (!Inventory.Contains(ItemData.Id)) return false;

	// If item can't be added to other inventory, return false
	if (!OtherInventory->ItemCanBeAdded(ItemData)) return false;

	OtherInventory->AddItemObject(ItemObjectToMove);

	// Remove item from our inventory (Will always be true, since existence is checked above)
	RemoveItemObject(ItemObjectToMove);

	return true;
}

UInventoryItemObject* UInventoryComponent::TryMoveItemWithId(const FName ItemId, UInventoryComponent* OtherInventory)
{
	check(Inventory.Contains(ItemId));

	UInventoryItemObject* ItemToGet = Inventory[ItemId];
	const bool MoveSuccessful = TryMoveItem(ItemToGet, OtherInventory);
	return MoveSuccessful ? ItemToGet : nullptr;
}


bool UInventoryComponent::TryMoveItems(UInventoryItemObject* InventoryItemObject, const int32 Amount, UInventoryComponent* OtherInventory)
{
	check(InventoryItemObject);
	check(OtherInventory);

	if (InventoryItemObject->GetQuantity() < Amount) return false;

	const FItemData ItemData = InventoryItemObject->GetItemData();

	if (!Inventory.Contains(ItemData.Id)) return false;

	if (!OtherInventory->ItemsCanBeAdded(ItemData, Amount)) return false;

	for (int i = 0; i < Amount; i++)
	{
		OtherInventory->AddItemObject(InventoryItemObject);
		RemoveItemObject(InventoryItemObject);
	}

	return true;
}


bool UInventoryComponent::UseItem(UInventoryItemObject* InventoryItemObject)
{
	if (InventoryItemObject->GetItemAction()->UseItem(GetOwner(), InventoryItemObject->GetItemData()))
	{
		RemoveItemObject(InventoryItemObject);
		return true;
	}

	return false;
}

void UInventoryComponent::DropItem(UInventoryItemObject* InventoryItemObject)
{
	check(Inventory.Contains(InventoryItemObject->GetItemData().Id));

	RemoveItemObject(InventoryItemObject);

	UClass* Class = InventoryItemObject->GetItemClass();
	const FVector Location = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 25.f;
	const FRotator Rotation = FRotator::ZeroRotator;
	const FActorSpawnParameters SpawnParameters;

	GetWorld()->SpawnActor<APickupItem>(Class, Location, Rotation, SpawnParameters);
}

TArray<UInventoryItemObject*> UInventoryComponent::GetItems()
{
	TArray<UInventoryItemObject*> Items;
	for (TTuple<FName, UInventoryItemObject*> Pair : Inventory)
	{
		Items.Add(Pair.Value);
	}

	return Items;
}

#pragma endregion

#pragma region Private Helpers

bool UInventoryComponent::ItemCanBeAdded(const FItemData& ItemData) const
{
	return CurrentWeight + ItemData.Weight <= MaxWeight;
}

bool UInventoryComponent::ItemsCanBeAdded(const FItemData& ItemData, int32 Amount) const
{
	return CurrentWeight + ItemData.Weight * Amount <= MaxWeight;
}

void UInventoryComponent::AddItemObject(const UInventoryItemObject* InventoryItemObject)
{
	check(InventoryItemObject);

	if (const FItemData ItemData = InventoryItemObject->GetItemData(); Inventory.Contains(ItemData.Id))
		IncreaseItemCount(ItemData);
	else
	{
		UInventoryItemObject* NewInventoryItemObject = UInventoryItemObject::Create(InventoryItemObject);
		AddNewItem(NewInventoryItemObject);
	}
}

void UInventoryComponent::RemoveItemObject(UInventoryItemObject* ExistingItemObject)
{
	check(ExistingItemObject);

	const FItemData ItemData = ExistingItemObject->GetItemData();
	check(Inventory.Contains(ItemData.Id));

	DecreaseItemCount(ItemData);

	if (ExistingItemObject->GetQuantity() == 0)
	{
		Inventory.Remove(ItemData.Id);
		ActiveTags.RemoveTags(ExistingItemObject->GetItemData().GrantingTags);
		OnItemRemoved.Broadcast(ExistingItemObject);
	}
}

void UInventoryComponent::AddNewItem(UInventoryItemObject* InventoryItemObject)
{
	const FItemData ItemToAdd = InventoryItemObject->GetItemData();
	Inventory.Add(ItemToAdd.Id, InventoryItemObject);
	CurrentWeight += ItemToAdd.Weight;
	ActiveTags.AppendTags(ItemToAdd.GrantingTags);
	OnInventoryUpdated.Broadcast();
	OnItemAdded.Broadcast(InventoryItemObject);
}

void UInventoryComponent::IncreaseItemCount(const FItemData& ItemData)
{
	check(Inventory.Contains(ItemData.Id));

	CurrentWeight += ItemData.Weight;
	Inventory[ItemData.Id]->Add();
	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::DecreaseItemCount(const FItemData& ItemData)
{
	check(Inventory.Contains(ItemData.Id));

	CurrentWeight -= ItemData.Weight;
	Inventory[ItemData.Id]->Remove();
	OnInventoryUpdated.Broadcast();
}

#pragma endregion
