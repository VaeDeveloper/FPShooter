// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FPSCharacterMovementComponent.h"
#include "Player/FPSCharacter.h"

float UFPSCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AFPSCharacter* Player = Cast<AFPSCharacter>(GetPawnOwner());
	
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
