// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayerState.h"

void AFPSPlayerState::LogInfo()
{
	UE_LOG(LogTemp, Warning, TEXT("TEAM ID : %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathNum);
}
