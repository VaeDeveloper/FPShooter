// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSSpectatorPawn.h"
#include "Camera/CameraComponent.h"


AFPSSpectatorPawn::AFPSSpectatorPawn()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetSimulatePhysics(true);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(Mesh);
	
}

void AFPSSpectatorPawn::BeginPlay()
{
	Mesh->AddImpulse(FVector(100000.f, 100000.f, 100000.f));
	GetController()->DisableInput(false);
}
