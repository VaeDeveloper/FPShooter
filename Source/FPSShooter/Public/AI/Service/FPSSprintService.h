// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FPSSprintService.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API UFPSSprintService : public UBTService
{
	GENERATED_BODY()
	
public:
	UFPSSprintService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Probability = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float WalkSpeed;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
