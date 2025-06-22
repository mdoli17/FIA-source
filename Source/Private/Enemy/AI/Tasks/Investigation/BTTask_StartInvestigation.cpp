// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Tasks/Investigation/BTTask_StartInvestigation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Interfaces/InvestigatableObject.h"
#include "Enemy/Interfaces/Investigator.h"

UBTTask_StartInvestigation::UBTTask_StartInvestigation()
{
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_StartInvestigation, BlackboardKey), UInvestigatableObject::StaticClass());
}

EBTNodeResult::Type UBTTask_StartInvestigation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController->GetPawn()->Implements<UInvestigator>()) return EBTNodeResult::Failed;

	UObject* BlackboardObject = AIController->GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);

	ensure(BlackboardObject);

	if (!BlackboardObject->Implements<UInvestigatableObject>()) return EBTNodeResult::Failed;

	IInvestigator::Execute_StartInvestigating(AIController->GetPawn(), BlackboardObject);

	return EBTNodeResult::Succeeded;
}
