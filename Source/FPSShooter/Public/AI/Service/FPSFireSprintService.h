// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FPSFireSprintService.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API UFPSFireSprintService : public UBTService
{
	GENERATED_BODY()

public:
	UFPSFireSprintService();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Speed;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
