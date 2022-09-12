// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FPSBaseWeapon.h"
#include "FPSRifleWeapon.generated.h"

class UFPSWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UParticleSystem;
class UAudioComponent;

UCLASS()
class FPSSHOOTER_API AFPSRifleWeapon : public AFPSBaseWeapon
{
	GENERATED_BODY()
	

public:
	AFPSRifleWeapon();

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

	UPROPERTY(VisibleAnywhere,Category = "VFX")
	UFPSWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* ShotFXAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	FName FXSocketName = "FX_Socket";


	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
    void PlayCameraShake();

	

private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;
	UPROPERTY()
	UAudioComponent* FireAudioComponent;

	void InitFX();
	void MakeDamage(const FHitResult& HitResult);
	void ShotFX();
	void SetFXActive(bool IsActive);
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
	AController* GetController() const;

};
