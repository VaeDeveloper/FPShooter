// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FPSBaseWeapon.h"
#include "FPSLauncherWeapon.generated.h"

class AFPSProjectile;
class USoundCue;

UCLASS()
class FPSSHOOTER_API AFPSLauncherWeapon : public AFPSBaseWeapon
{
	GENERATED_BODY()

public:

	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AFPSProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* NoAmmoSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float CoolDownTime = 1.0f;

	virtual void MakeShot() override;
	void PlayCameraShake();

private:
	FTimerHandle ShotCoolDownTimerHandle;

	void StartCoolDownTimer();

	bool CoolDownTimeOff = true;
};
