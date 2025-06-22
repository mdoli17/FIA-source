// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FocusComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UFocusComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFocusComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	float TraceDistance = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	TEnumAsByte<ECollisionChannel> TraceChannel;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Interaction")
	AActor* GetTracedActor() const
	{
		return TracedActor;
	}

private:
	UPROPERTY(BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<AActor> TracedActor;

	AActor* Trace() const;
};
