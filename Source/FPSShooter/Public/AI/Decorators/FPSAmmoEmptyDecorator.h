// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "FPSAmmoEmptyDecorator.generated.h"

class AFPSBaseWeapon;

UCLASS()
class FPSSHOOTER_API UFPSAmmoEmptyDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UFPSAmmoEmptyDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AFPSBaseWeapon> WeaponType;


	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
