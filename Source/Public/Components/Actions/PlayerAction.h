// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "PlayerAction.generated.h"

class ADetective;
/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UPlayerAction : public UAction
{
	GENERATED_BODY()

public:
	virtual void Initialize(AActor* Instigator) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Action", meta=(AllowPrivateAccess))
	ADetective* Player;

	UFUNCTION(BlueprintCallable, Category="Player Action")
	UWorld* GetWorld() const override;
};
