// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Patrolling/PatrolComponent.h"

#include "Enemy/AI/Patrolling/PatrolPoint.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UPatrolComponent::UPatrolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UPatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

TArray<APatrolPoint*> UPatrolComponent::FindPatrolPoints()
{
	TArray<FHitResult> OutHits;
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector End = Start;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	const bool Hit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End,
	                                                                  PatrolPointDetectionRadius,
	                                                                  PatrolPointObjectTypes, false, ActorsToIgnore,
	                                                                  EDrawDebugTrace::ForDuration, OutHits, true,
	                                                                  FLinearColor::Gray,
	                                                                  FLinearColor::Blue, 5.0f);
	TArray<APatrolPoint*> Result;
	if (Hit)
	{
		for (const FHitResult HitResult : OutHits)
		{
			if (HitResult.GetActor()->IsA(APatrolPoint::StaticClass()))
			{
				APatrolPoint* PatrolPoint = Cast<APatrolPoint>(HitResult.GetActor());
				Result.Add(PatrolPoint);
			}
		}
	}
	PatrolPoints = Result;

	UpdatePatrolPoints();

	return Result;
}

APatrolPoint* UPatrolComponent::GetNextPatrolPoint()
{
	if (PatrolPoints.IsEmpty()) FindPatrolPoints();
	if (PatrolPoints.IsEmpty()) return nullptr;

	if (FreshPoints.Num() == 0)
		UpdatePatrolPoints();

	// Take out first element since it is ordered
	return FreshPoints[0].Get();
}

APatrolPoint* UPatrolComponent::GetActivePatrolPoint() const
{
	return ActivePatrolPoint;
}

void UPatrolComponent::StartCheckingOut(APatrolPoint* PatrolPoint)
{
	if (!FreshPoints.Contains(PatrolPoint)) return;

	ActivePatrolPoint = PatrolPoint;
	FreshPoints.Remove(ActivePatrolPoint);
}

void UPatrolComponent::CompleteCheckingOut(APatrolPoint* PatrolPoint)
{
	if (ActivePatrolPoint != PatrolPoint) return;

	ActivePatrolPoint = nullptr;
	PatrolledPoints.Add(PatrolPoint);
}

void UPatrolComponent::UpdatePatrolPoints()
{
	FreshPoints = PatrolPoints;
	FreshPoints.Sort();
	PatrolledPoints.Empty();
}
