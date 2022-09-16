// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSVideoSettingsWidget.generated.h"

class UVerticalBox;
class UFPSSettingOptionWidget;

UCLASS()
class FPSSHOOTER_API UFPSVideoSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VideoSettingsContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UFPSSettingOptionWidget> SettingOptionWidgetClass;

	virtual void NativeOnInitialized() override;
	
};
