// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/FPSSprintService.h"
#include "AI/FPSAICharacter.h"
#include "Components/FPSCharacterMovementComponent.h"
#include "Components/FPSAIWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "FPSUtils.h"

UFPSSprintService::UFPSSprintService()
{
	NodeName = "Sprint";
}

void UFPSSprintService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto Character = Cast<AFPSAICharacter>(Controller->GetPawn());
		const auto WeaponComponent = FPSUtils::GetFPSPlayerComponent<UFPSWeaponComponent>(Controller->GetPawn());
		const auto MovementComponent = FPSUtils::GetFPSPlayerComponent<UFPSCharacterMovementComponent>(Controller->GetPawn());
		if (Character && MovementComponent  && Probability > 0 && FMath::FRand() <= Probability)
		{
			Character->IsMovingForward = true;
			Character->OnStartRunning();
		}
		else if (WeaponComponent->IsFiring())
		{
			Character->IsMovingForward = false;
			Character->OnStopRunning();
		}
		else
		{	
			Character->IsMovingForward = false;
			Character->OnStopRunning();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
