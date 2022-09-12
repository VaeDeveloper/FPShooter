// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPSGameOverWidget.h"
#include "FPSGameModeBase.h"
#include "Player/FPSPlayerState.h"
#include "UI/FPSPlayerStateWidget.h"
#include "Components/VerticalBox.h"
#include "FPSUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UFPSGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetWorld())
	{
		const auto GameMode = Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChange.AddUObject(this, &UFPSGameOverWidget::OnMatchStateChanged);
		}
	}
	if (ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &UFPSGameOverWidget::OnResetLevel);
	}
	
}

void UFPSGameOverWidget::OnMatchStateChanged(EFPSMatchState State)
{
	if (State == EFPSMatchState::GameOver)
	{
		UpdatePlayersState();
	}
}

void UFPSGameOverWidget::UpdatePlayersState()
{
	if (!GetWorld() || !PlayerStateBox) return;

	PlayerStateBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;
		
		const auto PlayerState = Cast<AFPSPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		const auto PlayerStateRowWidget = CreateWidget<UFPSPlayerStateWidget>(GetWorld(), PlayerStateRowWidgetClass);
		if (!PlayerStateRowWidget) continue;

		PlayerStateRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStateRowWidget->SetKills(FPSUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStateRowWidget->SetDeath(FPSUtils::TextFromInt(PlayerState->GetDeathNum()));
		PlayerStateRowWidget->SetTeam(FPSUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStateRowWidget->SetPlayerIndicatorImageVisible(Controller->IsPlayerController());
		PlayerStateRowWidget->SetTeamColor(PlayerState->GetTeamColor());

		PlayerStateBox->AddChild(PlayerStateRowWidget);


	}
}

void UFPSGameOverWidget::OnResetLevel()
{
	//const FName CurrentLevelName = "TestMap"; // Hard Code
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);

	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName)); // Hard Reset Level //


}
