// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayerController.h"
#include "Components/FPSRespawnComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameModeBase.h"


AFPSPlayerController::AFPSPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UFPSRespawnComponent>("RespawnComponent");
}

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	if (GetWorld())
	{
		const auto GameMode = Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChange.AddUObject(this, &AFPSPlayerController::OnMatchStateChanged);
		}

		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(2.f, 0.f, 5.f, FLinearColor::Black, false, false);
	}
}

void AFPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &AFPSPlayerController::OnPauseGame);
}

void AFPSPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AFPSPlayerController::OnMatchStateChanged(EFPSMatchState State)
{
	if (State == EFPSMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}
