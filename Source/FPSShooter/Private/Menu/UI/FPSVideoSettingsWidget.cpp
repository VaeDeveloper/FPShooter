// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/FPSVideoSettingsWidget.h"
#include "FPSGameUserSettings.h"
#include "Components/VerticalBox.h"
#include "Menu/UI/FPSSettingOptionWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogVideoSettings, All, All);


void UFPSVideoSettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto* UserSettings = UFPSGameUserSettings::Get();
	if (!UserSettings)
	{
		UE_LOG(LogVideoSettings, Error, TEXT("Error gameusersettings is nullptr"));
		return;
	}

	UserSettings->LoadSettings();
	const auto VideoSettings = UserSettings->GetVideoSettings();

	check(VideoSettingsContainer);
	VideoSettingsContainer->ClearChildren();


	for (auto* Setting: VideoSettings)
	{
		const auto SettingWidget = CreateWidget<UFPSSettingOptionWidget>(this, SettingOptionWidgetClass);
		check(SettingWidget);
 		SettingWidget->Init(Setting);
		VideoSettingsContainer->AddChild(SettingWidget);
	}

}
