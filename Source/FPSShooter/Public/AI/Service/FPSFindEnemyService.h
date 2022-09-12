// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FPSFindEnemyService.generated.h"


UCLASS()
class FPSSHOOTER_API UFPSFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:

	UFPSFindEnemyService();



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
