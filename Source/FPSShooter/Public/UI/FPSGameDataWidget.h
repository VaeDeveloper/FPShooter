// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSGameDataWidget.generated.h"

class AFPSGameModeBase;
class AFPSPlayerState;
UCLASS()
class FPSSHOOTER_API UFPSGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundsSecondsRemaining() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetStartRoundSecondsRemaining() const;

private:

	AFPSGameModeBase* GetFPSGameMode() const;
	AFPSPlayerState* GetFPSPlayerState() const;
	
};
