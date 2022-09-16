// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "FPSGameUserSettings.generated.h"


class UFPSGameSettings;


UCLASS()
class FPSSHOOTER_API UFPSGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UFPSGameUserSettings();

	static UFPSGameUserSettings* Get();

	const TArray<UFPSGameSettings*>& GetVideoSettings() const;

private:
	UPROPERTY()
	TArray<UFPSGameSettings*> VideoSettings;
	
};
