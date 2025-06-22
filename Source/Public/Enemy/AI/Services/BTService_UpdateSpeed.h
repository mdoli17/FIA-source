// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateSpeed.generated.h"

/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UBTService_UpdateSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_UpdateSpeed();

private:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess = "true"))
	float Speed;
};
