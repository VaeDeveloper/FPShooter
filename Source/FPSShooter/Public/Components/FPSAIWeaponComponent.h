// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/FPSWeaponComponent.h"
#include "FPSAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API UFPSAIWeaponComponent : public UFPSWeaponComponent
{
	GENERATED_BODY()
	
public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};
