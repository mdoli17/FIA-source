// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actions/ActionComponent.h"

#include "Components/Actions/Action.h"


void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupInitialActions();
}

// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UActionComponent::StartActionByName(FName ActionName, const FActionParams& Params)
{
	if (!Actions.Contains(ActionName)) return false;

	UAction* ActionToStart = Actions[ActionName];

	if (!ActionToStart->CanStartAction()) return false;

	const bool Started = ActionToStart->StartAction(Params);

	if (Started)
	{
		// Cancel necessary actions
		FGameplayTagContainer CancelingContainer = ActionToStart->CancelingTags;
		TArray<UAction*> RunningActionsCP = RunningActions;
		for (UAction* RunningAction : RunningActionsCP)
		{
			if (RunningAction->GrantingTags.HasAny(CancelingContainer))
			{
				StopActionByName(RunningAction->GetActionName());
			}
		}

		// Grant Tags
		ActiveGameplayTags.AppendTags(ActionToStart->GrantingTags);

		// Mark action as running
		RunningActions.Add(ActionToStart);

		OnTagsUpdated.Broadcast();
	}

	return Started;
}

bool UActionComponent::StopActionByName(FName ActionName)
{
	if (!Actions.Contains(ActionName)) return false;

	UAction* ActionToStop = Actions[ActionName];

	if (!ActionToStop->IsRunning()) return false;

	const bool Stopped = ActionToStop->StopAction();

	if (Stopped)
	{
		// Remove granting tags of action
		ActiveGameplayTags.RemoveTags(ActionToStop->GrantingTags);

		// Remove action as running
		RunningActions.Remove(ActionToStop);

		OnTagsUpdated.Broadcast();
	}

	return Stopped;
}

void UActionComponent::AddAction(TSubclassOf<UAction> ActionClass)
{
	if (!ensure(ActionClass)) return;

	UAction* NewAction = NewObject<UAction>(this, ActionClass);
	if (NewAction == nullptr) return;

	AActor* Owner = GetOwner();

	NewAction->Initialize(Owner);
	Actions.Add(NewAction->GetActionName(), NewAction);
}

void UActionComponent::RemoveAction(TSubclassOf<UAction> ActionClass)
{
	if (!ensure(ActionClass)) return;

	// TODO: Implement removing action.
}

void UActionComponent::SetupInitialActions()
{
	for (const TSubclassOf<UAction> InitialAction : InitialActions)
	{
		AddAction(InitialAction);
	}
}
