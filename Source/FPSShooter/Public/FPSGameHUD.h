// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSCoreTypes.h"
#include "FPSGameHUD.generated.h"

class UWidgetAnimation;

UCLASS()
class FPSSHOOTER_API AFPSGameHUD : public AHUD
{
	GENERATED_BODY()

public:

	
	virtual void DrawHUD() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TMap<EFPSMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;

	void OnMatchStateChanged(EFPSMatchState State);
	void DrawCrosshair();
	
};
