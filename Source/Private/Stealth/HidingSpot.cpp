// Fill out your copyright notice in the Description page of Project Settings.


#include "Stealth/HidingSpot.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/Hiding/Hidable.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AHidingSpot::AHidingSpot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));

	LockerInputComponent = CreateDefaultSubobject<UEnhancedInputComponent>(TEXT("Input Component"));

	SceneComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetupAttachment(SceneComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraComponent->SetActive(false);
	SpringArmComponent->bUsePawnControlRotation = false;
	bIsHiding = false;
}

// Called when the game starts or when spawned
void AHidingSpot::BeginPlay()
{
	Super::BeginPlay();

	LockerInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHidingSpot::Look);
	LockerInputComponent->BindAction(LeaveAction, ETriggerEvent::Triggered, this, &AHidingSpot::Leave);
}

// Called every frame
void AHidingSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHidingSpot::Interact_Implementation(AActor* Caller)
{
	// ------ Checks -------
	if (!Caller->Implements<UHidable>()) return;

	const APawn* Pawn = Cast<APawn>(Caller);

	if (Pawn == nullptr) return;

	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());

	if (PlayerController == nullptr) return;

	OwningPlayerController = PlayerController;

	CameraComponent->SetActive(true);
	EnableInputHandling();
	IHidable::Execute_EnterHiding(Caller, this);
	PlayerEnter();

	bIsHiding = true;
}

void AHidingSpot::Look(const FInputActionValue& Value)
{
	FRotator CurrentRotation = SpringArmComponent->GetRelativeRotation();
	const FVector2D LookValue = Value.Get<FVector2D>();

	CurrentRotation.Yaw = FMath::Clamp(CurrentRotation.Yaw + LookValue.X, -MaxYawRotation, MaxYawRotation);
	CurrentRotation.Pitch = FMath::Clamp(CurrentRotation.Pitch + LookValue.Y, -MaxPitchRotation, MaxPitchRotation);

	SpringArmComponent->SetRelativeRotation(CurrentRotation);
}

void AHidingSpot::Leave(const FInputActionValue& Value)
{
	CameraComponent->SetActive(false);
	DisableInputHandling();
	IHidable::Execute_LeaveHiding(OwningPlayerController->GetPawn());
	PlayerLeave();

	OwningPlayerController = nullptr;
	bIsHiding = false;
}

void AHidingSpot::EnableInputHandling()
{
	if (OwningPlayerController == nullptr) return;

	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(OwningPlayerController->GetLocalPlayer()))
	{
		InputSystem->AddMappingContext(MappingContext.LoadSynchronous(), 1);
	}

	OwningPlayerController->PushInputComponent(LockerInputComponent);
}

void AHidingSpot::DisableInputHandling()
{
	if (OwningPlayerController == nullptr) return;

	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(OwningPlayerController->GetLocalPlayer()))
	{
		InputSystem->RemoveMappingContext(MappingContext.LoadSynchronous());
	}

	OwningPlayerController->PopInputComponent(LockerInputComponent);
}
