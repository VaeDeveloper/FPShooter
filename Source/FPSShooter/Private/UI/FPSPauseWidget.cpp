// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPSPauseWidget.h"
#include <GameframeWork/GameModeBase.h>
#include <Components/Button.h>

void UFPSPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UFPSPauseWidget::OnClearPause);
	}

}

void UFPSPauseWidget::PlayFadeAnimation()
{
	this->PlayAnimation(FadeAnimation);
}

void UFPSPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
