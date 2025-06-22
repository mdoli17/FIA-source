// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FocusableActor.h"
#include "ItemDataAsset.h"
#include "Components/Interaction/IInteractable.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

class UBoxComponent;

UCLASS()
class FAITHINABYSS_API APickupItem : public AFocusableActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupItem();

	UFUNCTION(BlueprintCallable, Category="Item Configuration")
	UItemDataAsset* GetItemDataAsset() const
	{
		if (ItemDataAsset == nullptr) return GetItemDataAssetFromDataTable();
		return ItemDataAsset;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Configuration")
	FDataTableRowHandle TableRowHandle;

	UPROPERTY(BlueprintReadOnly, Category="Item Configuration")
	UItemDataAsset* ItemDataAsset;

	UFUNCTION(BlueprintImplementableEvent, Category="Interaction")
	void HandleInteraction();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AActor* Caller) override;

private:
	UItemDataAsset* GetItemDataAssetFromDataTable() const;
};
