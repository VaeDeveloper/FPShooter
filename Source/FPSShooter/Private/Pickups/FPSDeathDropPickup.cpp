// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/FPSDeathDropPickup.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/FPSHealthComponent.h"
#include "FPSUtils.h"

AFPSDeathDropPickup::AFPSDeathDropPickup()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
	
	
}

bool AFPSDeathDropPickup::CouldBeTaken() const
{
	return false;
}

void AFPSDeathDropPickup::BeginPlay()
{
	Super::BeginPlay();
	FVector Vector = FVector(10.f, 2000000.f, 3000000.f);
	CollisionComponent->AddForce(Vector);
	SetLifeSpan(5.0f);
}

void AFPSDeathDropPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	
	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickWasTaken();
	}
}

bool AFPSDeathDropPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = FPSUtils::GetFPSPlayerComponent<UFPSHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;


	return HealthComponent->TryToAddHealth(HealthAmount);
}

void AFPSDeathDropPickup::PickWasTaken()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		Destroy();
	}
	
}





