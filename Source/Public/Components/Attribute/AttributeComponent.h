// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttributeDepletedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttributeReplenishedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeUpdatedSignature, float, OldValue, float, NewValue, float, MaxValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float MaxValue = 100.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attribute")
	float CurrentValue = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float RegenerationRate = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float RegenerationStartDelay = 2.5f; // Per second

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	bool bIsRegenerative = true;

	bool bCanRegenerate = true;
	bool bIsBeingUsed = false;
	float AttributeUseRate = 0.0f;

	FTimerHandle RegenCheckTimerHandle;

private:
	void CheckRegen();
	void RegenCheckCallback();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	bool HasEnough(float Amount) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Stamina")
	void SingleUse(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void StartUsing(float UseRate);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void StopUsing(float UseRate);

	UFUNCTION(BlueprintCallable, Category="Stamina")
	void Reset();


	UPROPERTY(BlueprintAssignable)
	FOnAttributeDepletedSignature OnAttributeDepleted;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeReplenishedSignature OnAttributeReplenished;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeUpdatedSignature OnAttributeUpdated;

private:
	void HandleAttributeDepletion();
};
