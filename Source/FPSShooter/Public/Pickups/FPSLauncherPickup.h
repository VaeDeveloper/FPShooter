// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/FPSBasePickup.h"
#include "FPSLauncherPickup.generated.h"


class AFPSBaseWeapon;


UCLASS()
class FPSSHOOTER_API AFPSLauncherPickup : public AFPSBasePickup
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup");
	int32 ClipAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup");
	TSubclassOf<AFPSBaseWeapon> WeaponType;
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
