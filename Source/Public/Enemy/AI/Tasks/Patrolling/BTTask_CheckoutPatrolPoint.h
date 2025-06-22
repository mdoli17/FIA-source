// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CheckoutPatrolPoint.generated.h"

class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UBTTask_CheckoutPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_CheckoutPatrolPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY()
	UBehaviorTreeComponent* OwnerBTComponent;;

	UFUNCTION()
	void CheckoutPatrolPointCallback();
};
