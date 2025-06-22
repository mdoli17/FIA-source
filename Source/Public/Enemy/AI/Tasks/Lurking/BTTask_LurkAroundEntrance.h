// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Enemy/Interfaces/AILurkingInterface.h"
#include "BTTask_LurkAroundEntrance.generated.h"

/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UBTTask_LurkAroundEntrance : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;
	
	FOnLurkedAroundEntranceSignature* OnLurkedAroundEntranceDelegate;

	UFUNCTION()
	void LurkAroundEntranceHandler();
};
