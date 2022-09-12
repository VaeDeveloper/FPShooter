// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FPSBaseWeapon.h"
#include "FPSRailGun.generated.h"

class UFPSWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UParticleSystem;

UCLASS()
class FPSSHOOTER_API AFPSRailGun : public AFPSBaseWeapon
{
	GENERATED_BODY()

public:
	AFPSRailGun();


	virtual void StartFire() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float DamageAmount = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	float BulletSpread = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
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
	FTimerHandle ShotDownTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	void MakeDamage(const FHitResult& HitResult);
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
	AController* GetController() const;
};
