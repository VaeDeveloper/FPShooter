// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPSPlayerHUDWidget.h"
#include "Components/FPSHealthComponent.h"
#include "Components/FPSWeaponComponent.h"
#include "FPSUtils.h"


void UFPSPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	const auto HealthComponent = FPSUtils::GetFPSPlayerComponent<UFPSHealthComponent>(GetOwningPlayerPawn());
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UFPSPlayerHUDWidget::OnHealthChange);
		HealthComponent->OnArmorChanged.AddUObject(this, &UFPSPlayerHUDWidget::OnArmorChange);
	}
}

float UFPSPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = FPSUtils::GetFPSPlayerComponent<UFPSHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

float UFPSPlayerHUDWidget::GetArmorPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(UFPSHealthComponent::StaticClass());
	const auto ArmorComponent = Cast<UFPSHealthComponent>(Component);
	if (!ArmorComponent) return 0.0f;

	return ArmorComponent->GetArmorPercent();
}

bool UFPSPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = FPSUtils::GetFPSPlayerComponent<UFPSWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool UFPSPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = FPSUtils::GetFPSPlayerComponent<UFPSWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool UFPSPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = FPSUtils::GetFPSPlayerComponent<UFPSHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}




bool UFPSPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

void UFPSPlayerHUDWidget::OnHealthChange(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
	
}

void UFPSPlayerHUDWidget::OnArmorChange(float Armor, float ArmorDelta)
{
	if (ArmorDelta < 0.0f)
	{
		OnTakeDamage();
	}
	
}



