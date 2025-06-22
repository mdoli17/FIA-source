// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item System/InventoryComponent.h"
#include "InventoryListingWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSelectedDelegate, UInventoryItemObject*, InventoryItemObject);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemSelectionClearedDelegate);

class UTextBlock;
class UListView;
/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UInventoryListingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void Setup(UInventoryComponent* InventoryComponent);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void Clear();

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnItemSelectedDelegate OnItemSelected;

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnItemSelectionClearedDelegate OnItemSelectionCleared;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UListView* Contents;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* OwnerNameField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* WeightTextField;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UInventoryComponent* InventoryComp;

private:
	void EntryWidgetGenerateHandler(UUserWidget& EntryWidget);

	UFUNCTION()
	void ItemAddHandler(UInventoryItemObject* InventoryItemObject);

	UFUNCTION()
	void ItemRemoveHandler(UInventoryItemObject* InventoryItemObject);

	UFUNCTION()
	void InventoryUpdateHandler();

	UFUNCTION()
	void InventoryEntryClickHandler(UInventoryItemObject* InventoryItemObject);

	FDelegateHandle EntryWidgetGenerateDelegateHandle;
};
