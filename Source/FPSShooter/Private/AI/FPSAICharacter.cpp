// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FPSAICharacter.h"
#include "AI/FPSAIController.h"
#include "Components/FPSAIWeaponComponent.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <BrainComponent.h>

AFPSAICharacter::AFPSAICharacter(const FObjectInitializer& ObjInit):
	Super(ObjInit.SetDefaultSubobjectClass<UFPSAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AFPSAIController::StaticClass();


	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f,0.0f, 400.0f);
	}
}

void AFPSAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto FPSController = Cast<AAIController>(Controller);
	if (FPSController && FPSController->BrainComponent)
	{
		FPSController->BrainComponent->Cleanup();
	}

}
