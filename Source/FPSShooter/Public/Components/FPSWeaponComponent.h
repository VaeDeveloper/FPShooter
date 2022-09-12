// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSCoreTypes.h"
#include "FPSWeaponComponent.generated.h"

class AFPSBaseWeapon;




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSSHOOTER_API UFPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFPSWeaponComponent();

	virtual void StartFire();
	void StopFire();
	bool IsFiring() const;
	void Reload();

	//Switch Weapon
	virtual void NextWeapon();
	void PrevWeapon();
	void RifleWeapon();
	void RocketWeapon();
	void PlazmaWeapon();
	void RailWeapon();
	void LightningWeapon();

	void SetIndexForAnim(int32 AnimWeaponIndex);
	bool FireAnimInProg(bool InProgress);

	UFUNCTION(BlueprintCallable)
	int32 WeaponIndexForAnim() const;

	int32 CurrentWeaponIndex = 0;

	// UI
	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<AFPSBaseWeapon> WeaponType, int32 ClipAmount);
	bool NeedAmmo(TSubclassOf<AFPSBaseWeapon> WeaponType);


protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool CanFire() const;
	bool CanEquip() const;


	void EquipWeapon(int32 WeaponIndex);

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* FireAnimMontage;

	UPROPERTY()
	AFPSBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<AFPSBaseWeapon*> Weapons;

private:
	

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	UPROPERTY()
	UAnimMontage* CurrentShotAnimMontage = nullptr;
	
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;
	bool FireAnimInProgress = false;

	void SpawnWeapons();
	void AttachWeaponToSocket(AFPSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	

	float PlayAnimMontage(UAnimMontage* Animation);
	void StopAnimMontage(UAnimMontage* Animation);

	void InitAnimation();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);
	void OnFireFinished(USkeletalMeshComponent* MeshComp);

	bool CanReload() const;

	
	void ChangeClip();
	void OnEmptyClip(AFPSBaseWeapon* AmmoEmptyWeapon);


public:
	
		
	
};
