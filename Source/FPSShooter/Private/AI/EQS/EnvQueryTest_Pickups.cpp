// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnvQueryTest_Pickups.h"
#include <EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h>
#include "Pickups/FPSBasePickup.h"

UEnvQueryTest_Pickups::UEnvQueryTest_Pickups(const FObjectInitializer& ObjectInitializer) //
	: Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_Pickups::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const auto DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	const bool WantsBeTakeble = BoolValue.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		
		const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const auto PickupActor = Cast<AFPSBasePickup>(ItemActor);
		if (!PickupActor) continue;

		const auto CouldBeTaken = PickupActor->CouldBeTaken();
		It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakeble);
	}
}
