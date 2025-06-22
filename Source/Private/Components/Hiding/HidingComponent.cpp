// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Hiding/HidingComponent.h"


// Sets default values for this component's properties
UHidingComponent::UHidingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHidingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UHidingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHidingComponent::EnterHiding_Implementation(AHidingSpot* HidingSpot)
{
	TagContainer.AddTag(HideTag);
}

void UHidingComponent::LeaveHiding_Implementation()
{
	TagContainer.RemoveTag(HideTag);
}
