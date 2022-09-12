// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSCoreTypes.h"
#include "FPSPlayerHUDWidget.generated.h"


UCLASS()
class FPSSHOOTER_API UFPSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetArmorPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintImplementableEvent , Category = "UI")
	void OnTakeDamage();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

protected:

	virtual void NativeOnInitialized() override;

private:
	void OnHealthChange(float Health, float HealthDelta);
	void OnArmorChange(float Armor, float ArmorDelta);

};
