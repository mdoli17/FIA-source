// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Interaction/InteractionComponent.h"

#include "Components/Interaction/IInteractable.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::Interact(AActor* ActorToInteract)
{
	if (!ActorToInteract->Implements<UInteractable>()) return;

	IInteractable::Execute_Interact(ActorToInteract, GetOwner());
}
