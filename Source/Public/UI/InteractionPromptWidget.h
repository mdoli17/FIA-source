// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionPromptWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UInteractionPromptWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> ActionIconField;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> ActionNameField;

	
public:
	UFUNCTION(BlueprintCallable)
	void Setup(UTexture2D* ActionIcon, const FText& ActionName);

	UFUNCTION(BlueprintCallable)
	void Show();

	UFUNCTION(BlueprintCallable)
	void Hide();
};
