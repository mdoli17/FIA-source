// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Components/Interaction/IInteractable.h"
#include "Enemy/Interfaces/InvestigatableObject.h"
#include "GameFramework/Actor.h"
#include "HidingSpot.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;

UCLASS()
class FAITHINABYSS_API AHidingSpot : public AActor, public IInteractable, public IInvestigatableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHidingSpot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Hiding Spot")
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY()
	UEnhancedInputComponent* LockerInputComponent;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TSoftObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> LeaveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locker")
	float MaxYawRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locker")
	float MaxPitchRotation;

	UFUNCTION(BlueprintImplementableEvent, Category="Hiding Spot")
	void PlayerEnter();

	UFUNCTION(BlueprintImplementableEvent, Category="Hiding Spot")
	void PlayerLeave();
	
	virtual void Look(const FInputActionValue& Value);
	virtual void Leave(const FInputActionValue& Value);
	
	virtual void EnableInputHandling();
	virtual void DisableInputHandling();

	bool bIsHiding;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation(AActor* Caller) override;

	UFUNCTION(BlueprintCallable, Category="Hiding Spot")
	bool IsOccupied() const
	{
		return bIsHiding;
	}

private:
	APlayerController* OwningPlayerController;
};
