// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "FPSHealthPercentDecorator.generated.h"


UCLASS()
class FPSSHOOTER_API UFPSHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()
	

public:
	UFPSHealthPercentDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.6f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
