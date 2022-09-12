// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/FPSAmmoEmptyDecorator.h"
#include "AIController.h"
#include "FPSUtils.h"
#include "Components/FPSWeaponComponent.h"

UFPSAmmoEmptyDecorator::UFPSAmmoEmptyDecorator()
{
	NodeName = "AmmoEmpty";
}

bool UFPSAmmoEmptyDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto WeaponComponent = FPSUtils::GetFPSPlayerComponent<UFPSWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);

}
