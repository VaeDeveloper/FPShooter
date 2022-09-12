#pragma once
#include "Player/FPSPlayerState.h"

class FPSUtils
{
public:
	template <typename T>
	static T* GetFPSPlayerComponent(AActor* PlayerPawn)
	{
		
		if (!PlayerPawn) return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);;
	}

	bool static	AreEnemy(AController* Controller1, AController* Controller2)
	{
		if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

		const auto PlayerState1 = Cast<AFPSPlayerState>(Controller1->PlayerState);
		const auto PlayerState2 = Cast<AFPSPlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}

	static FText TextFromInt(int32 Number) { return FText::FromString(FString::FromInt(Number)); }
};






