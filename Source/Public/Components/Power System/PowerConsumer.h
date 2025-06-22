// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerConsumable.h"
#include "Components/ActorComponent.h"
#include "PowerConsumer.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UPowerConsumer : public UActorComponent, public IPowerConsumable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerConsumer();

	virtual void StartReceivingPower_Implementation() override;
	virtual void StopReceivingPower_Implementation() override;

	virtual float RequiredPowerAmount_Implementation() override
	{
		return RequiredPower;
	}

	virtual bool IsReceivingPower_Implementation() override
	{
		return bIsReceivingPower;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power System")
	float RequiredPower;

private:
	bool bIsReceivingPower;
};
