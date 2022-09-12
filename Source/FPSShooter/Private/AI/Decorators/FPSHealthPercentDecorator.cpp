// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/FPSHealthPercentDecorator.h"
#include "AIController.h"
#include "FPSUtils.h"
#include "Components/FPSHealthComponent.h"

UFPSHealthPercentDecorator::UFPSHealthPercentDecorator()
{
	NodeName = "HealthPercent";
}

bool UFPSHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = FPSUtils::GetFPSPlayerComponent<UFPSHealthComponent>(Controller->GetPawn());
	if (!HealthComponent && HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
	
}
