// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/FPSJumpService.h"
#include "AI/FPSAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UFPSJumpService::UFPSJumpService()
{
	NodeName = "Jump";
}

void UFPSJumpService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller)
	{
		const auto Character = Cast<AFPSAICharacter>(Controller->GetPawn());
		if (Character && Probability && FMath::FRand() <= Probability)
		{	
			Character->Jump();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

