// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionParams.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "Action.generated.h"

class UActionComponent;
/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class FAITHINABYSS_API UAction : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool CanStartAction();

	UFUNCTION(BlueprintCallable, Category="Action")
	virtual bool StartAction(const FActionParams& Params);

	UFUNCTION(BlueprintCallable, Category="Action")
	bool StopAction();

	UFUNCTION(BlueprintCallable, Category="Action")
	FName GetActionName() const
	{
		return Name;
	}

	UFUNCTION(BlueprintCallable, Category="Action")
	bool IsRunning() const
	{
		return bIsRunning;
	}

	// * Tags which are granted to action component when the action is started.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action")
	FGameplayTagContainer GrantingTags;

	// * Tags which block the action from starting
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action")
	FGameplayTagContainer BlockingTags;

	// * Tags of which actions in action component will be stopped once this action starts 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action")
	FGameplayTagContainer CancelingTags;

protected:
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void Initialize();

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool StartActionImplementation(const FActionParams& Params);

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool StopActionImplementation();

	UFUNCTION(BlueprintCallable, Category="Action")
	UActionComponent* GetOwningComponent() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action", meta=(AllowPrivateAccess))
	FName Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Action", meta=(AllowPrivateAccess))
	AActor* Owner;

	bool bIsRunning;
};
