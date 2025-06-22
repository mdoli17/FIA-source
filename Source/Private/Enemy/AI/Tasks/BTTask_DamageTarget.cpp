// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Tasks/BTTask_DamageTarget.h"

#include "AIController.h"
#include "Enemy/EnemyCharacter.h"

UBTTask_DamageTarget::UBTTask_DamageTarget()
{
	NodeName = TEXT("Damage Target");
}

EBTNodeResult::Type UBTTask_DamageTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Pawn))
	{
		EnemyCharacter->Attack();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}

FString UBTTask_DamageTarget::GetStaticDescription() const
{
	return Super::GetStaticDescription();
}
