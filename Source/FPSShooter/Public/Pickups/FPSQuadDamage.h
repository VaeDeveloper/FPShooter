// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/FPSBasePickup.h"
#include "FPSQuadDamage.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API AFPSQuadDamage : public AFPSBasePickup
{
	GENERATED_BODY()
	

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;

};
