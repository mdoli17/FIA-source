// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyCharacter.h"

#include "Enemy/AI/Patrolling/PatrolComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PatrolComponent = CreateDefaultSubobject<UPatrolComponent>(TEXT("Patrol Component"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::CheckoutPatrolPoint_Implementation(APatrolPoint* PatrolPoint)
{
	OnCheckoutPatrolPointFinished.Broadcast();
}

FOnCheckoutPatrolPointFinishedSignature* AEnemyCharacter::GetCheckoutPatrolPointFinishedSignature()
{
	return &OnCheckoutPatrolPointFinished;
}

void AEnemyCharacter::SetAlerted_Implementation(EAlertType AlertType)
{
	IAlertable::SetAlerted_Implementation(AlertType);
	// TODO: Update character visuals and animations based on AlertType.
}

void AEnemyCharacter::LurkAroundEntrance_Implementation(const TScriptInterface<IAIEntranceInterface>& AIEntranceInterface)
{
	OnLurkedAroundDelegate.Broadcast();
}
