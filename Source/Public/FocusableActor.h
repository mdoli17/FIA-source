// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Interaction/Focusable.h"
#include "GameFramework/Actor.h"
#include "FocusableActor.generated.h"

class UInteractionPromptWidget;
class UWidgetComponent;
class UBoxComponent;

UCLASS()
class FAITHINABYSS_API AFocusableActor : public AActor, public IFocusable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFocusableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<UInteractionPromptWidget> InteractionPromptWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TObjectPtr<UWidgetComponent> InteractionPromptWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TObjectPtr<UTexture2D> InteractionPromptIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	FText InteractionPromptText;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UInteractionPromptWidget> PromptInstance;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Focus_Implementation() override;
	virtual void Unfocus_Implementation() override;
};
