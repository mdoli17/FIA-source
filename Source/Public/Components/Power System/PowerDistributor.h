// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerConsumable.h"
#include "PowerDistributable.h"
#include "Components/ActorComponent.h"
#include "PowerDistributor.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UPowerDistributor : public UActorComponent, public IPowerDistributable
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerDistributor();

	virtual void StartReceivingPower_Implementation(const float PowerAmount) override;
	virtual void StopReceivingPower_Implementation(const float PowerAmount) override;

	UFUNCTION(BlueprintCallable, Category = "Power System")
	void AddPowerConsumable(AActor* PowerConsumableActor);

	UFUNCTION(BlueprintCallable, Category = "Power System")
	void RemovePowerConsumable(AActor* PowerConsumableActor);

	UFUNCTION(BlueprintCallable, Category = "Power System")
	void StartDistributingPower();

	UFUNCTION(BlueprintCallable, Category = "Power System")
	void StopDistributingPower();

	UFUNCTION(BlueprintCallable, Category = "Power System")
	bool IsDistributingPower() const
	{
		return bIsDistributingPower;
	}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power System")
	int MaxPowerConsumableCount;

	UPROPERTY(BlueprintReadOnly, Category = "Power System")
	TArray<TScriptInterface<IPowerConsumable>> Consumables;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power System")
	float MaxPower = 100.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Power System")
	float CurrentPower;

	UPROPERTY(BlueprintReadOnly, Category = "Power System")
	float DistributedPower;

private:
	bool bIsDistributingPower;
};
