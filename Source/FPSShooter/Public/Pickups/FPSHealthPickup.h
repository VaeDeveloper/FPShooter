// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/FPSBasePickup.h"
#include "FPSHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API AFPSHealthPickup : public AFPSBasePickup
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float HealthAmount = 100.0f;


private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
