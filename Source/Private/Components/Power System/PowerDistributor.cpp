// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Power System/PowerDistributor.h"


// Sets default values for this component's properties
UPowerDistributor::UPowerDistributor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UPowerDistributor::StartReceivingPower_Implementation(const float PowerAmount)
{
	IPowerDistributable::StartReceivingPower_Implementation(PowerAmount);

	if (CurrentPower + PowerAmount >= MaxPower) return;

	CurrentPower += PowerAmount;
}

void UPowerDistributor::StopReceivingPower_Implementation(const float PowerAmount)
{
	IPowerDistributable::StopReceivingPower_Implementation(PowerAmount);

	CurrentPower = FMath::Max(CurrentPower - PowerAmount, 0.0f);
}

void UPowerDistributor::AddPowerConsumable(AActor* PowerConsumableActor)
{
	if (!PowerConsumableActor->Implements<UPowerConsumable>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Given Actor %s doesn't implement consumable"), *PowerConsumableActor->GetName());
		return;
	}

	if (Consumables.Num() == MaxPowerConsumableCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("Max consumables reached for power distribution"));
		return;
	}

	if (Consumables.Contains(PowerConsumableActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is already in distribution list"), *PowerConsumableActor->GetName());
		return;
	}

	// TODO: Start distributing power to given PowerConsumableActor if power is being distributed 

	Consumables.Add(PowerConsumableActor);
}

void UPowerDistributor::RemovePowerConsumable(AActor* PowerConsumableActor)
{
	if (!PowerConsumableActor->Implements<UPowerConsumable>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Given Actor %s doesn't implement consumable"), *PowerConsumableActor->GetName());

		return;
	}

	if (!Consumables.Contains(PowerConsumableActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s isn't in distribution list"), *PowerConsumableActor->GetName());
		return;
	}

	// TODO: Stop distributing power to given PowerConsumableActor if power is being distributed

	Consumables.Remove(PowerConsumableActor);
}

void UPowerDistributor::StartDistributingPower()
{
	if (bIsDistributingPower) return;
	bIsDistributingPower = true;
	for (TScriptInterface<IPowerConsumable> PowerConsumable : Consumables)
	{
		const float RequiredPowerAmount = IPowerConsumable::Execute_RequiredPowerAmount(PowerConsumable.GetObject());
		if (CurrentPower - RequiredPowerAmount < 0.0f) continue;

		DistributedPower += RequiredPowerAmount;
		IPowerConsumable::Execute_StartReceivingPower(PowerConsumable.GetObject());
	}
}

void UPowerDistributor::StopDistributingPower()
{
	if (!bIsDistributingPower) return;
	bIsDistributingPower = false;
	for (TScriptInterface<IPowerConsumable> PowerConsumable : Consumables)
	{
		if (!IPowerConsumable::Execute_IsReceivingPower(PowerConsumable.GetObject())) continue;
		const float RequiredPowerAmount = IPowerConsumable::Execute_RequiredPowerAmount(PowerConsumable.GetObject());

		DistributedPower -= RequiredPowerAmount;
		IPowerConsumable::Execute_StopReceivingPower(PowerConsumable.GetObject());
	}
}
