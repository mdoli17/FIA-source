// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actions/PlayerAction.h"

#include "Detective.h"

void UPlayerAction::Initialize(AActor* Instigator)
{
	if (ADetective* Detective = Cast<ADetective>(Instigator))
	{
		Player = Detective;
	}

	Super::Initialize(Instigator);
}

UWorld* UPlayerAction::GetWorld() const
{
	if (const UActorComponent* Component = Cast<UActorComponent>(GetOuter()))
	{
		return Component->GetWorld();
	}

	return nullptr;
}
