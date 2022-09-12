// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/FPSLauncherPickup.h"
#include "Components/FPSHealthComponent.h"
#include "Components/FPSWeaponComponent.h"
#include "FPSUtils.h"

bool AFPSLauncherPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = FPSUtils::GetFPSPlayerComponent<UFPSHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;
        
    const auto WeaponComponent = FPSUtils::GetFPSPlayerComponent<UFPSWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;

    return WeaponComponent->TryToAddAmmo(WeaponType,ClipAmount);
    
}
