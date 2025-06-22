// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UInventoryItemPreviewWidget;
class UInventoryListingWidget;
class UTextBlock;
class UInventoryComponent;
class UButton;
class UInventoryItemObject;
class UListView;

/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UInventoryListingWidget* InventoryListingWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UInventoryItemPreviewWidget* ItemPreviewWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UButton* UseButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UButton* DropButton;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void ItemSelectHandler(UInventoryItemObject* Item);

	UFUNCTION()
	void ItemSelectionClearHandler();

	UFUNCTION()
	void UseItemClickHandler();

	UFUNCTION()
	void DropItemClickHandler();

	UFUNCTION(BlueprintImplementableEvent, Category="Inventory")
	void OnItemSelected(UInventoryItemObject* InventoryItemData);

	UFUNCTION(BlueprintImplementableEvent, Category="Inventory")
	void OnItemAdded(UInventoryItemObject* InventoryItemData);

	UFUNCTION(BlueprintImplementableEvent, Category="Inventory")
	void OnItemRemoved(UInventoryItemObject* InventoryItemData);

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	UInventoryComponent* InventoryComp;

	UPROPERTY(BlueprintReadOnly, Category="Item")
	TObjectPtr<UInventoryItemObject> SelectedItem;

public:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void Setup(UInventoryComponent* InventoryComponent);

private:
	UFUNCTION()
	void ItemAddHandler(UInventoryItemObject* InventoryItemData);

	UFUNCTION()
	void ItemRemoveHandler(UInventoryItemObject* InventoryItemData);
};
