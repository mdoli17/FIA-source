// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteractionPromptWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInteractionPromptWidget::NativeConstruct()
{
	Hide();
}

void UInteractionPromptWidget::Setup(UTexture2D* ActionIcon, const FText& ActionName)
{
	check(ActionIconField);
	check(ActionNameField);
	check(ActionIcon);

	ActionIconField->SetBrushFromTexture(ActionIcon);
	ActionNameField->SetText(ActionName);
}

void UInteractionPromptWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UInteractionPromptWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}
