// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPoint.generated.h"

UENUM()
enum EPatrolPointPriority
{
	High UMETA(DisplayName = "High"),
	Medium UMETA(DisplayName = "Medium"),
	Low UMETA(DisplayName = "Low")
};

UCLASS()
class FAITHINABYSS_API APatrolPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APatrolPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Patrol Data")
	TEnumAsByte<EPatrolPointPriority> Priority;

	FORCEINLINE bool operator<(const APatrolPoint& Other) const
	{
		return Priority < Other.Priority;
	}
};
