// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Interaction/IInteractable.h"
#include "GameFramework/Actor.h"
#include "Chest.generated.h"

class APickupItem;
class UItemDataAsset;
class UBoxComponent;
class UInventoryComponent;

UCLASS()
class FAITHINABYSS_API AChest : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChest();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Chest")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Chest")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Chest")
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Chest")
	TMap<TSubclassOf<APickupItem>, int32> DefaultItems;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void AddDefaultItemsToInventory();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void Interact_Implementation(AActor* Caller) override;
};
