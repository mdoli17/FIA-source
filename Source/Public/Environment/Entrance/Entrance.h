// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEntranceInterface.h"
#include "Components/Interaction/Focusable.h"
#include "Components/Interaction/IInteractable.h"
#include "GameFramework/Actor.h"
#include "Navigation/NavLinkProxy.h"
#include "Entrance.generated.h"

class UNavLinkComponent;
class UNavModifierComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEntranceStateUpdatedSignature, bool, IsOpen);

UCLASS()
class FAITHINABYSS_API AEntrance : public ANavLinkProxy, public IFocusable, public IInteractable, public IAIEntranceInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEntrance();

	UPROPERTY(BlueprintAssignable)
	FOnEntranceStateUpdatedSignature OnEntranceStateUpdated;

	virtual void Interact_Implementation(AActor* Caller) override;

	UFUNCTION(BlueprintCallable, Category="Entrance")
	virtual void Open(AActor* Caller);

	UFUNCTION(BlueprintCallable, Category="Entrance")
	virtual void Close(AActor* Caller);

	UFUNCTION(BlueprintCallable, Category="Entrance")
	virtual void Toggle(AActor* Caller);

	UFUNCTION(BlueprintCallable, Category="Entrance")
	bool IsOpen() const
	{
		return bIsOpen;
	}

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category="Entrance")
	void OnOpen(AActor* Caller);

	UFUNCTION(BlueprintImplementableEvent, Category="Entrance")
	void OnClose(AActor* Caller);

	UFUNCTION()
	void SmartLinkReachHandler(AActor* MovingActor, const FVector& DestinationPoint);

private:
	bool bIsOpen = false;
};
