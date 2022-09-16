// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/FPSPowerUpClass.h"


AFPSPowerUpClass::AFPSPowerUpClass()
{
 	
	PowerUpInterval = 0.f;
	TotalNrOfTicks = 0;

}

void AFPSPowerUpClass::BeginPlay()
{
	Super::BeginPlay();


}

void AFPSPowerUpClass::OnTickPowerUp()
{
	TicksProcessed++;

	OnPowerupTicked();

	if (TicksProcessed >= TotalNrOfTicks)
	{
		OnExpired();

		GetWorldTimerManager().ClearTimer(PowerTick);
	}
}

void AFPSPowerUpClass::ActivatePowerUp()
{
	OnActivatePowerUp();

	if (PowerUpInterval > 0.f)
	{
		GetWorldTimerManager().SetTimer(PowerTick, this, &AFPSPowerUpClass::OnTickPowerUp, PowerUpInterval, true, 0.f);
	}
	else
	{
		OnTickPowerUp();
	}

}


