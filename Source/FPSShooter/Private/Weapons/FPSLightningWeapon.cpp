// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FPSLightningWeapon.h"
#include "Weapons/Components/FPSWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Player/FPSCharacter.h"
#include "FPSUtils.h"




AFPSLightningWeapon::AFPSLightningWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<UFPSWeaponFXComponent>("WeaponFXComponent");
}

void AFPSLightningWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSLightningWeapon::StartFire()
{

	
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AFPSLightningWeapon::MakeShot, TimeBetweenShot, true);
	MakeShot();
}

void AFPSLightningWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void AFPSLightningWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		const auto Player = Cast<AFPSCharacter>(GetOwner());
		StopFire();
		return;
	}

	FVector TraceStart,TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;
	if (HitResult.bBlockingHit)
	{

		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	else
	{

	}
	DecreaseAmmo();
	PlayCameraShake();
	//InitLaserFX(GetMuzzleWorldLocation(),TraceEnd);
}


void AFPSLightningWeapon::PlayCameraShake()
{
	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(FireCameraShake);
}

bool AFPSLightningWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AFPSLightningWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamageActor = HitResult.GetActor();
	if (!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), this);
}

void AFPSLightningWeapon::InitLaserFX(const FVector& TraceStart, const FVector& TraceEnd)
{

	const auto LaserFX = UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, //
		WeaponMesh,                                        //
		MuzzleSocketName,                                  //
		FVector::ZeroVector,                               //
		FRotator::ZeroRotator,                             //
		EAttachLocation::SnapToTarget, true);

	
	if (LaserFX)
	{
		LaserFX->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

void AFPSLightningWeapon::SetLaserVisibility(bool Visibility)
{

}

AController* AFPSLightningWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}




