// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FPSLauncherWeapon.h"
#include "Weapons/FPSProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


void AFPSLauncherWeapon::StartFire()
{	
	MakeShot();
	
	StartCoolDownTimer();
}

void AFPSLauncherWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotCoolDownTimerHandle);
}

void AFPSLauncherWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{

		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);


	//Spawn Projectile Function (функция спавна проджектай
	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AFPSProjectile*  Projectile = GetWorld()->SpawnActorDeferred<AFPSProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}

	DecreaseAmmo();
	PlayCameraShake();
	SpawnMuzzleFX();
	UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
	
}

void AFPSLauncherWeapon::PlayCameraShake()
{
	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(FireCameraShake);
}

void AFPSLauncherWeapon::StartCoolDownTimer()
{
	GetWorldTimerManager().SetTimer(ShotCoolDownTimerHandle, this, &AFPSLauncherWeapon::MakeShot, CoolDownTime, true);
	CoolDownTimeOff = false;
}
