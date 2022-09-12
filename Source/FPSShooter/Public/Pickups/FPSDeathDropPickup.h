// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSDeathDropPickup.generated.h"

class USoundCue;
class UBoxComponent;

UCLASS()
class FPSSHOOTER_API AFPSDeathDropPickup : public AActor
{
	GENERATED_BODY()
	
public:	

	AFPSDeathDropPickup();

	bool CouldBeTaken() const;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Pickup")
	UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float HealthAmount = 100.0f;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickWasTaken();
	

};
