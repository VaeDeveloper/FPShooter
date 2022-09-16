// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameUserSettings.h"
#include "FPSGameSettings.h"

#define BIND_SETTINGS_FUNC(FUNC) \
         [&](int32 Level)        \
         {                       \
	        FUNC(Level);         \
	        ApplySettings(false);\
         }                       \

UFPSGameUserSettings::UFPSGameUserSettings()
{
	const TArray<FSettingOption> VFXOptions = { {"Low", 0}, {"Medium", 1}, {"High", 2}, {"Epic", 3} };
	{
		auto* Setting = NewObject<UFPSGameSettings>();
		check(Setting);
		Setting->SetName("Anti-Aliasing");
		Setting->SetOption(VFXOptions);
		Setting->AddGetter([&]() {return GetAntiAliasingQuality(); });
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetAntiAliasingQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<UFPSGameSettings>();
		check(Setting);
		Setting->SetName("Textures");
		Setting->SetOption(VFXOptions);
		Setting->AddGetter([&]() {return GetTextureQuality(); });
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetTextureQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<UFPSGameSettings>();
		check(Setting);
		Setting->SetName("Shadows");
		Setting->SetOption(VFXOptions);
		Setting->AddGetter([&]() {return GetShadowQuality(); });
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetShadowQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<UFPSGameSettings>();
		check(Setting);
		Setting->SetName("Post Processing");
		Setting->SetOption(VFXOptions);
		Setting->AddGetter([&]() {return GetPostProcessingQuality(); });
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetPostProcessingQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<UFPSGameSettings>();
		check(Setting);
		Setting->SetName("Effects");
		Setting->SetOption(VFXOptions);
		Setting->AddGetter([&]() {return GetVisualEffectQuality(); });
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetVisualEffectQuality));
		VideoSettings.Add(Setting);
	}


}

UFPSGameUserSettings* UFPSGameUserSettings::Get()
{
	return GEngine ? Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

const TArray<UFPSGameSettings*>& UFPSGameUserSettings::GetVideoSettings() const
{
	return VideoSettings;
}
