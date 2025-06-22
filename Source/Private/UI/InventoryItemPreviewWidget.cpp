// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryItemPreviewWidget.h"

#include "Components/TextBlock.h"
#include "Item System/ItemPreviewActor.h"

void UInventoryItemPreviewWidget::Setup(const FItemData ItemData)
{
	NameField->SetText(ItemData.Name);
	DescriptionField->SetText(ItemData.Description);
	WeightField->SetText(FText::FromString(FString::Printf(TEXT("%f"), ItemData.Weight)));

	SetVisibility(ESlateVisibility::Visible);

	check(ItemPreviewActor);
	ItemPreviewActor->ResetRotation(true);
	ItemPreviewActor->Initialize(ItemData);
}

void UInventoryItemPreviewWidget::Clear()
{
	SetVisibility(ESlateVisibility::Hidden);

	// check(ItemPreviewActor);
	ItemPreviewActor->Deinitialize();
}

void UInventoryItemPreviewWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);

	if (ItemPreviewActor != nullptr) return;

	check(ItemPreviewActorClass);

	// TODO: Creating and Destroying actor everytime this widget is opened or closed is not efficient. Think of a better way
	ItemPreviewActor = GetWorld()->SpawnActor<AItemPreviewActor>(ItemPreviewActorClass, ItemPreviewActorSpawnTransform);
}

void UInventoryItemPreviewWidget::NativeDestruct()
{
	Super::NativeDestruct();
	// TODO: Creating and Destroying actor everytime this widget is opened or closed is not efficient. Think of a better way
	GetWorld()->DestroyActor(ItemPreviewActor);
	ItemPreviewActor = nullptr;
}

FReply UInventoryItemPreviewWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// Right mouse button is used to reset rotation
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		// Reset if left mouse button is not pressed
		if (!InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
			ItemPreviewActor->ResetRotation();
		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);;
	}

	bIsMouseDown = true;
	LastMousePosition = InMouseEvent.GetScreenSpacePosition();
	ItemPreviewActor->StartRotation();
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UInventoryItemPreviewWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bIsMouseDown = false;
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

FReply UInventoryItemPreviewWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	if (!bIsMouseDown) return Reply;

	const FVector2D MousePosition = InMouseEvent.GetScreenSpacePosition();

	if (LastMousePosition - MousePosition == FVector2D::Zero()) return Reply;

	const FVector2D Delta = (LastMousePosition - MousePosition);

	ItemPreviewActor->Rotate(Delta);

	LastMousePosition = MousePosition;

	return Reply;
}

void UInventoryItemPreviewWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bIsMouseDown = InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton);
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}
