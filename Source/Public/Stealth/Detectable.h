// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Detectable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDetectionUpdatedSignature, bool, IsDetectable);

// This class does not need to be modified.
UINTERFACE()
class UDetectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FAITHINABYSS_API IDetectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Detection")
	void StartDetecting(); // Will show UI

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Detection")
	void UpdateDetectionProgress(float CurrentValue, float MaxValue); //Will update UI

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Detection")
	void StopDetecting(); // Will hide UI

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Detection")
	bool GetIsDetectable();

	virtual FOnDetectionUpdatedSignature* GetDetectionUpdatedDelegate() = 0;
};
