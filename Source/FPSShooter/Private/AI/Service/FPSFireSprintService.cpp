// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/FPSFireSprintService.h"
#include "FPSUtils.h"
#include "AI/FPSAICharacter.h"
#include "Components/FPSCharacterMovementComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

UFPSFireSprintService::UFPSFireSprintService()
{
	NodeName = "SprintFire";
}

void UFPSFireSprintService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto Character = Cast<AFPSAICharacter>(Controller->GetPawn());
		
		if (Character)
		{
			Character->IsMovingForward = false;
			Character->OnStopRunning();
			
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}