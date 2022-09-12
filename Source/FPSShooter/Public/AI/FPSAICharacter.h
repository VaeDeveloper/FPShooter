// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/FPSCharacter.h"
#include "FPSAICharacter.generated.h"


class UBehaviorTree;

UCLASS()
class FPSSHOOTER_API AFPSAICharacter : public AFPSCharacter
{
	GENERATED_BODY()

public:
	AFPSAICharacter(const FObjectInitializer& ObjInit);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BehaviorTree")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void OnDeath() override;
};
