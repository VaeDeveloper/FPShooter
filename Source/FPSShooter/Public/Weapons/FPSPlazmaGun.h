// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FPSBaseWeapon.h"
#include "FPSPlazmaGun.generated.h"


class UFPSWeaponFXComponent;
class UNiagaraComponent;
class AFPSProjectile;
class UAudioComponent;

UCLASS()
class FPSSHOOTER_API AFPSPlazmaGun : public AFPSBaseWeapon
{
	GENERATED_BODY()
	

public:
	AFPSPlazmaGun();

	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float TimeBetweenShot = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float BulletSpread = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float DamageAmount = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UFPSWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AFPSProjectile> ProjectileClass;

	


	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;


private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	UPROPERTY()
	UAudioComponent* FireAudioComponent;

	void InitFX();
	void SetFXActive(bool IsActive);
	void PlayCameraShake();
	

};
