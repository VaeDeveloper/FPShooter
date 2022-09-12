// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FPSCharacter.h"
#include "Player/FPSPlayerController.h"
#include "FPSGameHUD.h"
#include "AIController.h"
#include "FPSUtils.h"
#include "Components/FPSRespawnComponent.h"
#include "Player/FPSPlayerState.h"
#include "EngineUtils.h"
#include "Sound/SoundCue.h"


AFPSGameModeBase::AFPSGameModeBase()
{
	DefaultPawnClass = AFPSCharacter::StaticClass();
	PlayerControllerClass = AFPSPlayerController::StaticClass();
	HUDClass = AFPSGameHUD::StaticClass();
	PlayerStateClass = AFPSPlayerState::StaticClass();
}

void AFPSGameModeBase::StartPlay()
{
	Super::StartPlay();

	
	
	
	CurrentRound = 1;

	
	UGameplayStatics::PlaySound2D(GetWorld(), UIStartSound);
	UGameplayStatics::PlaySound2D(GetWorld(), StartRoundSound);
	UGameplayStatics::PlaySound2D(GetWorld(), VoiceSoundTimer);
	StartRoundCountDown();
	SetMatchState(EFPSMatchState::InProgress);
	
}

UClass* AFPSGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);	
}

void AFPSGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	UE_LOG(LogTemp, Warning, TEXT("DEAth"));
	const auto KillerPlayerState = KillerController ? Cast<AFPSPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState= VictimController ? Cast<AFPSPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();

		//UGameplayStatics::PlaySound2D(GetWorld(), FragSound);
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
		//UGameplayStatics::PlaySound2D(GetWorld(), FragSound);

	}
	StartRespawn(VictimController);
}

void AFPSGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

bool AFPSGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{

	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if (PauseSet)
	{
		SetMatchState(EFPSMatchState::Pause);
	}
	
	return PauseSet;
}

bool AFPSGameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetMatchState(EFPSMatchState::InProgress);
	}
	return PauseCleared;
}

void AFPSGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;
	
	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		const auto FPSAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(FPSAIController);
	}
}

void AFPSGameModeBase::StartRound()
{
	SpawnBots();
	CreateTeamsInfo();
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AFPSGameModeBase::GameTimerUpdate, 1.0f, true);
	UGameplayStatics::PlaySound2D(GetWorld(), FightSound);
}

void AFPSGameModeBase::StartRoundCountDown()
{
	StartRoundTimerCountDown = GameData.StartRoundTime;
	GetWorldTimerManager().SetTimer(GameStartRoundTimerHandle, this, &AFPSGameModeBase::GameStartTimerUpdate, 1.0f, true);
}

void AFPSGameModeBase::GameTimerUpdate()
{
	//UE_LOG(LogTemp, Error, TEXT("Timer; %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum); //timer & round log 

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
			
		}
	}
}

void AFPSGameModeBase::GameStartTimerUpdate()
{
	
	if (--StartRoundTimerCountDown == 0)
	{			
		GetWorldTimerManager().ClearTimer(GameStartRoundTimerHandle);
		StartRound();
			
	}
	
}

void AFPSGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void AFPSGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();

	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
	
}

void AFPSGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnComponent = FPSUtils::GetFPSPlayerComponent<UFPSRespawnComponent>(Controller);
	if (!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTime);
}

void AFPSGameModeBase::CreateTeamsInfo()
{ 
	if (!GetWorld()) return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AFPSPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
		SetPlayerColor(Controller);
		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor AFPSGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	return GameData.DefaultTeamColor;
}

void AFPSGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<AFPSCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<AFPSPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AFPSGameModeBase::LogPlayerInfo()
{
	if (!GetWorld()) return;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AFPSPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo();
	}
	
}

void AFPSGameModeBase::GameOver()
{
	LogPlayerInfo();// Log statistics player and bots
	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
			
		}
	}
	SetMatchState(EFPSMatchState::GameOver);
}

void AFPSGameModeBase::SetMatchState(EFPSMatchState State)
{
	if (MatchState == State) return;

	MatchState = State;
	OnMatchStateChange.Broadcast(MatchState);

}
