// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Tasks/BTTask_ClearBlackboardValue.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	AIController->GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
