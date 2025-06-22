// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Tasks/Lurking/BTTask_LurkAroundEntrance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Interfaces/AILurkingInterface.h"
#include "Environment/Entrance/AIEntranceInterface.h"

EBTNodeResult::Type UBTTask_LurkAroundEntrance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController) return EBTNodeResult::Failed;

	APawn* Pawn = AIController->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	if (!Pawn->Implements<UAILurkingInterface>()) return EBTNodeResult::Failed;

	BehaviorTreeComponent = &OwnerComp;
	UObject* AIEntranceInterfaceObject = (OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	TScriptInterface<IAIEntranceInterface> InterfaceRef;
	InterfaceRef.SetObject(AIEntranceInterfaceObject);
	InterfaceRef.SetInterface(Cast<IAIEntranceInterface>(AIEntranceInterfaceObject));

	OnLurkedAroundEntranceDelegate = Cast<IAILurkingInterface>(Pawn)->GetLurkedAroundEntranceDelegate();
	OnLurkedAroundEntranceDelegate->AddUniqueDynamic(this, &UBTTask_LurkAroundEntrance::LurkAroundEntranceHandler);

	IAILurkingInterface::Execute_LurkAroundEntrance(Pawn, InterfaceRef);
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_LurkAroundEntrance::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();

	IAILurkingInterface::Execute_AbortLurking(Pawn);
	OnLurkedAroundEntranceDelegate->RemoveDynamic(this, &UBTTask_LurkAroundEntrance::LurkAroundEntranceHandler);
	FinishLatentAbort(OwnerComp);

	OnLurkedAroundEntranceDelegate = nullptr;
	BehaviorTreeComponent = nullptr;

	return EBTNodeResult::Aborted;
}

void UBTTask_LurkAroundEntrance::LurkAroundEntranceHandler()
{
	OnLurkedAroundEntranceDelegate->RemoveDynamic(this, &UBTTask_LurkAroundEntrance::LurkAroundEntranceHandler);
	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);

	OnLurkedAroundEntranceDelegate = nullptr;
	BehaviorTreeComponent = nullptr;
}
