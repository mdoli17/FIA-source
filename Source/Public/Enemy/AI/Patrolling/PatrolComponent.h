// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolComponent.generated.h"

class USphereComponent;
class APatrolPoint;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPatrolComponent();

	UFUNCTION(BlueprintCallable, CallInEditor)
	TArray<APatrolPoint*> FindPatrolPoints();

	UFUNCTION(BlueprintCallable)
	APatrolPoint* GetNextPatrolPoint();

	UFUNCTION(BlueprintCallable)
	APatrolPoint* GetActivePatrolPoint() const;

	UFUNCTION(BlueprintCallable)
	void StartCheckingOut(APatrolPoint* PatrolPoint);

	UFUNCTION(BlueprintCallable)
	void CompleteCheckingOut(APatrolPoint* PatrolPoint);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patrolling", meta=(AllowPrivateAccess = true))
	float PatrolPointDetectionRadius = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Patrolling", meta=(AllowPrivateAccess = true))
	TArray<TEnumAsByte<EObjectTypeQuery>> PatrolPointObjectTypes;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Patrolling", meta=(AllowPrivateAccess = true))
	TArray<TObjectPtr<APatrolPoint>> PatrolPoints;

	void UpdatePatrolPoints();


	TObjectPtr<APatrolPoint> ActivePatrolPoint;
	TArray<TObjectPtr<APatrolPoint>> PatrolledPoints;
	TArray<TObjectPtr<APatrolPoint>> FreshPoints;
};
