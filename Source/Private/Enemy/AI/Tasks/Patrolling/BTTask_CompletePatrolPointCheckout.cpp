// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Tasks/Patrolling/BTTask_CompletePatrolPointCheckout.h"

#include "AIController.h"
#include "Enemy/AI/Patrolling/PatrolComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CompletePatrolPointCheckout::UBTTask_CompletePatrolPointCheckout()
{
	NodeName = TEXT("Complete Patrol Point Checkout");
}

EBTNodeResult::Type UBTTask_CompletePatrolPointCheckout::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* AIPawn = AIController->GetPawn();
	if (UPatrolComponent* PatrolComponent = Cast<UPatrolComponent>(
		AIPawn->GetComponentByClass(UPatrolComponent::StaticClass())))
	{
		APatrolPoint* PatrolPoint = PatrolComponent->GetActivePatrolPoint();
		if (PatrolPoint == nullptr)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
		}

		PatrolComponent->CompleteCheckingOut(PatrolPoint);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
