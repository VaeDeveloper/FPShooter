// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FPSWeaponComponent.h"
#include "Weapons/FPSBaseWeapon.h"
#include "Player/FPSCharacter.h"
#include "Animations/FPSEquipWeaponAnimNotify.h"
#include "Animations/FPSReloadWeaponAnimNotify.h"
#include "Animations/FPSFireAnimNotify.h"
#include "Animations/AnimUtils.h"


constexpr static int32 WeaponNum = 5;

UFPSWeaponComponent::UFPSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFPSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ѕроверка кол-ва оружи€ у персонажа 
	checkf(WeaponData.Num() == WeaponNum, TEXT("Character not items!!!")); 
	CurrentWeaponIndex = 0;

	SpawnWeapons();
	InitAnimation();
	EquipWeapon(CurrentWeaponIndex);
		
}

void UFPSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void UFPSWeaponComponent::SpawnWeapons()
{

	AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<AFPSBaseWeapon>(OneWeaponData.WeaponClasses);
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &UFPSWeaponComponent::OnEmptyClip);
		
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);


		AttachWeaponToSocket(Weapon, Character->GetWeaponAttachmentMesh(), WeaponArmorySocketName);
	}


}
 
void UFPSWeaponComponent::AttachWeaponToSocket(AFPSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);

}

void UFPSWeaponComponent::EquipWeapon(int32 WeaponIndex)
{

	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		return;
	}
	AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();

		AttachWeaponToSocket(CurrentWeapon, Character->GetWeaponAttachmentMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {
		return Data.WeaponClasses == CurrentWeapon->GetClass();
		});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
	CurrentShotAnimMontage = CurrentWeaponData ? CurrentWeaponData->ShootAnimMontage : nullptr;
	AttachWeaponToSocket(CurrentWeapon, Character->GetWeaponAttachmentMesh(), WeaponEquipSocketName);
	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void UFPSWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
	if (Character)
	{
		
		Character->GetWeaponAttachmentMesh()->AnimScriptInstance->Montage_Play(Animation);
	}
	
}

void UFPSWeaponComponent::StopAnimMontage(UAnimMontage* Animation)
{
	AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
	if (!Character) return;

	Character->GetWeaponAttachmentMesh()->AnimScriptInstance->Montage_Stop(Animation->BlendOut.GetBlendTime(), Animation);
}

void UFPSWeaponComponent::InitAnimation()
{
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UFPSEquipWeaponAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{

		EquipFinishedNotify->OnNotified.AddUObject(this, &UFPSWeaponComponent::OnEquipFinished);
	}
	else
	{
		checkNoEntry();
	}

	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UFPSReloadWeaponAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify) continue;
		ReloadFinishedNotify->OnNotified.AddUObject(this, &UFPSWeaponComponent::OnReloadFinished);

	}


	for (auto OneWeaponData : WeaponData)
	{

		auto FireFinishedNotify = AnimUtils::FindNotifyByClass<UFPSFireAnimNotify>(OneWeaponData.ShootAnimMontage);
		if (!FireFinishedNotify) continue;
		FireFinishedNotify->OnNotified.AddUObject(this, &UFPSWeaponComponent::OnFireFinished);

	}

}

void UFPSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetWeaponAttachmentMesh()) return;

	EquipAnimInProgress = false;
}

void UFPSWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetWeaponAttachmentMesh()) return;

	ReloadAnimInProgress = false;

}

void UFPSWeaponComponent::OnFireFinished(USkeletalMeshComponent* MeshComp)
{
	AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetWeaponAttachmentMesh()) return;

	FireAnimInProgress = false;
}



bool UFPSWeaponComponent::FireAnimInProg() const
{
	return FireAnimInProgress;
}

bool UFPSWeaponComponent::ReloadAnimInProg() const
{
	return ReloadAnimInProgress;
}


bool UFPSWeaponComponent::CanFire() const //переопределить в AIWeaponComponent
{
	return CurrentWeapon 
		&& !EquipAnimInProgress 
		&& !ReloadAnimInProgress 
		&& !CurrentWeapon->IsAmmoEmpty() 
		&& !CurrentWeapon->IsClipEmpty(); // в AI компоненте удалить
}

bool UFPSWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UFPSWeaponComponent::CanReload() const
{
	return CurrentWeapon
		&& !EquipAnimInProgress
		&& !ReloadAnimInProgress
		&& CurrentWeapon->CanReload();
}

void UFPSWeaponComponent::StartFire()
{
	if (!CanFire()) return;
	FireAnimInProgress = true;
	CurrentWeapon->StartFire();
	
	PlayAnimMontage(CurrentShotAnimMontage);
}

void UFPSWeaponComponent::StopFire()
{

	if (!CurrentWeapon) return;

	CurrentWeapon->StopFire();
	
	StopAnimMontage(CurrentShotAnimMontage);
	
}

bool UFPSWeaponComponent::IsFiring() const
{
	return CurrentWeapon && CurrentWeapon->IsFiring();
}

void UFPSWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UFPSWeaponComponent::PrevWeapon()
{
	if (!CanEquip()) return;
	CurrentWeaponIndex = 2;
	EquipWeapon(CurrentWeaponIndex);
}

void UFPSWeaponComponent::RifleWeapon()
{
	if (!CanEquip() || CurrentWeaponIndex == 0) return;
	CurrentWeaponIndex = 0;
	EquipWeapon(CurrentWeaponIndex);
}

void UFPSWeaponComponent::RocketWeapon()
{
	if (!CanEquip() || CurrentWeaponIndex == 1) return;
	CurrentWeaponIndex = 1;
	EquipWeapon(CurrentWeaponIndex);
}

void UFPSWeaponComponent::PlazmaWeapon()
{
	if (!CanEquip() || CurrentWeaponIndex == 2) return;
	CurrentWeaponIndex = 2;
	EquipWeapon(CurrentWeaponIndex);
}

void UFPSWeaponComponent::RailWeapon()
{
	if (!CanEquip() || CurrentWeaponIndex == 3) return;
	CurrentWeaponIndex = 3;
	EquipWeapon(CurrentWeaponIndex);
}

void UFPSWeaponComponent::LightningWeapon()
{
	if (!CanEquip() || CurrentWeaponIndex == 4) return;
	CurrentWeaponIndex = 4;
	EquipWeapon(CurrentWeaponIndex);
}

void UFPSWeaponComponent::SetIndexForAnim(int32 AnimWeaponIndex)
{
	CurrentWeaponIndex = AnimWeaponIndex;
}

int32 UFPSWeaponComponent::WeaponIndexForAnim() const
{
	return CurrentWeaponIndex;
}

bool UFPSWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{

	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;

}

bool UFPSWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}

void UFPSWeaponComponent::Reload()
{
	ChangeClip();
}

bool UFPSWeaponComponent::TryToAddAmmo(TSubclassOf<AFPSBaseWeapon> WeaponType, int32 ClipAmount)
{

	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return Weapon->TryToAddAmmo(ClipAmount);
		}
	}
	return false;
}

bool UFPSWeaponComponent::NeedAmmo(TSubclassOf<AFPSBaseWeapon> WeaponType)
{
	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return !Weapon->IsAmmoFull();
		}
	}
	return false;
}

void UFPSWeaponComponent::OnEmptyClip(AFPSBaseWeapon* AmmoEmptyWeapon)
{
	if (!AmmoEmptyWeapon)
	{
		return;
	}

	if (CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for (const auto Weapon : Weapons)
		{
			if (Weapon == AmmoEmptyWeapon)
			{

				Weapon->ChangeClip();
			}
		}
	}
}

void UFPSWeaponComponent::ChangeClip()
{
	if (!CanReload()) return;

	AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
	if (!Character) return;

	Character->OnStopAiming();

	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	
	PlayAnimMontage(CurrentReloadAnimMontage);
	ReloadAnimInProgress = true;



}


