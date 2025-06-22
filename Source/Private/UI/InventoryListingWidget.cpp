// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryListingWidget.h"

#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "UI/InventoryEntry.h"

void UInventoryListingWidget::Setup(UInventoryComponent* InventoryComponent)
{
	check(InventoryComponent);

	InventoryComp = InventoryComponent;

	InventoryComp->OnItemAdded.AddUniqueDynamic(this, &UInventoryListingWidget::ItemAddHandler);
	InventoryComp->OnItemRemoved.AddUniqueDynamic(this, &UInventoryListingWidget::ItemRemoveHandler);
	InventoryComp->OnInventoryUpdated.AddUniqueDynamic(this, &UInventoryListingWidget::InventoryUpdateHandler);

	const TArray<UInventoryItemObject*> Items = InventoryComp->GetItems();

	Contents->SetListItems(Items);
	OwnerNameField->SetText(FText::FromString(InventoryComp->GetOwnerName()));
	WeightTextField->SetText(FText::Join(FText::FromString(FString::Printf(TEXT("/"))), InventoryComp->GetInventoryWeightText(), InventoryComp->GetInventoryMaxWeightText()));
}

void UInventoryListingWidget::Clear()
{
	Contents->ClearListItems();
	OwnerNameField->SetText(FText::GetEmpty());
	WeightTextField->SetText(FText::GetEmpty());
}

void UInventoryListingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	EntryWidgetGenerateDelegateHandle = Contents->OnEntryWidgetGenerated().AddUObject(this, &UInventoryListingWidget::EntryWidgetGenerateHandler);
}

void UInventoryListingWidget::NativeDestruct()
{
	Super::NativeDestruct();
	Contents->OnEntryWidgetGenerated().Remove(EntryWidgetGenerateDelegateHandle);
}

void UInventoryListingWidget::EntryWidgetGenerateHandler(UUserWidget& EntryWidget)
{
	if (UInventoryEntry* InventoryEntry = Cast<UInventoryEntry>(&EntryWidget))
	{
		InventoryEntry->OnItemClicked.AddUObject(this, &UInventoryListingWidget::InventoryEntryClickHandler);
	}
}

void UInventoryListingWidget::ItemAddHandler(UInventoryItemObject* InventoryItemObject)
{
	Contents->AddItem(InventoryItemObject);
}

void UInventoryListingWidget::ItemRemoveHandler(UInventoryItemObject* InventoryItemObject)
{
	Contents->RemoveItem(InventoryItemObject);
	OnItemSelectionCleared.Broadcast();
}

void UInventoryListingWidget::InventoryUpdateHandler()
{
	WeightTextField->SetText(FText::Join(FText::FromString(FString::Printf(TEXT("/"))), InventoryComp->GetInventoryWeightText(), InventoryComp->GetInventoryMaxWeightText()));
}

void UInventoryListingWidget::InventoryEntryClickHandler(UInventoryItemObject* InventoryItemObject)
{
	OnItemSelected.Broadcast(InventoryItemObject);
}
