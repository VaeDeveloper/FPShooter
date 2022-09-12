// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIController.generated.h"

class UFPSAIPerceptionComponent;
class UFPSRespawnComponent;

UCLASS()
class FPSSHOOTER_API AFPSAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFPSAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UFPSAIPerceptionComponent* FPSAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UFPSRespawnComponent* RespawnComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;

	
	
};
