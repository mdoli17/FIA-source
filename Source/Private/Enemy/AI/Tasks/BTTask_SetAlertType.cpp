// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Tasks/BTTask_SetAlertType.h"

#include "AIController.h"
#include "Enemy/Interfaces/Alertable.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetAlertType::UBTTask_SetAlertType()
{
	NodeName = TEXT("Set Alert Type");
	BlackboardKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SetAlertType, BlackboardKey), StaticEnum<EAlertType>());
}

EBTNodeResult::Type UBTTask_SetAlertType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (APawn* Pawn = AIController->GetPawn(); Pawn->Implements<UAlertable>())
	{
		IAlertable::Execute_SetAlerted(Pawn, AlertType);
	}
	AIController->GetBlackboardComponent()->SetValueAsEnum(BlackboardKey.SelectedKeyName, AlertType);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_SetAlertType::GetStaticDescription() const
{
	return FString::Printf(TEXT("Alert Type: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
