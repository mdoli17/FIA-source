// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionParams.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTagsUpdated);


class UAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FAITHINABYSS_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UActionComponent();

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartActionByName(FName ActionName, const FActionParams& Params = FActionParams());

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopActionByName(FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddAction(TSubclassOf<UAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category="Actions")
	void RemoveAction(TSubclassOf<UAction> ActionClass);

	UPROPERTY(BlueprintReadOnly, Category="Actions")
	FGameplayTagContainer ActiveGameplayTags;

	UPROPERTY(BlueprintAssignable)
	FOnTagsUpdated OnTagsUpdated;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Actions")
	TArray<TSubclassOf<UAction>> InitialActions;

	UPROPERTY(BlueprintReadOnly, Category="Actions")
	TMap<FName, UAction*> Actions;

	UPROPERTY(BlueprintReadOnly, Category="Actions")
	TArray<UAction*> RunningActions;

private:
	void SetupInitialActions();
};
