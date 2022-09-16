// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FPSRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "FPSUtils.h"
#include "Weapons/Components/FPSWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Player/FPSCharacter.h"
#include "FPSUtils.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"




AFPSRifleWeapon::AFPSRifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<UFPSWeaponFXComponent>("WeaponFXComponent");
}

void AFPSRifleWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponFXComponent);
}

void AFPSRifleWeapon::StartFire()
{
	InitFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AFPSRifleWeapon::MakeShot, TimeBetweenShot, true);
	MakeShot();
}

void AFPSRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetFXActive(false);
}

void AFPSRifleWeapon::GetDamage(float DamageInst)
{
	DamageAmount = DamageInst;
	
}

void AFPSRifleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{	
		const auto Player = Cast<AFPSCharacter>(GetOwner());
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
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
	DecreaseAmmo();
	PlayCameraShake();
	SpawnMuzzleFX();
	ShotFX();
}

void AFPSRifleWeapon::InitFX()
{
	if (!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
	}
	SetFXActive(true);
}

void AFPSRifleWeapon::SetFXActive(bool IsActive)
{
	if (FireAudioComponent)
	{
		FireAudioComponent->SetPaused(!IsActive);
	}
}

bool AFPSRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
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

void AFPSRifleWeapon::PlayCameraShake()
{
	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(FireCameraShake);
}

void AFPSRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamageActor = HitResult.GetActor();
	if (!DamageActor) return;

	FPointDamageEvent PointDamageEvent;
	PointDamageEvent.HitInfo = HitResult;
	DamageActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

void AFPSRifleWeapon::ShotFX()
{
	UGameplayStatics::SpawnEmitterAttached(ShotFXAmmo, WeaponMesh, FXSocketName);
}

void AFPSRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	if (TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

AController* AFPSRifleWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;

}
