// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StartInvestigation.generated.h"

/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UBTTask_StartInvestigation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_StartInvestigation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
