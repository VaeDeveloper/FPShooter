// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSPowerUpPickup.generated.h"

class USphereComponent;
class AFPSPowerUpClass;

UCLASS()
class FPSSHOOTER_API AFPSPowerUpPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AFPSPowerUpPickup();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	TSubclassOf<AFPSPowerUpClass> PowerUpClass;

	AFPSPowerUpClass* PowerUpInstance;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	float CooldownDuration;

	FTimerHandle RespawnTimerHandle;

	void Respawn();

	virtual void BeginPlay() override;

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
