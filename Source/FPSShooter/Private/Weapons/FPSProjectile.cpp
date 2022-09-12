// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FPSProjectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FPSCharacter.h"
#include "Weapons/Components/FPSWeaponFXComponent.h"


AFPSProjectile::AFPSProjectile()
{

	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("SphereComponent");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);


	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	WeaponFXComponent = CreateDefaultSubobject<UFPSWeaponFXComponent>("WeaponFXComponent");
}


void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);

	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnProjectileHit);
	SetLifeSpan(LifeSpanProjectile);
}

void AFPSProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	UGameplayStatics::ApplyRadialDamage(GetWorld(), //
		DamageAmount,                               //
		GetActorLocation(),                         //
		DamageRadius,                               //
		UDamageType::StaticClass(),                 //
		{},                                         // Damage GetOwner Character???
		this,                                       //
		GetController(),                            //
		DoFullDamage);                              //

	
	WeaponFXComponent->PlayImpactFX(Hit);
	Destroy();
}

AController* AFPSProjectile::GetController() const 
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;

}

