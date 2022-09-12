// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FPSAIController.h"
#include "AI/FPSAICharacter.h"
#include "Components/FPSAIPerceptionComponent.h"
#include "Components/FPSRespawnComponent.h"

#include "BehaviorTree/BlackboardComponent.h"

AFPSAIController::AFPSAIController()
{
	FPSAIPerceptionComponent = CreateDefaultSubobject<UFPSAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*FPSAIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<UFPSRespawnComponent>("RespawnComponent");

	bWantsPlayerState = true;
}

void AFPSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto FPSCharacter = Cast<AFPSAICharacter>(InPawn);
	if (FPSCharacter)
	{
		RunBehaviorTree(FPSCharacter->BehaviorTreeAsset);
	}
}

void AFPSAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* AFPSAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
