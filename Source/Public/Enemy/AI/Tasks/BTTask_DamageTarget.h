﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_DamageTarget.generated.h"

/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UBTTask_DamageTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_DamageTarget();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
