// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Tasks/Patrolling/BTTask_CheckoutPatrolPoint.h"

#include "Enemy/EnemyCharacter.h"
#include "Enemy/AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/AI/Patrolling/PatrolPoint.h"


UBTTask_CheckoutPatrolPoint::UBTTask_CheckoutPatrolPoint()
{
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_CheckoutPatrolPoint, BlackboardKey), APatrolPoint::StaticClass());
}

EBTNodeResult::Type UBTTask_CheckoutPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerBTComponent = &OwnerComp;

	const AAIController* AIController = OwnerComp.GetAIOwner();

	if (APawn* Pawn = AIController->GetPawn(); IPatrolPointCheckoutInterface* Interface = Cast<IPatrolPointCheckoutInterface>(Pawn))
	{
		if (FOnCheckoutPatrolPointFinishedSignature* Delegate = Interface->GetCheckoutPatrolPointFinishedSignature())
		{
			Delegate->AddUniqueDynamic(this, &UBTTask_CheckoutPatrolPoint::CheckoutPatrolPointCallback);
			APatrolPoint* PatrolPoint = Cast<APatrolPoint>(AIController->GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
			IPatrolPointCheckoutInterface::Execute_CheckoutPatrolPoint(Pawn, PatrolPoint);

			return EBTNodeResult::InProgress;
		}
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_CheckoutPatrolPoint::CheckoutPatrolPointCallback()
{
	check(OwnerBTComponent);

	const AAIController* AIController = OwnerBTComponent->GetAIOwner();

	if (APawn* Pawn = AIController->GetPawn(); IPatrolPointCheckoutInterface* Interface = Cast<IPatrolPointCheckoutInterface>(Pawn))
	{
		if (FOnCheckoutPatrolPointFinishedSignature* Delegate = Interface->GetCheckoutPatrolPointFinishedSignature())
		{
			Delegate->RemoveDynamic(this, &UBTTask_CheckoutPatrolPoint::CheckoutPatrolPointCallback);
		}
	}

	FinishLatentTask(*OwnerBTComponent, EBTNodeResult::Succeeded);
}
