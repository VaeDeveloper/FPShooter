// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_Pickups.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API UEnvQueryTest_Pickups : public UEnvQueryTest
{
	GENERATED_BODY()
public:
	UEnvQueryTest_Pickups(const FObjectInitializer& ObjectInitializer);
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override; 
};
