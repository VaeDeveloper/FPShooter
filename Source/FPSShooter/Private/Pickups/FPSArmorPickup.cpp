// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/FPSArmorPickup.h"
#include "Components/FPSHealthComponent.h"
#include "FPSUtils.h"

bool AFPSArmorPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = FPSUtils::GetFPSPlayerComponent<UFPSHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;


	return HealthComponent->TryToAddArmor(ArmorAmount);;
	
}
