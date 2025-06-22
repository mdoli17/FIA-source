// Fill out your copyright notice in the Description page of Project Settings.


#include "Item System/ItemPreviewActor.h"

#include "FCTween.h"
#include "Components/SceneCaptureComponent2D.h"


// Sets default values
AItemPreviewActor::AItemPreviewActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture"));

	SceneComponent->SetupAttachment(RootComponent);
	StaticMesh->SetupAttachment(SceneComponent);
	SceneCapture->SetupAttachment(SceneComponent);
}

void AItemPreviewActor::Initialize(const FItemData ItemData)
{
	StaticMesh->SetStaticMesh(ItemData.Mesh);
}

void AItemPreviewActor::Deinitialize()
{
	StaticMesh->SetStaticMesh(nullptr);
}

void AItemPreviewActor::StartRotation()
{
	if (RotationResetTween != nullptr) RotationResetTween->Pause();
}

void AItemPreviewActor::Rotate(const FVector2D& RotationInput)
{
	const FVector UpVector = SceneCapture->GetUpVector();
	const FVector ForwardVector = SceneCapture->GetRightVector();

	const float XRotationRad = FMath::DegreesToRadians(RotationInput.X);
	const float YRotationRad = FMath::DegreesToRadians(RotationInput.Y);

	const FQuat UpRotationQuat = FQuat(UpVector, XRotationRad);
	const FQuat ForwardRotationQuat = FQuat(ForwardVector, YRotationRad);

	const FQuat CombinedRotationQuat = UpRotationQuat * ForwardRotationQuat;

	const FQuat CurrentRotationQuat = StaticMesh->GetComponentQuat();

	const FQuat NewRotationQuat = CombinedRotationQuat * CurrentRotationQuat;

	StaticMesh->SetWorldRotation(NewRotationQuat);
}


void AItemPreviewActor::ResetRotation(const bool Instant)
{
	if (RotationResetTween != nullptr) RotationResetTween->Destroy();

	const FQuat StartRotation = StaticMesh->GetRelativeRotation().Quaternion();
	const FQuat EndRotation = FRotator::ZeroRotator.Quaternion();

	if (Instant)
	{
		StaticMesh->SetRelativeRotation(FRotator::ZeroRotator);
		return;
	}

	RotationResetTween = FCTween::Play(StartRotation, EndRotation, [&](const FQuat& T)
	{
		StaticMesh->SetRelativeRotation(T);
	}, RotationResetDuration, RotationResetEase);
}
