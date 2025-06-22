// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Investigator.generated.h"

class IInvestigatableObject;
// This class does not need to be modified.
UINTERFACE()
class UInvestigator : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FAITHINABYSS_API IInvestigator
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Investigation")
	void StartInvestigating(const TScriptInterface<IInvestigatableObject>& InvestigatableObject);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Investigation")
	void EndInvestigating(const TScriptInterface<IInvestigatableObject>& InvestigatableObject);
};
