// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPSCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API UFPSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.2", ClampMax = "10.0"))
	float RunModifier = 2.f;


	virtual float GetMaxSpeed() const override;

	
};
