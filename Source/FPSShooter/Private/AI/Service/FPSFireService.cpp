// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/FPSFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "FPSUtils.h"
#include "Components/FPSWeaponComponent.h"




UFPSFireService::UFPSFireService()
{
	NodeName = "Fire";
}

void UFPSFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	
	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto WeaponComponent = FPSUtils::GetFPSPlayerComponent<UFPSWeaponComponent>(Controller->GetPawn());
		
		if (WeaponComponent)
		{
			if (HasAim) 
			{
				WeaponComponent->StartFire();
				
			}
			else
			{
				WeaponComponent->StopFire();
			}
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
