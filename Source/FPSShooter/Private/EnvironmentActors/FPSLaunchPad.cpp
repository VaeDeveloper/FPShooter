// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentActors/FPSLaunchPad.h"
#include "Player/FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


AFPSLaunchPad::AFPSLaunchPad()
{
    OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
    OverlapComponent->SetBoxExtent(FVector(75, 75, 50));
    RootComponent = OverlapComponent;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComponent->SetupAttachment(RootComponent);

    OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OverlapLaunchPad);

    LaunchAngle = 35.0f;
    LaunchStrength = 1500.f;
}

void AFPSLaunchPad::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    FRotator LaunchDirection = GetActorRotation();
    LaunchDirection.Pitch += LaunchAngle;
    FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

    ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
    if (OtherCharacter)
    {
        OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);
        UGameplayStatics::PlaySound2D(GetWorld(), JumpSound);

    }
    else if (OtherComp && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

        //spawn fx
    }
}




