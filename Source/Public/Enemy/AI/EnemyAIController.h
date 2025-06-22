// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Enemy/Interfaces/Alertable.h"
#include "EnemyAIController.generated.h"

class ADetective;
class UAttributeComponent;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;
struct FAIStimulus;
class UBehaviorTreeComponent;
class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class FAITHINABYSS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	UFUNCTION()
	void PerceptionUpdateHandler(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=( AllowPrivateAccess = true))
	FName TargetActorKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=( AllowPrivateAccess = true))
	FName InvestigationLocationKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=( AllowPrivateAccess = true))
	FName AlertTypeKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess=true))
	FName HasSightKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess=true))
	FName TargetLastLocationKey;

	void SetupPerceptionSystem();

	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig;

	TObjectPtr<ADetective> Detective;

protected:
	UFUNCTION(BlueprintCallable)
	TEnumAsByte<EAlertType> GetCurrentAlertType();

private:
	/// Stimuli Handlers
	void HandleSensingSound(FAIStimulus Stimulus) const;
	void HandleSensingSight(AActor* SeenActor);
	void HandleLosingSight(AActor* LostActor);

	void HandleSeeingPlayer();
	void HandleLosingSightOfPlayer();

	void PrepareForInvestigation(const FVector& Location) const;
};
