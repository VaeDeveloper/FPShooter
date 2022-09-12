// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentActors/FPSTeleport.h"
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundCue.h>

AFPSTeleport::AFPSTeleport()
{
	OnActorBeginOverlap.AddDynamic(this, &AFPSTeleport::EnterTeleportBox);
	OnActorEndOverlap.AddDynamic(this, &AFPSTeleport::EndTeleportBox);
	bTeleporting = false;
}

void AFPSTeleport::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSTeleport::EnterTeleportBox(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherTeleport)
		{
			ACharacter* Character = Cast<ACharacter>(OtherActor);
			if (Character && !OtherTeleport->bTeleporting)
			{
				bTeleporting = true;
				Character->SetActorRotation(OtherTeleport->GetActorRotation());
				Character->GetController()->SetControlRotation(Character->GetActorRotation());
				Character->SetActorLocation(OtherTeleport->GetActorLocation());

				//Play Sound
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), EnterSound, GetActorLocation());
			}
		}
	}
}

void AFPSTeleport::EndTeleportBox(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherTeleport && !bTeleporting)
		{
			OtherTeleport->bTeleporting = false;
		}
	}
}


