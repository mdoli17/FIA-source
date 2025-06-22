// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "ItemDataAsset.h"
#include "PickupItem.h"
#include "InventoryComponent.generated.h"

class UInventoryItemObject;
class UItemDataAsset;
class UItemAction;

UENUM(BlueprintType)
enum EItemType
{
	Consumable,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAddedDelegate, UInventoryItemObject*, ItemData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemovedDelegate, UInventoryItemObject*, ItemData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdatedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryItemDataUpdatedDelegate);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool TryAddItem(const APickupItem* PickupItem);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool TryMoveItem(UInventoryItemObject* ItemObjectToMove, UInventoryComponent* OtherInventory);

	/// Moves item with given itemId to OtherInventory
	UFUNCTION(BlueprintCallable, Category="Inventory")
	UInventoryItemObject* TryMoveItemWithId(const FName ItemId, UInventoryComponent* OtherInventory);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool TryMoveItems(UInventoryItemObject* InventoryItemObject, const int32 Amount, UInventoryComponent* OtherInventory);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool UseItem(UInventoryItemObject* InventoryItemObject);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void DropItem(UInventoryItemObject* InventoryItemObject);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	TArray<UInventoryItemObject*> GetItems();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool HasItem(const FName ItemId) const
	{
		return Inventory.Contains(ItemId);
	}

	UFUNCTION(BlueprintCallable, Category="Inventory Information")
	FString GetOwnerName() const { return GetOwner()->GetName(); } // TODO: FText should be returned instead of FString

	UFUNCTION(BlueprintCallable, Category="Inventory")
	float GetInventoryWeight() const { return CurrentWeight; }

	UFUNCTION(BlueprintCallable, Category="Inventory")
	FText GetInventoryWeightText() const { return FText::FromString(FString::Printf(TEXT("%.2f"), CurrentWeight)); }

	UFUNCTION(BlueprintCallable, Category="Inventory")
	float GetInventoryMaxWeight() const { return MaxWeight; }

	UFUNCTION(BlueprintCallable, Category="Inventory")
	FText GetInventoryMaxWeightText() const { return FText::FromString(FString::Printf(TEXT("%.2f"), MaxWeight)); }

#pragma region Delegates
	// -------------------- Delegates --------------------
	UPROPERTY(BlueprintAssignable)
	FOnItemAddedDelegate OnItemAdded;

	UPROPERTY(BlueprintAssignable)
	FOnItemRemovedDelegate OnItemRemoved;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdatedDelegate OnInventoryUpdated;
	// -------------------- Delegates --------------------
#pragma endregion

private:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool ItemCanBeAdded(const FItemData& ItemData) const;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool ItemsCanBeAdded(const FItemData& ItemData, int32 Amount) const;

	// If item already exists in inventory, increases count and weight.
	// Otherwise, creates a new item object and adds it to inventory.
	void AddItemObject(const UInventoryItemObject* InventoryItemObject);

	// Decreases count and weight of item.
	// If count reaches 0, removes item from inventory.
	void RemoveItemObject(UInventoryItemObject* ExistingItemObject);

	// Adds InventoryItemObject to inventory. 
	void AddNewItem(UInventoryItemObject* InventoryItemObject);

	// Increases count and weight of item.
	void IncreaseItemCount(const FItemData& ItemData);

	// Decreases count and weight of item.
	void DecreaseItemCount(const FItemData& ItemData);

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FName, UInventoryItemObject*> Inventory;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	float MaxWeight = 100;

	float CurrentWeight;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Inventory", meta=(AllowPrivateAccess="true"))
	FGameplayTagContainer ActiveTags;
};

UCLASS(BlueprintType)
class FAITHINABYSS_API UInventoryItemObject : public UObject
{
	GENERATED_BODY()

public:
	FItemData GetItemData() const
	{
		return ItemData;
	}

	UItemAction* GetItemAction() const
	{
		return ItemAction;
	}

	TSubclassOf<APickupItem> GetItemClass() const
	{
		return ItemClass;
	}

	UFUNCTION(BlueprintCallable, Category="Inventory Item Data")
	int32 GetQuantity() const
	{
		return Quantity;
	}

	UFUNCTION(BlueprintCallable, Category="Inventory Item Action")
	void Add()
	{
		Quantity++;
		OnInventoryItemDataUpdated.Broadcast();
	}

	UFUNCTION(BlueprintCallable, Category="Inventory Item Action")
	void Remove()
	{
		Quantity--;
		OnInventoryItemDataUpdated.Broadcast();
	}

	FOnInventoryItemDataUpdatedDelegate OnInventoryItemDataUpdated;

	static UInventoryItemObject* Create(const APickupItem* PickupItem)
	{
		const UItemDataAsset* ItemDataAsset = PickupItem->GetItemDataAsset();
		UInventoryItemObject* Instance = NewObject<UInventoryItemObject>();
		Instance->Quantity = 1;
		Instance->ItemData = ItemDataAsset->Data;
		Instance->ItemAction = ItemDataAsset->ActionAsset == nullptr ? nullptr : NewObject<UItemAction>(Instance, ItemDataAsset->ActionAsset);
		Instance->ItemClass = PickupItem->GetClass();
		return Instance;
	}

	static UInventoryItemObject* Create(const UInventoryItemObject* InventoryItemObject)
	{
		UInventoryItemObject* Instance = NewObject<UInventoryItemObject>();
		Instance->Quantity = 1;
		Instance->ItemData = InventoryItemObject->ItemData;
		Instance->ItemAction = InventoryItemObject->ItemAction;
		Instance->ItemClass = InventoryItemObject->ItemClass;
		return Instance;
	}

private:
	UPROPERTY(BlueprintReadOnly, Category="Inventory Item Data", meta=(AllowPrivateAccess="true"))
	FItemData ItemData;

	UPROPERTY(BlueprintReadOnly, Category="Inventory Item Data", meta=(AllowPrivateAccess="true"))
	UItemAction* ItemAction;

	UPROPERTY(BlueprintReadOnly, Category="Inventory Item Data", meta=(AllowPrivateAccess="true"))
	TSubclassOf<APickupItem> ItemClass;

	int32 Quantity;
};
