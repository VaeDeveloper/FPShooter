// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSRespawnComponent.generated.h"

class USoundCue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSSHOOTER_API UFPSRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFPSRespawnComponent();
		
	void Respawn(int32 RespawnTime);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* VoiceSound;

private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;

	void RespawnTimerUpdate();
		
};
