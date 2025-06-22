// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerDistributable.h"
#include "Components/ActorComponent.h"
#include "PowerGenerator.generated.h"


class UPowerDistributor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPowerGenerationStarted);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPowerGenerationStopped);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UPowerGenerator : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerGenerator();
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power System")
	float GenerationAmount;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Power System")
	TObjectPtr<AActor> DistributableActor;

	UFUNCTION(BlueprintCallable, Category = "Power System")
	void StartGeneratingPower();

	UFUNCTION(BlueprintCallable, Category = "Power System")
	void StopGeneratingPower();

	UFUNCTION(BlueprintCallable, Category = "Power System")
	bool IsGeneratingPower() const
	{
		return bIsGeneratingPower;
	}

protected:
	TScriptInterface<IPowerDistributable> Distributable;

	UPROPERTY(BlueprintAssignable)
	FOnPowerGenerationStarted OnPowerGenerationStarted;

	UPROPERTY(BlueprintAssignable)
	FOnPowerGenerationStopped OnPowerGenerationStopped;

private:
	bool bIsGeneratingPower;
};
