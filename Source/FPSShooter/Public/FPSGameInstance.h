// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPSCoreTypes.h"
#include "FPSGameInstance.generated.h"



UCLASS()
class FPSSHOOTER_API UFPSGameInstance : public UGameInstance
{
	GENERATED_BODY()



public:

	FLevelData GetStartupLevel() const { return StartupLevel; }
	void SetStartupLevel(const FLevelData& Data) { StartupLevel = Data; }

	TArray<FLevelData> GetLevelData() const { return LevelsData; }

	FName GetMenuLevelName() const { return MenuLevelName; }


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TArray<FLevelData> LevelsData;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;

private:

	FLevelData StartupLevel;
};
