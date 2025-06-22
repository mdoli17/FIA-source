// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPatrolPointCheckoutInterface.generated.h"

class APatrolPoint;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckoutPatrolPointFinishedSignature);

// This class does not need to be modified.
UINTERFACE()
class UPatrolPointCheckoutInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FAITHINABYSS_API IPatrolPointCheckoutInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Patrol Point")
	void CheckoutPatrolPoint(APatrolPoint* PatrolPoint);

	virtual FOnCheckoutPatrolPointFinishedSignature* GetCheckoutPatrolPointFinishedSignature() = 0;
};
