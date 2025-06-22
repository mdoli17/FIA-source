// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Tasks/Patrolling/BTTask_StartPatrolPointCheckout.h"

#include "AIController.h"
#include "Enemy/AI/Patrolling/PatrolComponent.h"
#include "Enemy/AI/Patrolling/PatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_StartPatrolPointCheckout::UBTTask_StartPatrolPointCheckout()
{
	NodeName = TEXT("Start Partol Point Checkout");
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_StartPatrolPointCheckout, BlackboardKey),
	                              APatrolPoint::StaticClass());
	MoveToKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_StartPatrolPointCheckout, BlackboardKey));
}

EBTNodeResult::Type UBTTask_StartPatrolPointCheckout::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                                  uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* AIPawn = AIController->GetPawn();
	if (UPatrolComponent* PatrolComponent = Cast<UPatrolComponent>(AIPawn->GetComponentByClass(UPatrolComponent::StaticClass())))
	{
		APatrolPoint* PatrolPoint = PatrolComponent->GetNextPatrolPoint();

		if (PatrolPoint == nullptr)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
		}

		PatrolComponent->StartCheckingOut(PatrolPoint);

		UObject* Value = PatrolPoint;
		AIController->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, Value);
		AIController->GetBlackboardComponent()->SetValueAsVector(MoveToKey.SelectedKeyName, PatrolPoint->GetActorLocation());

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}

FString UBTTask_StartPatrolPointCheckout::GetStaticDescription() const
{
	return FString::Printf(TEXT("Object: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
