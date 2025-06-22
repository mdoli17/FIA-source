// Fill out your copyright notice in the Description page of Project Settings.


#include "Detective.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Interaction/FocusComponent.h"
#include "Components/Attribute/AttributeComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/GrabComponent.h"
#include "Components/Actions/ActionComponent.h"
#include "Components/Interaction/InteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item System/InventoryComponent.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionStimuliSourceComponent.h"
#include "UI/InventoryWidget.h"
#include "UI/TransferInventoryWidget.h"

// Sets default values
ADetective::ADetective()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraRootComponent = CreateDefaultSubobject<USceneComponent>("Camera Root Component");
	CameraRootComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(CameraRootComponent);
	CameraComponent->SetRelativeLocation(FVector(0, 0, 88.0f));

	FocusComponent = CreateDefaultSubobject<UFocusComponent>(TEXT("Focus Component"));
	FocusComponent->SetupAttachment(CameraComponent);
	FocusComponent->SetRelativeLocation(FVector::Zero());

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction Component"));
	InteractionComponent->SetupAttachment(CameraComponent);

	GrabComponent = CreateDefaultSubobject<UGrabComponent>(TEXT("Grab Component"));
	GrabComponent->SetupAttachment(CameraComponent);

	StaminaComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("Stamina Component"));
	HealthComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("Health Component"));
	PerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Perception Stimuli Source Component"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	ActionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("Action Component"));
}

// Called when the game starts or when spawned
void ADetective::BeginPlay()
{
	Super::BeginPlay();
	InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
	TransferInventoryWidget = CreateWidget<UTransferInventoryWidget>(GetWorld(), TransferInventoryWidgetClass);
}

// Called every frame
void ADetective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADetective::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SetupMappingContext(InputMapping.LoadSynchronous(), 0, true);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(InputMove, ETriggerEvent::Triggered, this, &ADetective::Move);
	EnhancedInputComponent->BindAction(InputLook, ETriggerEvent::Triggered, this, &ADetective::Look);
	EnhancedInputComponent->BindAction(InputLook, ETriggerEvent::Completed, this, &ADetective::CompleteLook);
	EnhancedInputComponent->BindAction(InputJump, ETriggerEvent::Triggered, this, &ADetective::CharacterJump);
	EnhancedInputComponent->BindAction(InputSprint, ETriggerEvent::Triggered, this, &ADetective::Sprint);
	EnhancedInputComponent->BindAction(InputCrouch, ETriggerEvent::Triggered, this, &ADetective::CharacterCrouch);
	EnhancedInputComponent->BindAction(InputInteract, ETriggerEvent::Triggered, this, &ADetective::Interact);
	EnhancedInputComponent->BindAction(InputInventory, ETriggerEvent::Triggered, this, &ADetective::ShowInventory);
	EnhancedInputComponent->BindAction(InputLean, ETriggerEvent::Triggered, this, &ADetective::Lean);
	EnhancedInputComponent->BindAction(InputQuickLookBack, ETriggerEvent::Triggered, this, &ADetective::QuickLookBack);

	EnhancedInputComponent->BindAction(InputGrab, ETriggerEvent::Triggered, this, &ADetective::Grab);
	EnhancedInputComponent->BindAction(InputRelease, ETriggerEvent::Triggered, this, &ADetective::Release);
	EnhancedInputComponent->BindAction(InputThrow, ETriggerEvent::Triggered, this, &ADetective::Throw);
}

void ADetective::SetupMappingContext(UInputMappingContext* MappingContext, const int32 Priority, const bool Clear)
{
	if (MappingContext == nullptr) return;

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (Clear)
				InputSubsystem->ClearAllMappings();
			InputSubsystem->AddMappingContext(MappingContext, Priority);
		}
	}
}

void ADetective::Move(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;

	const FVector2D MoveValue = Value.Get<FVector2D>();

	FActionParams Params;
	Params.VectorValue = FVector(MoveValue.X, MoveValue.Y, 0.0f);
	if (MoveValue != FVector2D::ZeroVector)
	{
		ActionComponent->StartActionByName("Move", Params);
	}
	else
	{
		ActionComponent->StopActionByName("Move");
	}
}

void ADetective::Look(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	const FVector2D LookValue = Value.Get<FVector2D>();

	FActionParams Params;
	Params.VectorValue = FVector(LookValue.X, LookValue.Y, 0.0f);
	ActionComponent->StartActionByName("Look", Params);
}

void ADetective::CompleteLook(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	ActionComponent->StopActionByName("Look");
}


void ADetective::CharacterJump(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;

	ActionComponent->StartActionByName("Jump");
}

void ADetective::Sprint(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		ActionComponent->StartActionByName("Sprint");
	}
	else
	{
		ActionComponent->StopActionByName("Sprint");
	}
}

void ADetective::Lean(const FInputActionValue& Value)
{
	if (const float FloatValue = Value.Get<float>(); FloatValue == 0)
	{
		ActionComponent->StopActionByName("Lean");
	}
	else
	{
		FActionParams ActionParams;
		ActionParams.FloatValue = FloatValue;
		ActionComponent->StartActionByName("Lean", ActionParams);
	}
}

void ADetective::QuickLookBack(const FInputActionValue& Value)
{
	if (const float FloatValue = Value.Get<float>(); FloatValue == 0)
	{
		ActionComponent->StopActionByName("QuickLookBack");
	}
	else
	{
		FActionParams ActionParams;
		ActionParams.FloatValue = FloatValue;
		ActionComponent->StartActionByName("QuickLookBack", ActionParams);
	}
}


void ADetective::CharacterCrouch(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void ADetective::Interact(const FInputActionValue& Value)
{
	ActionComponent->StartActionByName("Interact");
}

void ADetective::ShowInventory(const FInputActionValue& Value)
{
	check(InventoryWidget);

	InventoryWidget->Setup(InventoryComponent);
	InventoryWidget->AddToViewport();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		PlayerController->bShowMouseCursor = true;

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

		PlayerController->SetInputMode(InputMode);
	}
}

void ADetective::Grab(const FInputActionValue& Value)
{
	ActionComponent->StartActionByName("Grab");
}

void ADetective::Release(const FInputActionValue& Value)
{
	ActionComponent->StopActionByName("Grab");
}

void ADetective::Throw(const FInputActionValue& Value)
{
	ActionComponent->StartActionByName("Throw");
}

void ADetective::TakeDamage_Implementation(const float Amount)
{
	HealthComponent->SingleUse(Amount);
}

void ADetective::SetupTransfer_Implementation(UInventoryComponent* TransferInventoryComponent)
{
	check(TransferInventoryWidget);

	TransferInventoryWidget->Setup(InventoryComponent, TransferInventoryComponent);
	TransferInventoryWidget->AddToViewport();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		PlayerController->bShowMouseCursor = true;

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TransferInventoryWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

		PlayerController->SetInputMode(InputMode);
	}
}

bool ADetective::GetIsDetectable_Implementation()
{
	return !GetMovementComponent()->IsCrouching();
}

FOnDetectionUpdatedSignature* ADetective::GetDetectionUpdatedDelegate()
{
	return &OnDetectionUpdated;
}
