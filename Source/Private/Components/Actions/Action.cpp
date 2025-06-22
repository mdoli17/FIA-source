// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actions/Action.h"

#include "Components/Actions/ActionComponent.h"

void UAction::Initialize(AActor* Instigator)
{
	Owner = Instigator;
	Initialize();
}


bool UAction::StartAction(const FActionParams& Params)
{
	bIsRunning = StartActionImplementation(Params);

	return bIsRunning;
}

bool UAction::StopAction()
{
	ensureAlways(bIsRunning);

	const bool bActionStopped = StopActionImplementation();

	if (bActionStopped)
	{
		bIsRunning = false;
	}

	return bActionStopped;;
}

bool UAction::CanStartAction_Implementation()
{
	const UActionComponent* ActionComponent = GetOwningComponent();

	return !ActionComponent->ActiveGameplayTags.HasAny(BlockingTags);
}

UActionComponent* UAction::GetOwningComponent() const
{
	return Cast<UActionComponent>(GetOuter());
}

void UAction::Initialize_Implementation()
{
}

bool UAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	return true;
}

bool UAction::StopActionImplementation_Implementation()
{
	return true;
}
