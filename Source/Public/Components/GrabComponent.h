// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabComponent.generated.h"


class IGrabbable;
class UPhysicsHandleComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UGrabComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Grab Component")
	void Grab(AActor* ActorToGrab);

	UFUNCTION(BlueprintCallable, Category="Grab Component")
	void Release();

	UFUNCTION(BlueprintCallable, Category="Grab Component")
	void Throw();

	UFUNCTION(BlueprintCallable, Category="Grab Component")
	bool IsGrabbing() const
	{
		return bIsGrabbing;
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grab Component")
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grab Component")
	float ThrowingForce;

private:
	AActor* GrabbedActor;
	bool bIsGrabbing;
};
