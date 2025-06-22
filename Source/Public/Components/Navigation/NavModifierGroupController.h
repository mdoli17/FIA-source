// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NavModifierGroupController.generated.h"


class ANavModifierVolume;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UNavModifierGroupController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UNavModifierGroupController();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Nav Modifier Group Controller")
	TMap<ANavModifierVolume*, TSubclassOf<UNavArea>> NavModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Nav Modifier Group Controller")
	TSubclassOf<UNavArea> ActiveNavAreaClass;

public:
	UFUNCTION(BlueprintCallable, Category="Nav Modifier Group Controller")
	void ActivateModifiers();

	UFUNCTION(BlueprintCallable, Category="Nav Modifier Group Controller")
	void DeactivateModifiers();
};
