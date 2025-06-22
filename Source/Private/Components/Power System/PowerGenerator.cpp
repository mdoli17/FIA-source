// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Power System/PowerGenerator.h"


// Sets default values for this component's properties
UPowerGenerator::UPowerGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPowerGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (DistributableActor->Implements<UPowerDistributable>())
	{
		Distributable = DistributableActor;
	}
}

void UPowerGenerator::StartGeneratingPower()
{
	if (bIsGeneratingPower) return;

	bIsGeneratingPower = true;
	OnPowerGenerationStarted.Broadcast();

	if (Distributable.GetObject() == nullptr) return;

	IPowerDistributable::Execute_StartReceivingPower(Distributable.GetObject(), GenerationAmount);
}

void UPowerGenerator::StopGeneratingPower()
{
	if (!bIsGeneratingPower) return;

	bIsGeneratingPower = false;
	OnPowerGenerationStopped.Broadcast();

	if (Distributable.GetObject() == nullptr) return;

	IPowerDistributable::Execute_StopReceivingPower(Distributable.GetObject(), GenerationAmount);
}
