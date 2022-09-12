// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/FPSMenuPlayerController.h"

void AFPSMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
