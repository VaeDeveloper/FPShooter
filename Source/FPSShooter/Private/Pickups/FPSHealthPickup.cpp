// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/FPSHealthPickup.h"
#include "Components/FPSHealthComponent.h"
#include "FPSUtils.h"

bool AFPSHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = FPSUtils::GetFPSPlayerComponent<UFPSHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
	
}
