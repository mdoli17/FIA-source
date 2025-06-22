// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GrabComponent.h"

#include "Components/Grabbing/Grabbable.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


// Sets default values for this component's properties
UGrabComponent::UGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Handle"));
	ThrowingForce = 1000.0f;
}


// Called when the game starts
void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsGrabbing) return;

	PhysicsHandle->SetTargetLocation(GetComponentLocation() + GetForwardVector() * 150.0f);
	// ...
}

void UGrabComponent::Grab(AActor* ActorToGrab)
{
	if (bIsGrabbing) return;

	if (!ActorToGrab->Implements<UGrabbable>()) return;

	GrabbedActor = ActorToGrab;

	UPrimitiveComponent* ComponentToGrab = IGrabbable::Execute_GetComponentToGrab(GrabbedActor);
	PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, ComponentToGrab->GetComponentLocation());

	bIsGrabbing = true;

	IGrabbable::Execute_OnGrab(GrabbedActor);
}

void UGrabComponent::Release()
{
	if (!bIsGrabbing) return;

	PhysicsHandle->ReleaseComponent();

	IGrabbable::Execute_OnRelease(GrabbedActor);

	GrabbedActor = nullptr;
	bIsGrabbing = false;
}

void UGrabComponent::Throw()
{
	if (!bIsGrabbing) return;

	UPrimitiveComponent* ComponentToThrow = PhysicsHandle->GetGrabbedComponent();
	PhysicsHandle->ReleaseComponent();

	const FVector Impulse = GetForwardVector() * ThrowingForce;
	ComponentToThrow->AddImpulse(Impulse);
	IGrabbable::Execute_OnThrow(GrabbedActor);

	GrabbedActor = nullptr;
	bIsGrabbing = false;
}
