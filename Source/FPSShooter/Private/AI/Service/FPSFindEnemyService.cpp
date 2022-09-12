// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/FPSFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "FPSUtils.h"
#include "Components/FPSAIPerceptionComponent.h"
#include "GameFramework/Character.h"

UFPSFindEnemyService::UFPSFindEnemyService()
{
	NodeName = "Find Enemy";
	
}

void UFPSFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		
		
		const auto PerceptionComponent = FPSUtils::GetFPSPlayerComponent<UFPSAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
