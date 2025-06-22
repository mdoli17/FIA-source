// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damagable.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "Components/Hiding/Hidable.h"
#include "Item System/Chest/ItemTransferInterface.h"
#include "Stealth/Detectable.h"
#include "Detective.generated.h"

class UInteractionComponent;
class UGrabComponent;
class UActionComponent;
class UTransferInventoryWidget;
class UInventoryWidget;
class UInventoryComponent;
class UAIPerceptionStimuliSourceComponent;
class UAttributeComponent;
class UCameraComponent;
class UFocusComponent;

UCLASS()
class FAITHINABYSS_API ADetective : public ACharacter, public IDamagable, public IDetectable, public IItemTransferInterface, public IHidable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADetective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<UTransferInventoryWidget> TransferInventoryWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category="UI")
	TObjectPtr<UInventoryWidget> InventoryWidget;

	UPROPERTY(BlueprintReadOnly, Category="UI")
	TObjectPtr<UTransferInventoryWidget> TransferInventoryWidget;

#pragma region Input

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputLean;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputQuickLookBack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputCrouch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputGrab;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputRelease;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InputThrow;

	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void CompleteLook(const FInputActionValue& Value);
	virtual void CharacterJump(const FInputActionValue& Value);
	virtual void Sprint(const FInputActionValue& Value);
	virtual void Lean(const FInputActionValue& Value);
	virtual void QuickLookBack(const FInputActionValue& Value);
	virtual void CharacterCrouch(const FInputActionValue& Value);
	virtual void Interact(const FInputActionValue& Value);
	virtual void ShowInventory(const FInputActionValue& Value);

	virtual void Grab(const FInputActionValue& Value);
	virtual void Release(const FInputActionValue& Value);
	virtual void Throw(const FInputActionValue& Value);

#pragma endregion

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sounds")
	TObjectPtr<USoundBase> JumpSound;

#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<USceneComponent> CameraRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<UInteractionComponent> InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<UFocusComponent> FocusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<UAttributeComponent> StaminaComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<UAttributeComponent> HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<UAIPerceptionStimuliSourceComponent> PerceptionStimuliSourceComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<UActionComponent> ActionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")
	TObjectPtr<UGrabComponent> GrabComponent;


#pragma endregion

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void SetupMappingContext(UInputMappingContext* MappingContext, const int32 Priority, bool Clear = false);

	virtual void TakeDamage_Implementation(float Amount) override;
	virtual void SetupTransfer_Implementation(UInventoryComponent* TransferInventoryComponent) override;

	virtual bool GetIsDetectable_Implementation() override;
	virtual FOnDetectionUpdatedSignature* GetDetectionUpdatedDelegate() override;

private:
	UPROPERTY(BlueprintAssignable)
	FOnDetectionUpdatedSignature OnDetectionUpdated;
};
