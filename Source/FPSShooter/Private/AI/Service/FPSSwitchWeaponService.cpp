// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/FPSSwitchWeaponService.h"
#include "AIController.h"
#include "FPSUtils.h"
#include "Components/FPSWeaponComponent.h"

UFPSSwitchWeaponService::UFPSSwitchWeaponService()
{
	NodeName = "SwitchWeapon";
}

void UFPSSwitchWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = FPSUtils::GetFPSPlayerComponent<UFPSWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
