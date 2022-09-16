// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FPSAIPerceptionComponent.h"
#include "AIController.h"
#include "FPSUtils.h"
#include "Components/FPSHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"


AActor* UFPSAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0)
	{
		GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
		if (PercieveActors.Num() == 0) return nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = FPSUtils::GetFPSPlayerComponent<UFPSHealthComponent>(PercieveActor);

		const auto PercivePawn = Cast<APawn>(PercieveActor);
		const auto AreEnemies = PercivePawn && FPSUtils::AreEnemy(Controller, PercivePawn->Controller);

		if (HealthComponent && !HealthComponent->IsDead() && AreEnemies) 
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}
	return BestPawn;
}
