// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FCEasing.h"
#include "ItemData.h"
#include "GameFramework/Actor.h"
#include "ItemPreviewActor.generated.h"

class FCTweenInstance;

UCLASS()
class FAITHINABYSS_API AItemPreviewActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemPreviewActor();

	/// Sets static mesh from Item Data
	UFUNCTION(BlueprintCallable, Category="Item Preview")
	void Initialize(const FItemData ItemData);

	// Clears static mesh component
	UFUNCTION(BlueprintCallable, Category="Item Preview")
	void Deinitialize();

	UFUNCTION(BlueprintCallable, Category="Item Preview | Control")
	void StartRotation();

	UFUNCTION(BlueprintCallable, Category="Item Preview | Control")
	void Rotate(const FVector2D& RotationInput);

	UFUNCTION(BlueprintCallable, Category="Item Preview | Control")
	void ResetRotation(const bool Instant = false);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<USceneCaptureComponent2D> SceneCapture;

	UPROPERTY(EditDefaultsOnly, Category="Properties", meta=(AllowPrivateAccess=true))
	float RotationResetDuration = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category="Properties", meta=(AllowPrivateAccess=true))
	EFCEase RotationResetEase = EFCEase::OutQuad;

	FCTweenInstance* RotationResetTween;
};
