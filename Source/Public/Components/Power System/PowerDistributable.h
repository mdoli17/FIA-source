// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PowerDistributable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPowerDistributable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FAITHINABYSS_API IPowerDistributable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Power System")
	void StartReceivingPower(const float PowerAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Power System")
	void StopReceivingPower(const float PowerAmount);
};
