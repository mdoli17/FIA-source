// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Entrance/Entrance.h"

// Sets default values
AEntrance::AEntrance()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetHidden(false);
	SetActorEnableCollision(true);

	PointLinks.Empty();
	bSmartLinkIsRelevant = true;
}

void AEntrance::BeginPlay()
{
	Super::BeginPlay();

	OnSmartLinkReached.AddUniqueDynamic(this, &AEntrance::SmartLinkReachHandler);
}

void AEntrance::Interact_Implementation(AActor* Caller)
{
	bIsOpen ? Close(Caller) : Open(Caller);
}

void AEntrance::Open(AActor* Caller)
{
	if (bIsOpen) return;

	bIsOpen = true;
	OnOpen(Caller);
	OnEntranceStateUpdated.Broadcast(bIsOpen);
}

void AEntrance::Close(AActor* Caller)
{
	if (!bIsOpen) return;

	bIsOpen = false;
	OnClose(Caller);
	OnEntranceStateUpdated.Broadcast(bIsOpen);
}

void AEntrance::Toggle(AActor* Caller)
{
	bIsOpen ? Close(Caller) : Open(Caller);
}

void AEntrance::SmartLinkReachHandler(AActor* MovingActor, const FVector& DestinationPoint)
{
	if (!bIsOpen) Open(MovingActor);
}
