// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FPSRespawnComponent.h"
#include "FPSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"



UFPSRespawnComponent::UFPSRespawnComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UFPSRespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;

	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UFPSRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

void UFPSRespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));

	}
}




