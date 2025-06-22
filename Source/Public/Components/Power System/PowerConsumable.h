// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PowerConsumable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPowerConsumable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FAITHINABYSS_API IPowerConsumable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Power System")
	void StartReceivingPower();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Power System")
	void StopReceivingPower();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Power System")
	bool IsReceivingPower();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Power System")
	float RequiredPowerAmount();
};
