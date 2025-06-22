// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item System/ItemData.h"
#include "InventoryItemPreviewWidget.generated.h"

class AItemPreviewActor;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class FAITHINABYSS_API UInventoryItemPreviewWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Setup(const FItemData ItemData);

	UFUNCTION(BlueprintCallable)
	void Clear();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Preview", meta=(AllowPrivateAccess=true))
	TSubclassOf<AItemPreviewActor> ItemPreviewActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item Preview", meta=(AllowPrivateAccess=true))
	FTransform ItemPreviewActorSpawnTransform;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UImage* PreviewImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* NameField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* DescriptionField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* WeightField;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<AItemPreviewActor> ItemPreviewActor;

private:
	bool bIsMouseDown;
	FVector2D LastMousePosition;
};
