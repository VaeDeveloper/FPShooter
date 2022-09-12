// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Components/FPSWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Components/FPSHealthComponent.h"
#include "Sound/SoundCue.h"


UFPSWeaponFXComponent::UFPSWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFPSWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}

	

	//Spawn Niagara (спавн эффектов Ниагары)
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		ImpactData.NiagaraEffect,
		Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());
	
	//Decal
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),//
		              ImpactData.DecalData.Material,  //
		              ImpactData.DecalData.Size,      //
		              Hit.ImpactPoint,                //
		              Hit.ImpactNormal.Rotation());   
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}
	// Sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.ImpactSound, Hit.ImpactPoint);

}




