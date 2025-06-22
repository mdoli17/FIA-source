// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Attribute/AttributeComponent.h"


// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	Reset();
	// ...
}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsBeingUsed)
	{
		const float UseAmount = AttributeUseRate * DeltaTime;
		const float OldValue = CurrentValue;
		CurrentValue = FMath::Max(CurrentValue - UseAmount, 0.0f);
		OnAttributeUpdated.Broadcast(OldValue, CurrentValue, MaxValue);
		if (CurrentValue == 0) HandleAttributeDepletion();
	}
	else
	{
		if (!bIsRegenerative) return;
		if (!bCanRegenerate || CurrentValue >= MaxValue) return;

		const float RegenAmount = RegenerationRate * DeltaTime;
		const float OldValue = CurrentValue;
		CurrentValue = FMath::Min(CurrentValue + RegenAmount, MaxValue);
		OnAttributeUpdated.Broadcast(OldValue, CurrentValue, MaxValue);
		if (CurrentValue == MaxValue) OnAttributeReplenished.Broadcast();
	}
}

bool UAttributeComponent::HasEnough(const float Amount) const
{
	return CurrentValue >= Amount;
}


void UAttributeComponent::SingleUse_Implementation(const float Amount)
{
	bCanRegenerate = false;
	const float OldValue = CurrentValue;
	CurrentValue = FMath::Max(CurrentValue - Amount, 0.0f);
	OnAttributeUpdated.Broadcast(OldValue, CurrentValue, MaxValue);
	CheckRegen();
}

void UAttributeComponent::StartUsing(const float UseRate)
{
	AttributeUseRate += UseRate;
	bIsBeingUsed = true;
	bCanRegenerate = false;
	GetWorld()->GetTimerManager().ClearTimer(RegenCheckTimerHandle);
}

void UAttributeComponent::StopUsing(const float UseRate)
{
	if (!bIsBeingUsed) return;

	AttributeUseRate = FMath::Max(AttributeUseRate - UseRate, 0.0f);
	bIsBeingUsed = AttributeUseRate != 0.0f;

	CheckRegen();
}

void UAttributeComponent::Reset()
{
	CurrentValue = MaxValue;
}


void UAttributeComponent::HandleAttributeDepletion()
{
	bIsBeingUsed = false;
	AttributeUseRate = 0.0f;
	OnAttributeDepleted.Broadcast();
	CheckRegen();
}


void UAttributeComponent::CheckRegen()
{
	if (!bIsBeingUsed)
	{
		GetWorld()->GetTimerManager().SetTimer(RegenCheckTimerHandle, this, &UAttributeComponent::RegenCheckCallback, RegenerationStartDelay);
	}
}

void UAttributeComponent::RegenCheckCallback()
{
	bCanRegenerate = true;
	GetWorld()->GetTimerManager().ClearTimer(RegenCheckTimerHandle);
}
