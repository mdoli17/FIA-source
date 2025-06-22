#pragma once

#include "CoreMinimal.h"
#include "ActionParams.generated.h"

USTRUCT(BlueprintType)
struct FActionParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Parameters")
	int32 IntValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Parameters")
	float FloatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Parameters")
	FVector VectorValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Parameters")
	FString StringValue;
};
