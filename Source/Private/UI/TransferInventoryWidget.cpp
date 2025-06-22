// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TransferInventoryWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/InventoryItemPreviewWidget.h"
#include "UI/InventoryListingWidget.h"

void UTransferInventoryWidget::Setup(UInventoryComponent* InventoryComponentA, UInventoryComponent* InventoryComponentB)
{
	InventoryA = InventoryComponentA;
	InventoryB = InventoryComponentB;

	InventoryListingWidgetA->Setup(InventoryA);
	InventoryListingWidgetB->Setup(InventoryB);

	TransferButton->SetVisibility(ESlateVisibility::Hidden);
}

FReply UTransferInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
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

		InventoryListingWidgetA->Clear();
		InventoryListingWidgetB->Clear();

		return FReply::Handled();
	}
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UTransferInventoryWidget::NativeConstruct()
{
	Super::NativeOnInitialized();

	InventoryListingWidgetA->OnItemSelected.AddUniqueDynamic(this, &UTransferInventoryWidget::ItemFromInventoryASelectHandler);
	InventoryListingWidgetA->OnItemSelectionCleared.AddUniqueDynamic(this, &UTransferInventoryWidget::ItemSelectionClearHandler);

	InventoryListingWidgetB->OnItemSelected.AddUniqueDynamic(this, &UTransferInventoryWidget::ItemFromInventoryBSelectHandler);
	InventoryListingWidgetB->OnItemSelectionCleared.AddUniqueDynamic(this, &UTransferInventoryWidget::ItemSelectionClearHandler);

	TransferButton->OnClicked.AddUniqueDynamic(this, &UTransferInventoryWidget::TransferButtonClickHandler);
}

void UTransferInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();

	InventoryListingWidgetA->OnItemSelected.RemoveDynamic(this, &UTransferInventoryWidget::ItemFromInventoryASelectHandler);
	InventoryListingWidgetA->OnItemSelectionCleared.RemoveDynamic(this, &UTransferInventoryWidget::ItemSelectionClearHandler);

	InventoryListingWidgetB->OnItemSelected.RemoveDynamic(this, &UTransferInventoryWidget::ItemFromInventoryBSelectHandler);
	InventoryListingWidgetB->OnItemSelectionCleared.RemoveDynamic(this, &UTransferInventoryWidget::ItemSelectionClearHandler);

	TransferButton->OnClicked.RemoveDynamic(this, &UTransferInventoryWidget::TransferButtonClickHandler);
}


void UTransferInventoryWidget::ItemFromInventoryASelectHandler(UInventoryItemObject* ItemObject)
{
	SelectedItem = ItemObject;
	ItemPreviewWidget->Setup(ItemObject->GetItemData());
	TransferDirection = Put;
	TransferTextBlock->SetText(PutText);
	TransferButton->SetVisibility(ESlateVisibility::Visible);
}

void UTransferInventoryWidget::ItemFromInventoryBSelectHandler(UInventoryItemObject* ItemObject)
{
	SelectedItem = ItemObject;
	ItemPreviewWidget->Setup(ItemObject->GetItemData());
	TransferDirection = Take;
	TransferTextBlock->SetText(TakeText);
	TransferButton->SetVisibility(ESlateVisibility::Visible);
}

void UTransferInventoryWidget::ItemSelectionClearHandler()
{
	SelectedItem = nullptr;
	ItemPreviewWidget->Clear();
	TransferButton->SetVisibility(ESlateVisibility::Hidden);
}

void UTransferInventoryWidget::TransferButtonClickHandler()
{
	if (TransferDirection == Put)
	{
		InventoryA->TryMoveItem(SelectedItem, InventoryB);
	}
	else if (TransferDirection == Take)
	{
		InventoryB->TryMoveItem(SelectedItem, InventoryA);
	}
}
