// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/FPSBasePickup.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


AFPSBasePickup::AFPSBasePickup()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);

}

bool AFPSBasePickup::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
	
}


void AFPSBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	


	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickWasTaken();
	}
	
}



bool AFPSBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void AFPSBasePickup::PickWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AFPSBasePickup::Respawn,RespawnTime);
}

void AFPSBasePickup::Respawn()
{
	// SoundFX

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

