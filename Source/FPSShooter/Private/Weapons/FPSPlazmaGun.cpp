// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FPSPlazmaGun.h"
#include "Weapons/Components/FPSWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/FPSProjectile.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"


AFPSPlazmaGun::AFPSPlazmaGun()
{
	WeaponFXComponent = CreateDefaultSubobject<UFPSWeaponFXComponent>("WeaponFXComponent");
}

void AFPSPlazmaGun::StartFire()
{
	InitFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AFPSPlazmaGun::MakeShot, TimeBetweenShot, true);
	MakeShot();
}

void AFPSPlazmaGun::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetFXActive(false);
}

void AFPSPlazmaGun::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}
	

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{	
		StopFire();
		return;
	}
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AFPSProjectile* Projectile = GetWorld()->SpawnActorDeferred<AFPSProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner()); 
		Projectile->FinishSpawning(SpawnTransform);
	}

	DecreaseAmmo();
	PlayCameraShake();
	SpawnMuzzleFX();
}

bool AFPSPlazmaGun::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
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

void AFPSPlazmaGun::InitFX()
{
	if (!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
	}
	SetFXActive(true);
}

void AFPSPlazmaGun::SetFXActive(bool IsActive)
{
	if (FireAudioComponent)
	{
		FireAudioComponent->SetPaused(!IsActive);
	}
}

void AFPSPlazmaGun::PlayCameraShake()
{
	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(FireCameraShake);
}
