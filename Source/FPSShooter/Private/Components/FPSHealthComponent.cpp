// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FPSHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "FPSGameModeBase.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"



UFPSHealthComponent::UFPSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFPSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);
	Armor = 0.0f;
	OnArmorChanged.Broadcast(Armor,Armor);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UFPSHealthComponent::OnTakeAnyDamage);
	}
}

void UFPSHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f || IsDead() ||  !GetWorld()) return;

	Armor = FMath::Clamp(Armor - Damage, 0.f, MaxArmor);
	OnArmorChanged.Broadcast(Armor, Armor);

	
	if(Armor <= 0.f)
	{
		SetHealth(Health - Damage);
	
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}


	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
		
	}
	else if (AutoHeal && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UFPSHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
	PlayCameraShake();

	const auto Player = Cast<APawn>(GetOwner());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PainSound, Player->GetActorLocation(), Player->GetActorRotation());
}

void UFPSHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);
	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UFPSHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

void UFPSHealthComponent::SetArmor(float NewArmor)
{
	const auto NextArmor = FMath::Clamp(NewArmor, 0.0f, MaxArmor);
	const auto ArmorDelta = NextArmor - Armor;

	Armor = NextArmor;
	OnArmorChanged.Broadcast(Armor, ArmorDelta);
}

void UFPSHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);

}

void UFPSHealthComponent::Killed(AController* KillerController)
{
	if (!GetWorld()) return;
	const auto GameMode = Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);
}

bool UFPSHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull()) return false;

	SetHealth(Health + HealthAmount);
	return true;
}

bool UFPSHealthComponent::TryToAddArmor(float ArmorAmount)
{
	if (Armor == MaxArmor) return false;

	SetArmor(Armor + ArmorAmount);
	return true;
}

bool UFPSHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}