// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Interaction/FocusComponent.h"
#include "Components/Interaction/Focusable.h"

UFocusComponent::UFocusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFocusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get new interactable
	AActor* NewlyTracedActor = Trace();

	// Don't continue if actor isn't new
	if (NewlyTracedActor == TracedActor) return;

	// Unfocus old actor if possible
	if (TracedActor != nullptr)
	{
		if (TracedActor->Implements<UFocusable>())
			IFocusable::Execute_Unfocus(TracedActor);
	}

	// Focus new actor if possible
	if (NewlyTracedActor != nullptr)
	{
		if (NewlyTracedActor->Implements<UFocusable>())
			IFocusable::Execute_Focus(NewlyTracedActor);
	}

	TracedActor = NewlyTracedActor;
}

AActor* UFocusComponent::Trace() const
{
	FHitResult Hit;
	const FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * TraceDistance;
	ECollisionChannel Channel = TraceChannel;
	FCollisionQueryParams Params;

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, Params);

	if (AActor* HitActor = Hit.GetActor(); Hit.IsValidBlockingHit() && IsValid(HitActor))
	{
		{
			return HitActor;
		}
	}

	return nullptr;
}
