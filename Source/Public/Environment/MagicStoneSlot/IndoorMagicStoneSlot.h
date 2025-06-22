// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicStoneSlot.h"
#include "IndoorMagicStoneSlot.generated.h"

class AEntrance;

UCLASS()
class FAITHINABYSS_API AIndoorMagicStoneSlot : public AMagicStoneSlot
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIndoorMagicStoneSlot();

protected:
	virtual void BeginPlay() override;
	virtual void Activate() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Indoor Magic Stone Slot")
	TArray<AEntrance*> Entrances;

	UFUNCTION()
	void EntranceStateUpdateHandler(bool IsOpen);

private:
	bool CanActivate();
};
