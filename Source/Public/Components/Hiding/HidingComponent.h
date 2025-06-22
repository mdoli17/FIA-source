// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Hidable.h"
#include "Components/ActorComponent.h"
#include "HidingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UHidingComponent : public UActorComponent, public IHidable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHidingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	FGameplayTagContainer TagContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Tags")
	FGameplayTag HideTag;

	virtual void EnterHiding_Implementation(AHidingSpot* HidingSpot) override;
	virtual void LeaveHiding_Implementation() override;
};
