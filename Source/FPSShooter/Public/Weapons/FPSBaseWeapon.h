// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSCoreTypes.h"
#include "FPSBaseWeapon.generated.h"



class USkeletalMeshComponent;
class UCameraShakeBase;
class UNiagaraSystem;
class UNiagaraComponent;
class UMySkeletalMeshComponent;
class USoundCue;


UCLASS()
class FPSSHOOTER_API AFPSBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	AFPSBaseWeapon();

	FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();
	bool IsFiring() const;

	void ChangeClip();
	bool CanReload() const;
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	bool TryToAddAmmo(int32 ClipAmount);
	void UseWeaponMesh();
	bool IsAmmoFull() const;

	FWeaponUIData GetUIData() const { return UIData; }
	FAmmoData GetAmmoData() const { return CurrentAmmo; }
	
	

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	FName MuzzleSocketName = "MuzzleFlash_Socket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float TraceMaxDistance = 15000;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo{15, 10, true};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> FireCameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* FireSound;

	virtual void BeginPlay() override;

	virtual void MakeShot();
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;


	
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	bool FireInProgress = false;
	FVector GetMuzzleWorldLocation() const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	void DecreaseAmmo();
	
	
	void LogAmmo();

	UNiagaraComponent* SpawnMuzzleFX();

private:
	FAmmoData CurrentAmmo;

	void PlayCameraShake();

};
