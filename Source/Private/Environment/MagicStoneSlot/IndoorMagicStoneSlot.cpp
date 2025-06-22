// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/MagicStoneSlot/IndoorMagicStoneSlot.h"

#include "Environment/Entrance/Entrance.h"


// Sets default values
AIndoorMagicStoneSlot::AIndoorMagicStoneSlot()
{
}

void AIndoorMagicStoneSlot::BeginPlay()
{
	Super::BeginPlay();

	for (AEntrance* Entrance : Entrances)
	{
		Entrance->OnEntranceStateUpdated.AddDynamic(this, &AIndoorMagicStoneSlot::EntranceStateUpdateHandler);
	}
}

void AIndoorMagicStoneSlot::Activate()
{
	if (!CanActivate()) return;

	Super::Activate();
}

void AIndoorMagicStoneSlot::EntranceStateUpdateHandler(bool IsOpen)
{
	if (IsOpen)
	{
		Deactivate();
	}
	else if (HasStone() && CanActivate())
	{
		Activate();
	}
}

bool AIndoorMagicStoneSlot::CanActivate()
{
	for (const AEntrance* Entrance : Entrances)
	{
		if (Entrance->IsOpen()) return false;
	}

	return true;
}
