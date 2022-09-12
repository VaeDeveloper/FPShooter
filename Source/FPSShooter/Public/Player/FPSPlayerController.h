// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSCoreTypes.h"
#include "FPSPlayerController.generated.h"

class UFPSRespawnComponent;

UCLASS()
class FPSSHOOTER_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFPSPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UFPSRespawnComponent* RespawnComponent;
		
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	void OnPauseGame();
	void OnMatchStateChanged(EFPSMatchState State);
};
