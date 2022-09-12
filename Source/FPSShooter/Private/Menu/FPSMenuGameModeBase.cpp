// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/FPSMenuGameModeBase.h"
#include "Menu/FPSMenuPlayerController.h"
#include "Menu/UI/FPSMenuGameHUD.h"

AFPSMenuGameModeBase::AFPSMenuGameModeBase()
{
	PlayerControllerClass = AFPSMenuPlayerController::StaticClass();
	HUDClass = AFPSMenuGameHUD::StaticClass();
}
