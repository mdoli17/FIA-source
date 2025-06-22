// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Navigation/NavModifierGroupController.h"
#include "NavModifierVolume.h"


// Sets default values for this component's properties
UNavModifierGroupController::UNavModifierGroupController()
{
}

void UNavModifierGroupController::ActivateModifiers()
{
	for (TTuple<ANavModifierVolume*, TSubclassOf<UNavArea>> Tuple : NavModifiers)
	{
		Tuple.Key->SetAreaClass(ActiveNavAreaClass);
	}
}

void UNavModifierGroupController::DeactivateModifiers()
{
	for (TTuple<ANavModifierVolume*, TSubclassOf<UNavArea>> Tuple : NavModifiers)
	{
		Tuple.Key->SetAreaClass(Tuple.Value);
	}
}
