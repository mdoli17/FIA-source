// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StartPatrolPointCheckout.generated.h"

/**
 * Start PatrolPoint Checkout task node.
 * Finds PatrolComponent on owning pawn, tries to get a patrol point and mark it for checkout.
 * Updates PatrolPoint and MoveLocation blackboard key values.
 */
UCLASS()
class FAITHINABYSS_API UBTTask_StartPatrolPointCheckout : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_StartPatrolPointCheckout();

	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector MoveToKey;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
