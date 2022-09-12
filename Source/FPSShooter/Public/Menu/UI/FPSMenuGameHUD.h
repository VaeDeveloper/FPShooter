// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSMenuGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API AFPSMenuGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;



	virtual void BeginPlay() override;
	
};
