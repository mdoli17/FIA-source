// Fill out your copyright notice in the Description page of Project Settings.


#include "Item System/PickupItem.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Item System/InventoryComponent.h"
#include "Item System/ItemDataAsset.h"
#include "Item System/ItemRowBase.h"


// Sets default values
APickupItem::APickupItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");

	StaticMesh->SetupAttachment(RootComponent);
	InteractionPromptWidget->SetupAttachment(StaticMesh);
}

void APickupItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (ItemDataAsset == nullptr) ItemDataAsset = GetItemDataAssetFromDataTable();

	if (ItemDataAsset == nullptr) return;

	StaticMesh->SetStaticMesh(ItemDataAsset->Data.Mesh.Get());
	StaticMesh->SetCollisionProfileName(FName(TEXT("InteractableIgnoreOnlyPawn")));
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupItem::Interact_Implementation(AActor* Caller)
{
	if (UInventoryComponent* InventoryComponent = Caller->GetComponentByClass<UInventoryComponent>())
	{
		if (InventoryComponent->TryAddItem(this))
		{
			HandleInteraction();
			Destroy();
		}
	}
}

UItemDataAsset* APickupItem::GetItemDataAssetFromDataTable() const
{
	if (TableRowHandle.DataTable == nullptr) return nullptr;

	const FItemRowBase* TableRow = TableRowHandle.DataTable->FindRow<FItemRowBase>(TableRowHandle.RowName, "");
	if (!TableRow) return nullptr;

	return TableRow->ItemDataAsset;
}
