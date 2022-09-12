// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameHUD.h"
#include "Engine/Canvas.h"
#include "Player/FPSCharacter.h"
#include "Blueprint/UserWidget.h"
#include "FPSGameModeBase.h"


void AFPSGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AFPSGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EFPSMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass)); // 
	GameWidgets.Add(EFPSMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EFPSMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChange.AddUObject(this, &AFPSGameHUD::OnMatchStateChanged);
			// Play Animation ??? How Play WidgetAnimation ( как создать  анимацию виджета) как получить ссылку из массива виджетов? 
		}
	}
}



void AFPSGameHUD::OnMatchStateChanged(EFPSMatchState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);

	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}


	//UE_LOG(LogTemp, Warning, TEXT("Match state change: %s"), *UEnum::GetValueAsString(State)); логирование состояния игры
}

void AFPSGameHUD::DrawCrosshair()
{	
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThikness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Red;

	if (&AFPSCharacter::IsAim)
	{
		DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThikness);
		DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThikness);
	}
}
