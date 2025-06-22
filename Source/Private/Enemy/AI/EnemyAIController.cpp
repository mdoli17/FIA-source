// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/EnemyAIController.h"

#include "Enemy/AI/Perception/AISenseTags.h"
#include "Enemy/Interfaces/Alertable.h"
#include "Detective.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"


AEnemyAIController::AEnemyAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));

	SetupPerceptionSystem();
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AEnemyAIController::PerceptionUpdateHandler);

	if (IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
	}
}

void AEnemyAIController::PerceptionUpdateHandler(AActor* Actor, FAIStimulus Stimulus)
{
	// Handle noise sense
	if (Stimulus.Tag == AISenseTags::NoiseTag)
	{
		// Ignore sound sense if chasing player
		if (BlackboardComponent->GetValueAsEnum(AlertTypeKey) == Alert) return;

		HandleSensingSound(Stimulus);

		return;
	}

	// Handle sight sense
	if (Stimulus.WasSuccessfullySensed())
		HandleSensingSight(Actor);
	else
		HandleLosingSight(Actor);
}

void AEnemyAIController::HandleSensingSound(FAIStimulus Stimulus) const
{
	if (BlackboardComponent->GetValueAsEnum(AlertTypeKey) == Alert) return;

	const FVector StimulusLocation = Stimulus.StimulusLocation;
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSys == nullptr) return;

	FNavLocation ProjectedLocation;
	FVector SearchExtent(500.0f, 500.0f, 500.0f); // TODO: Expose search extent

	if (!NavSys->ProjectPointToNavigation(StimulusLocation, ProjectedLocation, SearchExtent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find navigable location for sound stimuli"));
		return;
	}

	PrepareForInvestigation(ProjectedLocation.Location);
}


void AEnemyAIController::HandleSensingSight(AActor* SeenActor)
{
	// Check if SeenActor is player
	ADetective* Detected = Cast<ADetective>(SeenActor);
	if (!IsValid(Detected)) return;

	// Store player reference
	Detective = Detected;

	HandleSeeingPlayer();
}

void AEnemyAIController::HandleLosingSight(AActor* LostActor)
{
	// Check if LostActor is player
	if (const ADetective* Lost = Cast<ADetective>(LostActor); !IsValid(Lost)) return;

	HandleLosingSightOfPlayer();
}

void AEnemyAIController::HandleSeeingPlayer()
{
	check(Detective);

	BlackboardComponent->SetValueAsBool(HasSightKey, true);
	BlackboardComponent->SetValueAsObject(TargetActorKey, Detective);
	BlackboardComponent->SetValueAsEnum(AlertTypeKey, Alert);

	if (GetPawn()->Implements<UAlertable>())
		IAlertable::Execute_SetAlerted(GetPawn(), Alert);
}

void AEnemyAIController::HandleLosingSightOfPlayer()
{
	const FVector LastKnownLocation = Detective->GetActorLocation();

	// Clear player reference
	Detective = nullptr;
	BlackboardComponent->SetValueAsVector(TargetLastLocationKey, LastKnownLocation);
	BlackboardComponent->SetValueAsBool(HasSightKey, false);
	BlackboardComponent->SetValueAsObject(TargetActorKey, nullptr);
}

void AEnemyAIController::PrepareForInvestigation(const FVector& Location) const
{
	BlackboardComponent->SetValueAsVector(InvestigationLocationKey, Location);
	BlackboardComponent->SetValueAsEnum(AlertTypeKey, Investigate);

	if (GetPawn()->Implements<UAlertable>())
		IAlertable::Execute_SetAlerted(GetPawn(), Investigate);
}

TEnumAsByte<EAlertType> AEnemyAIController::GetCurrentAlertType()
{
	return static_cast<EAlertType>(BlackboardComponent->GetValueAsEnum(AlertTypeKey));
}

void AEnemyAIController::SetupPerceptionSystem()
{
	// Setup sight config object
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	check(SightConfig);
	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = 2000.f;
	SightConfig->PeripheralVisionAngleDegrees = 60.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*SightConfig);

	// Setup hearing config object
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");
	check(HearingConfig);
	HearingConfig->HearingRange = 2000.f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*HearingConfig);
}
