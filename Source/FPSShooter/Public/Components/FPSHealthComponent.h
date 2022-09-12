// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSCoreTypes.h"
#include "FPSHealthComponent.generated.h"

class UCameraShakeBase;
class USoundCue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSSHOOTER_API UFPSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFPSHealthComponent();

	float GetHeath() const { return Health; }
	float GetArmor() const { return Armor; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }



	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const { return Health / MaxHealth; } 

	UFUNCTION(BlueprintCallable)
	float GetArmorPercent() const { return Armor / MaxArmor; }


	FOnDeath OnDeath;
	FOnHeathChange OnHealthChanged;
	FOnArmorChange OnArmorChanged;

	bool TryToAddHealth(float HealthAmount);
	bool TryToAddArmor(float ArmorAmount);
	bool IsHealthFull() const;
	

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = 0.f, ClampMax = 100.f))
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = 0.f, ClampMax = 100.f))
	float MaxArmor = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float HealUpdateTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float HealDelay = 3.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float HealModifier = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float Health = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SoundFX")
	USoundCue* PainSound;

	



private:

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void HealUpdate();
	void SetHealth(float NewHealth);
	void SetArmor(float NewArmor);



	float Armor = 0.f;
	
	FTimerHandle HealTimerHandle;

	void PlayCameraShake();

	void Killed(AController* KillerController);
		
};
