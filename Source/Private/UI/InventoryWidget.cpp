// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"

#include "Components/Button.h"
#include "Components/ListView.h"
#include "Item System/InventoryComponent.h"
#include "UI/InventoryEntry.h"
#include "UI/InventoryItemPreviewWidget.h"
#include "UI/InventoryListingWidget.h"

void UInventoryWidget::Setup(UInventoryComponent* InventoryComponent)
{
	InventoryComp = InventoryComponent;

	InventoryComp->OnItemAdded.AddUniqueDynamic(this, &UInventoryWidget::ItemAddHandler);
	InventoryComp->OnItemRemoved.AddUniqueDynamic(this, &UInventoryWidget::ItemRemoveHandler);

	InventoryListingWidget->Setup(InventoryComponent);

	UseButton->SetVisibility(ESlateVisibility::Hidden);
	DropButton->SetVisibility(ESlateVisibility::Hidden);
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Tab)
	{
		if (APlayerController* PlayerController = GetOwningPlayer())
		{
			PlayerController->bShowMouseCursor = false;

			const FInputModeGameOnly InputMode;

			PlayerController->SetInputMode(InputMode);
		}
		RemoveFromParent();

		InventoryListingWidget->Clear();

		return FReply::Handled();
	}
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeOnInitialized();
	InventoryListingWidget->OnItemSelected.AddUniqueDynamic(this, &UInventoryWidget::ItemSelectHandler);
	InventoryListingWidget->OnItemSelectionCleared.AddUniqueDynamic(this, &UInventoryWidget::ItemSelectionClearHandler);
	UseButton->OnClicked.AddUniqueDynamic(this, &UInventoryWidget::UseItemClickHandler);
	DropButton->OnClicked.AddUniqueDynamic(this, &UInventoryWidget::DropItemClickHandler);
}

void UInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();
	InventoryListingWidget->OnItemSelected.RemoveDynamic(this, &UInventoryWidget::ItemSelectHandler);
	InventoryListingWidget->OnItemSelectionCleared.RemoveDynamic(this, &UInventoryWidget::ItemSelectionClearHandler);
	UseButton->OnClicked.RemoveDynamic(this, &UInventoryWidget::UseItemClickHandler);
	DropButton->OnClicked.RemoveDynamic(this, &UInventoryWidget::DropItemClickHandler);
}


void UInventoryWidget::ItemSelectHandler(UInventoryItemObject* Item)
{
	SelectedItem = Item;

	ItemPreviewWidget->Setup(Item->GetItemData());
	UseButton->SetVisibility(ESlateVisibility::Visible);
	DropButton->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryWidget::ItemSelectionClearHandler()
{
	SelectedItem = nullptr;
	ItemPreviewWidget->Clear();
	UseButton->SetVisibility(ESlateVisibility::Hidden);
	DropButton->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryWidget::UseItemClickHandler()
{
	if (SelectedItem == nullptr) return;
	InventoryComp->UseItem(SelectedItem);
}

void UInventoryWidget::DropItemClickHandler()
{
	if (SelectedItem == nullptr) return;
	InventoryComp->DropItem(SelectedItem);
}

void UInventoryWidget::ItemAddHandler(UInventoryItemObject* InventoryItemData)
{
	OnItemAdded(InventoryItemData);
}

void UInventoryWidget::ItemRemoveHandler(UInventoryItemObject* InventoryItemData)
{
	OnItemRemoved(InventoryItemData);
	if (SelectedItem == InventoryItemData)
	{
		SelectedItem = nullptr;
		ItemPreviewWidget->Clear();
	}
}
