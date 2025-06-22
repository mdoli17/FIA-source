// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Interfaces/Alertable.h"
#include "Enemy/Ai/Patrolling/IPatrolPointCheckoutInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/AILurkingInterface.h"
#include "Interfaces/Investigator.h"
#include "EnemyCharacter.generated.h"

class UPatrolComponent;


UCLASS()
class FAITHINABYSS_API AEnemyCharacter : public ACharacter, public IAlertable, public IPatrolPointCheckoutInterface, public IInvestigator, public IAILurkingInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Alertable")
	void SetAlerted(EAlertType AlertType);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol Point")
	void CheckoutPatrolPoint(APatrolPoint* PatrolPoint);

	virtual void CheckoutPatrolPoint_Implementation(APatrolPoint* PatrolPoint) override;
	virtual FOnCheckoutPatrolPointFinishedSignature* GetCheckoutPatrolPointFinishedSignature() override;

	virtual void SetAlerted_Implementation(EAlertType AlertType) override;


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Combat")
	void Attack();

#pragma region AILurkingInterface

protected:
	FOnLurkedAroundEntranceSignature OnLurkedAroundDelegate;

public:
	virtual void LurkAroundEntrance_Implementation(const TScriptInterface<IAIEntranceInterface>& AIEntranceInterface) override;

	virtual FOnLurkedAroundEntranceSignature* GetLurkedAroundEntranceDelegate() override
	{
		return &OnLurkedAroundDelegate;
	}

#pragma endregion

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Patrolling", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPatrolComponent> PatrolComponent;

	UPROPERTY(BlueprintAssignable)
	FOnCheckoutPatrolPointFinishedSignature OnCheckoutPatrolPointFinished;
};
