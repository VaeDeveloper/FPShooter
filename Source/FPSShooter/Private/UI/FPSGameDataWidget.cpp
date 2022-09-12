// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPSGameDataWidget.h"
#include "FPSGameModeBase.h"
#include "Player/FPSPlayerState.h"

int32 UFPSGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetFPSPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UFPSGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetFPSGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UFPSGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetFPSGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UFPSGameDataWidget::GetRoundsSecondsRemaining() const
{
	const auto GameMode = GetFPSGameMode();
	return GameMode ? GameMode->GetRoundSecondRemainig() : 0;
}

int32 UFPSGameDataWidget::GetStartRoundSecondsRemaining() const
{
	const auto GameMode = GetFPSGameMode();
	return GameMode ? GameMode->GetStartRoundTimerRemaining() : 0;
}

AFPSGameModeBase* UFPSGameDataWidget::GetFPSGameMode() const
{
	return GetWorld() ? Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AFPSPlayerState* UFPSGameDataWidget::GetFPSPlayerState() const
{
	return GetOwningPlayer() ? Cast<AFPSPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
