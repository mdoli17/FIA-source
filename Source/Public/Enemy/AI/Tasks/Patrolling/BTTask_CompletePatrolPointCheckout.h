// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CompletePatrolPointCheckout.generated.h"

/**
 * Complete PatrolPoint Checkout task node.
 * Finds PatrolComponent on owning pawn, tries to get a patrol point and clears it from checkout.
 */
UCLASS()
class FAITHINABYSS_API UBTTask_CompletePatrolPointCheckout : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_CompletePatrolPointCheckout();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
