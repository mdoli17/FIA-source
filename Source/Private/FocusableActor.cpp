// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusableActor.h"

#include "Components/WidgetComponent.h"
#include "UI/InteractionPromptWidget.h"


// Sets default values
AFocusableActor::AFocusableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	InteractionPromptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Prompt UI"));

	InteractionPromptWidget->SetupAttachment(RootComponent);

	InteractionPromptWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void AFocusableActor::BeginPlay()
{
	Super::BeginPlay();
	if (InteractionPromptWidgetClass == nullptr) return;
	InteractionPromptWidget->SetWidgetClass(InteractionPromptWidgetClass);
	PromptInstance = Cast<UInteractionPromptWidget>(InteractionPromptWidget->GetWidget());
	check(PromptInstance);
	PromptInstance->Setup(InteractionPromptIcon, InteractionPromptText);
}

// Called every frame
void AFocusableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFocusableActor::Focus_Implementation()
{
	IFocusable::Focus_Implementation();
	check(PromptInstance);
	PromptInstance->Show();
}

void AFocusableActor::Unfocus_Implementation()
{
	IFocusable::Unfocus_Implementation();
	check(PromptInstance);
	PromptInstance->Hide();
}
