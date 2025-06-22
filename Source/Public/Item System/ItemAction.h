#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "ItemAction.generated.h"

UCLASS(BlueprintType, Blueprintable)
class FAITHINABYSS_API UItemAction : public UObject // TODO: Should be renamed to UInventoryItemUseAction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Item Action")
	bool UseItem(AActor* Caller, FItemData ItemData);
};
