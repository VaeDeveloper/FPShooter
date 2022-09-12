// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

class UCapsuleComponent;
class UProjectileMovementComponent;
class UFPSWeaponFXComponent;

UCLASS()
class FPSSHOOTER_API AFPSProjectile : public AActor
{
	GENERATED_BODY()

public:

	AFPSProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float DamageRadius = 200.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float DamageAmount = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float LifeSpanProjectile = 5.f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UFPSWeaponFXComponent* WeaponFXComponent;


private:

	FVector ShotDirection;

	UFUNCTION()
		void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;



};
