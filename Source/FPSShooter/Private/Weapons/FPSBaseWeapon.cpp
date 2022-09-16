// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FPSBaseWeapon.h"
#include "Components/FPSWeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Player/FPSCharacter.h"
#include "Camera/CameraShakeBase.h"
#include "NiagaraFunctionLibrary.h"
#include "FPSUtils.h"





AFPSBaseWeapon::AFPSBaseWeapon()
{

	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
	WeaponMesh->CastShadow = false;
	WeaponMesh->bCastDynamicShadow = false;


}

void AFPSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
	CurrentAmmo = DefaultAmmo;
}

void AFPSBaseWeapon::StartFire()
{
	FireInProgress = true;
}

void AFPSBaseWeapon::StopFire()
{
	FireInProgress = false;
}

bool AFPSBaseWeapon::IsFiring() const
{
	return FireInProgress;
}

void AFPSBaseWeapon::MakeShot()
{
	
}

bool AFPSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto FPSCharacter = Cast<ACharacter>(GetOwner());
	if (!FPSCharacter) return false;

	if (FPSCharacter->IsPlayerControlled())
	{
		const auto Controller = FPSCharacter->GetController<APlayerController>();
		if (!Controller) return false;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}


	return true;
}

FVector AFPSBaseWeapon::GetMuzzleWorldLocation() const // возвращает локацию сокета дула 
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}  

bool AFPSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;

	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AFPSBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParam;
	CollisionParam.AddIgnoredActor(GetOwner());
	CollisionParam.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParam);
}

void AFPSBaseWeapon::DecreaseAmmo()  
{
	const auto WeaponComponent = FPSUtils::GetFPSPlayerComponent<UFPSWeaponComponent>(GetOwner());
	if (CurrentAmmo.Bullets == 0) return;		
	
	CurrentAmmo.Bullets--;

	
	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		WeaponComponent->StopFire();
		//OnClipEmpty.Broadcast(this);  как добавить функцию в AI

	}
} 

bool AFPSBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool AFPSBaseWeapon::IsAmmoEmpty() const 
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AFPSBaseWeapon::IsClipEmpty() const 
{	
	return CurrentAmmo.Bullets == 0;
}

bool AFPSBaseWeapon::IsLastBullet() const
{
	
	return CurrentAmmo.Bullets < 2;
}


bool AFPSBaseWeapon::TryToAddAmmo(int32 ClipAmount)
{
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipAmount <= 0) return false;

	if (IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipAmount;

		if (DefaultAmmo.Clips - NextClipsAmount >= 0)
		{	
			
			CurrentAmmo.Clips = NextClipsAmount;
		}
		else
		{
			
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		}
	}
	else
	{
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}
	return true;
}

void AFPSBaseWeapon::UseWeaponMesh()
{
	WeaponMesh->SetVisibility(true);
}


void AFPSBaseWeapon::ChangeClip()
{	
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool AFPSBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && //
		CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void AFPSBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
}


UNiagaraComponent* AFPSBaseWeapon::SpawnMuzzleFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, //
		WeaponMesh,                                        //
		MuzzleSocketName,                                  //
		FVector::ZeroVector,                               //
		FRotator::ZeroRotator,                             //
		EAttachLocation::SnapToTarget, true);
}


void AFPSBaseWeapon::PlayCameraShake() {}
