// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "FPSAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API UFPSAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	AActor* GetClosestEnemy() const;
};
