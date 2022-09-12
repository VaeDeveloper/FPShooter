// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UBoxComponent;
class USoundCue;

UCLASS()
class FPSSHOOTER_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AFPSLaunchPad();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* JumpSound;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBoxComponent* OverlapComponent;

	UFUNCTION()
	void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchStrength;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchAngle;

};
