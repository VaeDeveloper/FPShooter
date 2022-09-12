// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/FPSAILocationTasks.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UFPSAILocationTasks::UFPSAILocationTasks()
{
	NodeName = "NextLocation";
}

EBTNodeResult::Type UFPSAILocationTasks::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller && !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	const auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
	if(!NavSystem) return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	auto Location = Pawn->GetActorLocation();
	if (!SelfCenter)
	{
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if (!CenterActor) return EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();
	}

	const auto Found = NavSystem->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
	if (!Found) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;



	
}
