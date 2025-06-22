#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataAsset.h"
#include "ItemRowBase.generated.h"

USTRUCT(BlueprintType)
struct FItemRowBase : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Information")
	TObjectPtr<UItemDataAsset> ItemDataAsset;
};
