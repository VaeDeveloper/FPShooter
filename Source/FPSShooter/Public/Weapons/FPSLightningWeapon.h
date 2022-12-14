// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FPSBaseWeapon.h"
#include "FPSLightningWeapon.generated.h"


class UFPSWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;



UCLASS()
class FPSSHOOTER_API AFPSLightningWeapon : public AFPSBaseWeapon
{
	GENERATED_BODY()
	

public:
	AFPSLightningWeapon();

	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float TimeBetweenShot = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	float BulletSpread = 0.6f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float DamageAmount = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UFPSWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
	virtual void MakeShot() override;
	void PlayCameraShake();

	


private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* LaserFXComponent;

	void MakeDamage(const FHitResult& HitResult);
	void InitLaserFX(const FVector& TraceStart,const FVector& TraceEnd);
	void SetLaserVisibility(bool Visibility);
	AController* GetController() const;
};
