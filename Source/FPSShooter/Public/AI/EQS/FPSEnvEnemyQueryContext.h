// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "FPSEnvEnemyQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API UFPSEnvEnemyQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName EnemyActorKeyName = "EnemyActor";


};
