// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Alertable.generated.h"

UENUM(Blueprintable)
enum EAlertType
{
	Neutral, // Default state
	Investigate, // Has a clue to check
	Alert // Player is detected
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UAlertable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for an Actor that can be Alerted.
 */
class FAITHINABYSS_API IAlertable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Alertable")
	void SetAlerted(EAlertType AlertType);
};
