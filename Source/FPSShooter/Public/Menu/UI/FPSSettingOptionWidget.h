// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSSettingOptionWidget.generated.h"

class UTextBlock;
class UFPSGameSettings;
class UButton;

UCLASS()
class FPSSHOOTER_API UFPSSettingOptionWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SettingDisplayName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SettingCurrentValue;

	UPROPERTY(meta = (BindWidget))
	UButton* NextSettingButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PrevSettingButton;

	virtual void NativeOnInitialized() override;


private:

	TWeakObjectPtr<UFPSGameSettings> Setting;

	void Init(UFPSGameSettings* Setting);
	void UpdateTexts();

	UFUNCTION()
	void OnNextSetting();

	UFUNCTION()
	void OnPrevSetting();

	friend class UFPSVideoSettingsWidget;

};
