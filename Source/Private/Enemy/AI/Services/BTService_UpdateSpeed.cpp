// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Services/BTService_UpdateSpeed.h"

#include "AIController.h"
#include "Enemy/EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_UpdateSpeed::UBTService_UpdateSpeed()
{
	NodeName = TEXT("Change Speed");
}

void UBTService_UpdateSpeed::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
	const AAIController* AIController = SearchData.OwnerComp.GetAIOwner();
	check(AIController);
	APawn* Pawn = AIController->GetPawn();
	const AEnemyCharacter* Character = Cast<AEnemyCharacter>(Pawn);
	check(Character);
	Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
}
