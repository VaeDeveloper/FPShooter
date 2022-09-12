// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSCoreTypes.h"
#include "FPSGameModeBase.generated.h"


class AAIController;
class USoundCue;

UCLASS()
class FPSSHOOTER_API AFPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSGameModeBase();

	FOnMatchStateChangeSignature OnMatchStateChange;

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	void Killed(AController* KillerController, AController* VictimController);
	void RespawnRequest(AController* Controller);

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;

	FGameData GetGameData() const { return GameData; }	
	int32 GetCurrentRoundNum() const { return CurrentRound; }
	int32 GetRoundSecondRemainig() const { return RoundCountDown; }
	int32 GetStartRoundTimerRemaining() const { return StartRoundTimerCountDown; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* VoiceSoundTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* FightSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* StartRoundSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* UIStartSound;




private:

	EFPSMatchState MatchState = EFPSMatchState::WaitingToStart;

	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;
	int32 StartRoundTimerCountDown = 0;
	FTimerHandle GameRoundTimerHandle;
	FTimerHandle GameStartRoundTimerHandle;


	void SpawnBots();
	void StartRound();
	void StartRoundCountDown();
	void GameTimerUpdate();
	void GameStartTimerUpdate();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);
	void StartRespawn(AController* Controller);

	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	void LogPlayerInfo();

	void GameOver();  

	void SetMatchState(EFPSMatchState State);

	
};
