// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "InventoryEntry.generated.h"

class UInventoryItemObject;
class UButton;
class UTextBlock;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemClicked, UInventoryItemObject* /* Item */);
DECLARE_MULTICAST_DELEGATE(FOnItemUpdatedDelegate);

/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UInventoryEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	FOnItemClicked OnItemClicked;
	FOnItemUpdatedDelegate OnItemUpdated;

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* NameField;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* CountField;

	UPROPERTY(meta=(BindWidget))
	UButton* Button;

private:
	UFUNCTION()
	void ButtonClickHandler();

	UFUNCTION()
	void InventoryItemDataUpdateHandler();

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UInventoryItemObject* InventoryItemData;
};
