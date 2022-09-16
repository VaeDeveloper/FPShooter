// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/FPSPowerUpPickup.h"
#include "Components/SphereComponent.h"
#include "Pickups/FPSPowerUpClass.h"
#include "TimerManager.h"


AFPSPowerUpPickup::AFPSPowerUpPickup()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetSphereRadius(75.f);
	RootComponent = SphereComponent;

}


void AFPSPowerUpPickup::BeginPlay()
{
	Super::BeginPlay();
	Respawn();
}

void AFPSPowerUpPickup::Respawn()
{
	if (!PowerUpClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	PowerUpInstance = GetWorld()->SpawnActor<AFPSPowerUpClass>(PowerUpClass, GetTransform(), SpawnParams);
}

void AFPSPowerUpPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (PowerUpInstance)
	{
		PowerUpInstance->ActivatePowerUp();
		PowerUpInstance = nullptr;

		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AFPSPowerUpPickup::Respawn, CooldownDuration);
	}
}



