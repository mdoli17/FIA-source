// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item System/InventoryComponent.h"
#include "TransferInventoryWidget.generated.h"

class UTextBlock;
class UButton;
class UInventoryComponent;
class UInventoryItemPreviewWidget;
class UInventoryListingWidget;
/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UTransferInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	enum ETransferDirection
	{
		Put,
		Take
	};

	const FText PutText = FText::FromString("Put");
	const FText TakeText = FText::FromString("Take");

public:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void Setup(UInventoryComponent* InventoryComponentA, UInventoryComponent* InventoryComponentB);

protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UInventoryListingWidget* InventoryListingWidgetA;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UInventoryListingWidget* InventoryListingWidgetB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UInventoryItemPreviewWidget* ItemPreviewWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UButton* TransferButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* TransferTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UInventoryComponent* InventoryA;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UInventoryComponent* InventoryB;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UInventoryItemObject* SelectedItem;

	UFUNCTION()
	void ItemFromInventoryASelectHandler(UInventoryItemObject* ItemObject);

	UFUNCTION()
	void ItemFromInventoryBSelectHandler(UInventoryItemObject* ItemObject);

	UFUNCTION()
	void ItemSelectionClearHandler();

	UFUNCTION()
	void TransferButtonClickHandler();

private:
	ETransferDirection TransferDirection;
};
