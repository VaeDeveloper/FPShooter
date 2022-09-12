// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPSPlayerStateWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UFPSPlayerStateWidget::SetPlayerName(const FText& Text)
{
	if (!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void UFPSPlayerStateWidget::SetKills(const FText& Text)
{
	if (!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}

void UFPSPlayerStateWidget::SetDeath(const FText& Text)
{
	if (!DeathTextBlock) return;
	DeathTextBlock->SetText(Text);
}

void UFPSPlayerStateWidget::SetTeam(const FText& Text)
{
	if (!TeamTextBlock) return;
	TeamTextBlock->SetText(Text);
}

void UFPSPlayerStateWidget::SetPlayerIndicatorImageVisible(bool Visible)
{
	if (!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UFPSPlayerStateWidget::SetTeamColor(const FLinearColor& Color)
{
	if (!TeamImage) return;
	TeamImage->SetColorAndOpacity(Color);
}
