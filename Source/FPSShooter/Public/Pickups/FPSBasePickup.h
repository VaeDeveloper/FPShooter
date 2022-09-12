// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class FPSSHOOTER_API AFPSBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AFPSBasePickup();

	bool CouldBeTaken() const;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float RespawnTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* PickupSound;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:

	FTimerHandle RespawnTimerHandle;

	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickWasTaken();
	void Respawn();

};
