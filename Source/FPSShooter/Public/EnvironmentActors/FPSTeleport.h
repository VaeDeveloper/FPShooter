// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "FPSTeleport.generated.h"

class USoundCue;

UCLASS()
class FPSSHOOTER_API AFPSTeleport : public ATriggerBox
{
	GENERATED_BODY()
	

public:

	AFPSTeleport();

	UFUNCTION()
	void EnterTeleportBox(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void EndTeleportBox(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere, Category = "Teleport")
	AFPSTeleport* OtherTeleport;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* EnterSound;

	UPROPERTY()
	bool bTeleporting;

protected:


	virtual void BeginPlay() override;


};
