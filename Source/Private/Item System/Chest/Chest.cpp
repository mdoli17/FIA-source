// Fill out your copyright notice in the Description page of Project Settings.


#include "Item System/Chest/Chest.h"

#include "Components/BoxComponent.h"
#include "Item System/InventoryComponent.h"
#include "Item System/Chest/ItemTransferInterface.h"


// Sets default values
AChest::AChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	StaticMeshComponent->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	AddDefaultItemsToInventory();
}

void AChest::AddDefaultItemsToInventory()
{
	for (TTuple<TSubclassOf<APickupItem>, int32> DefaultItem : DefaultItems)
	{
		APickupItem* DefaultObject = DefaultItem.Key->GetDefaultObject<APickupItem>();
		for (int32 i = 0; i < DefaultItem.Value; i++)
		{
			InventoryComponent->TryAddItem(DefaultObject);
		}
	}
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChest::Interact_Implementation(AActor* Caller)
{
	IItemTransferInterface* ItemTransferInterface = Cast<IItemTransferInterface>(Caller);

	if (!Caller->Implements<UItemTransferInterface>()) return;

	IItemTransferInterface::Execute_SetupTransfer(Caller, InventoryComponent);
}
