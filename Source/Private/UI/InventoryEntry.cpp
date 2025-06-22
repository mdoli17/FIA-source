// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryEntry.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Item System/InventoryComponent.h"

void UInventoryEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	InventoryItemData = Cast<UInventoryItemObject>(ListItemObject);

	check(InventoryItemData);

	InventoryItemData->OnInventoryItemDataUpdated.AddUniqueDynamic(this, &UInventoryEntry::InventoryItemDataUpdateHandler);

	const FText Name = InventoryItemData->GetItemData().Name;
	const FText Count = FText::FromString(FString::Printf(TEXT("%d"), InventoryItemData->GetQuantity()));

	NameField->SetText(Name);
	CountField->SetText(Count);
}

void UInventoryEntry::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddUniqueDynamic(this, &UInventoryEntry::ButtonClickHandler);
}

void UInventoryEntry::NativeDestruct()
{
	Super::NativeDestruct();

	Button->OnClicked.RemoveDynamic(this, &UInventoryEntry::ButtonClickHandler);
}

void UInventoryEntry::ButtonClickHandler()
{
	OnItemClicked.Broadcast(InventoryItemData);
}

void UInventoryEntry::InventoryItemDataUpdateHandler()
{
	const FText Count = FText::FromString(FString::Printf(TEXT("%d"), InventoryItemData->GetQuantity()));
	CountField->SetText(Count);
	OnItemUpdated.Broadcast();
}
