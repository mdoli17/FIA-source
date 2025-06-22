// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Interfaces/Alertable.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetAlertType.generated.h"

/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UBTTask_SetAlertType : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_SetAlertType();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Alert Type")
	TEnumAsByte<EAlertType> AlertType;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
