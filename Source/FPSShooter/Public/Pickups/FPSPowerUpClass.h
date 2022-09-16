// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSPowerUpClass.generated.h"

UCLASS()
class FPSSHOOTER_API AFPSPowerUpClass : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AFPSPowerUpClass();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
	float PowerUpInterval;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
	int32 TotalNrOfTicks;

	FTimerHandle PowerTick;

	int32 TicksProcessed;

	UFUNCTION()
	void OnTickPowerUp();


public:	

	void ActivatePowerUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUp")
	void OnActivatePowerUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUp")
	void OnPowerupTicked();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUp")
	void OnExpired();

};
