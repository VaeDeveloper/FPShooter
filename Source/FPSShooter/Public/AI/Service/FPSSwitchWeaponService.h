// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FPSSwitchWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API UFPSSwitchWeaponService : public UBTService
{
	GENERATED_BODY()
	
public:
	UFPSSwitchWeaponService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Probability = 0.5f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
