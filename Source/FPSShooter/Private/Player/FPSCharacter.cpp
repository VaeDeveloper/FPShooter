// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSCharacter.h"
#include "Player/FPSPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/FPSCharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/FPSHandMeshComponent.h"
#include "Components/FPSHealthComponent.h"
#include "Components/FPSWeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/FPSHealthPickup.h"
#include "Sound/SoundCue.h"



DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);



AFPSCharacter::AFPSCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UFPSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	CameraComponent->SetFieldOfView(CameraCurrentFOV);



	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	HandMesh->SetupAttachment(CameraComponent);
	HandMesh->CastShadow = false;
	HandMesh->bCastDynamicShadow = false;
	


	TPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TPSMesh"));
	TPSMesh->SetupAttachment(CameraComponent);
	TPSMesh->CastShadow = false;
	TPSMesh->bCastDynamicShadow = false;
	TPSMesh->bOwnerNoSee = true;

	HealthComponent = CreateDefaultSubobject<UFPSHealthComponent>(TEXT("Health Component"));
	WeaponComponent = CreateDefaultSubobject<UFPSWeaponComponent>(TEXT("WeaponComponent"));

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->bOwnerNoSee = true;
	HealthTextComponent->SetupAttachment(CameraComponent);


	ArmorTextComponent = CreateDefaultSubobject<UTextRenderComponent>("ArmorTextComponent");
	ArmorTextComponent->bOwnerNoSee = true;
	ArmorTextComponent->SetupAttachment(CameraComponent);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");

	JumpMaxHoldTime = 0.0f;
	JumpMaxCount = 2;
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(HealthTextComponent);

	AquireAbility(Ability);

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AFPSCharacter::OnPlayerCapsuleHit);
	GetCharacterMovement()->SetPlaneConstraintEnabled(true);

	OnHealthChanged(HealthComponent->GetHeath(), 0.0f);
	OnArmorChanged(HealthComponent->GetArmor(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &AFPSCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AFPSCharacter::OnHealthChanged);
	HealthComponent->OnArmorChanged.AddUObject(this, &AFPSCharacter::OnArmorChanged);

	if (IsValid(CameraTiltCurve))
	{
		FOnTimelineFloat TimelineCallBack;
		TimelineCallBack.BindUFunction(this, FName("UpdateCameraTilt"));
		CameraTiltTimeline.AddInterpFloat(CameraTiltCurve, TimelineCallBack);
	}
	
	LandedDelegate.AddDynamic(this, &AFPSCharacter::OnCroundLanded);

}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	

	if (bIsWallRunning)
	{
		UpdateWallRun();
	}
	CameraTiltTimeline.TickTimeline(DeltaTime);

	if (bIsAiming)
	{
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraAimFOV, DeltaTime, ZoomInterpSpeed);
		
	}	
	else
	{
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraDefaultFOV, DeltaTime, ZoomInterpSpeed);
		
	}
	CameraComponent->SetFieldOfView(CameraCurrentFOV);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement Input 
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::LookUp);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJumping);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AFPSCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AFPSCharacter::OnStopRunning);

	// Shooting Input
	PlayerInputComponent->BindAction("Aiming", IE_Pressed, this, &AFPSCharacter::OnStartAiming);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &AFPSCharacter::OnStopAiming);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnStartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UFPSWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UFPSWeaponComponent::Reload);


	//Switch Weapon Input
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UFPSWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("PrevWeapon", IE_Pressed, WeaponComponent, &UFPSWeaponComponent::PrevWeapon);
	PlayerInputComponent->BindAction("RifleWeapon", IE_Pressed, WeaponComponent, &UFPSWeaponComponent::RifleWeapon);
	PlayerInputComponent->BindAction("RocketWeapon", IE_Pressed, WeaponComponent, &UFPSWeaponComponent::RocketWeapon);
	PlayerInputComponent->BindAction("PlazmaWeapon", IE_Pressed, WeaponComponent, &UFPSWeaponComponent::PlazmaWeapon);
	PlayerInputComponent->BindAction("RailGun", IE_Pressed, WeaponComponent, &UFPSWeaponComponent::RailWeapon);
	PlayerInputComponent->BindAction("LightningWeapon", IE_Pressed, WeaponComponent, &UFPSWeaponComponent::LightningWeapon);

	//Ability
	PlayerInputComponent->BindAction("Ability", IE_Pressed, this, &AFPSCharacter::ActivateAbility);

}


// Movement Function 
void AFPSCharacter::Jump()
{
	GetCharacterMovement()->AirControl = 0.2f;
	if (bIsWallRunning)
	{
		FVector JumpDirection = FVector::ZeroVector;
		if (CurrentWallRunSide == EWallRunSide::None)
		{
			//UE_LOG(LogTemp, Warning, TEXT("UP"));
		}

		if (CurrentWallRunSide == EWallRunSide::Right)
		{
			JumpDirection = FVector::CrossProduct(CurrentWallRunDirection, FVector::UpVector).GetSafeNormal();
			//UE_LOG(LogTemp, Warning, TEXT("Left"));
		}
		else
		{
			JumpDirection = FVector::CrossProduct(FVector::UpVector, CurrentWallRunDirection).GetSafeNormal();
			//UE_LOG(LogTemp, Warning, TEXT("Right"));
		}
		JumpDirection += FVector::UpVector;
		LaunchCharacter(GetCharacterMovement()->JumpZVelocity * JumpDirection.GetSafeNormal(),false, true);
		
		StopWallRun();
	}
	else
	{
		Super::Jump();
		if (JumpCurrentCount == 1)
		{
			
			GetCharacterMovement()->AirControl = 0.2f;
			LaunchCharacter(GetActorForwardVector() * 1500, true, false);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), JumpVoiceSound, GetActorLocation());
		}
	}
}

void AFPSCharacter::MoveForward(float Amount)
{
	ForwardAxis = Amount;
	IsMovingForward = Amount > 0.f;
	AddMovementInput(GetActorForwardVector(), Amount);

	if (IsRunning() && WeaponComponent->IsFiring())
	{
		WeaponComponent->StopFire();
	}
}

void AFPSCharacter::MoveRight(float Amount)
{
	RightAxis = Amount;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AFPSCharacter::Turn(float Amount)
{
	AddControllerYawInput(Amount);
}

void AFPSCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
	
}

void AFPSCharacter::OnCroundLanded(const FHitResult& Hit)
{
	
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
	//UE_LOG(LogTemp, Warning, TEXT("FallVelocity: %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVel.X) return;

	if (FallVelocityZ > 900.f)
	{
		
	}
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVel, DamageLanded, -FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
	const auto PlayerController = Cast<AFPSPlayerController>(GetController());

}

void AFPSCharacter::OnStartRunning()
{
	bWantsToRun = true;
	OnStopAiming();
	if (IsRunning())
	{
		WeaponComponent->StopFire();
	}
}

void AFPSCharacter::OnStopRunning()
{
	bWantsToRun = false;
}

bool AFPSCharacter::IsRunning() const
{	
	
	return bWantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float AFPSCharacter::GetMovementDirection() const  // Calculate Movement Direction
{
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto	CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

FRotator AFPSCharacter::GetAimOffsets() const
{
	const FVector AimDirectionWS = GetBaseAimRotation().Vector();
	const FVector AimDirectionLS = ActorToWorld().InverseTransformVectorNoScale(AimDirectionWS);
	const FRotator AimRotLS = AimDirectionLS.Rotation();

	return AimRotLS;
	
}



void AFPSCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInstance = GetWeaponAttachmentMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInstance) return;

	MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);

}

//Ability
void AFPSCharacter::ActivateAbility()
{
	//UE_LOG(LogTemp, Warning, TEXT("Ability Activate"));
	GetAbilitySystemComponent()->TryActivateAbilityByClass(Ability);
}

void AFPSCharacter::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
{
	if (AbilitySystemComponent)
	{
		if (HasAuthority() && AbilityToAquire)
		{
			FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
			SpecDef.Ability = AbilityToAquire;
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(SpecDef, 1);
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent* AFPSCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}



// WALL Running Functions 
void AFPSCharacter::OnPlayerCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	FVector HitNormal = Hit.ImpactNormal;

	if (bIsWallRunning) return;
	
	if (!IsSurfaceWallRunning(HitNormal)) return;

	if (!GetCharacterMovement()->IsFalling()) return;

	

	EWallRunSide Side = EWallRunSide::None;
	FVector Direction = FVector::ZeroVector;
	GetWallRunSideAndDirections(HitNormal, Side, Direction);
	
	if (!AreRequiredKeyDown(Side))
	{
		return;
	}
	
	StartWallRun(Side, Direction);

}

void AFPSCharacter::GetWallRunSideAndDirections(const FVector& HitNormal, EWallRunSide& OutSide, FVector& OutDirection) const 
{	
	if (FVector::DotProduct(HitNormal, GetActorUpVector()) == 0)
	{
		OutSide = EWallRunSide::None;
		OutDirection = FVector::CrossProduct(HitNormal, FVector::UpVector).GetSafeNormal();
		
	}
	if (FVector::DotProduct(HitNormal, GetActorRightVector()) > 0)
	{
		OutSide = EWallRunSide::Left;
		OutDirection = FVector::CrossProduct(HitNormal, FVector::UpVector).GetSafeNormal();
	
	}
	else
	{
		OutSide = EWallRunSide::Right;
		OutDirection = FVector::CrossProduct(FVector::UpVector, HitNormal).GetSafeNormal();

	}
}

bool AFPSCharacter::IsSurfaceWallRunning(const FVector& SurfaceNormal) const
{
	if (SurfaceNormal.Z > GetCharacterMovement()->GetWalkableFloorZ() || SurfaceNormal.Z < -0.005f)
	{
		return false;
	}
	return true;
}

bool AFPSCharacter::AreRequiredKeyDown(EWallRunSide Side) const
{
	if (ForwardAxis < 0.1f)
	{
		return false;
	}
	if (Side == EWallRunSide::Right && RightAxis < -0.1f)
	{
		return false;
	}
	if (Side == EWallRunSide::Left && RightAxis > 0.1f)
	{
		return false;
	}

	return true;

}

void AFPSCharacter::StartWallRun(EWallRunSide Side, const FVector& Direction)
{
	BeginCameraTilt();
	bIsWallRunning = true;

	CurrentWallRunSide = Side;
	CurrentWallRunDirection = Direction;

	GetCharacterMovement()->SetPlaneConstraintNormal(FVector::UpVector);

	GetWorld()->GetTimerManager().SetTimer(WallRunTimer, this, &AFPSCharacter::StopWallRun, MaxWallRunTime, false);

}

void AFPSCharacter::StopWallRun()
{
	EndCameraTilt();
	bIsWallRunning = false;

	GetCharacterMovement()->SetPlaneConstraintNormal(FVector::ZeroVector);
}

void AFPSCharacter::UpdateWallRun()
{

	if (!AreRequiredKeyDown(CurrentWallRunSide))
	{
		StopWallRun();
		return;
	} 
	FHitResult HitResult;
	

	FVector LineTraceDirection = CurrentWallRunSide == EWallRunSide::Right ? GetActorRightVector() : -GetActorRightVector();
	float LineTraceLength = 150.f;

	FVector StartPosition = GetActorLocation();
	FVector EndPosition = StartPosition + LineTraceLength * LineTraceDirection;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_Visibility, QueryParams))
	{
		
		EWallRunSide Side = EWallRunSide::None;
		FVector Direction = FVector::ZeroVector;
		GetWallRunSideAndDirections(HitResult.ImpactNormal, Side, Direction);

		if (Side != CurrentWallRunSide)
		{
			StopWallRun();
		}
		else
		{
			CurrentWallRunDirection = Direction;
			GetCharacterMovement()->Velocity = GetCharacterMovement()->GetMaxSpeed() * CurrentWallRunDirection;

		}
	}
	else
	{
		StopWallRun();
	}

}

void AFPSCharacter::UpdateCameraTilt(float Value)
{
	FRotator CurrentControlRotation = GetControlRotation();
	CurrentControlRotation.Roll = CurrentWallRunSide == EWallRunSide::Left ? Value : -Value;
	GetController()->SetControlRotation(CurrentControlRotation);


}

bool AFPSCharacter::IsWallRun() const
{
	return bIsWallRunning;
}



//Shooting Function 
void AFPSCharacter::SetAiming(bool bNewAiming)
{
	bIsAiming = bNewAiming;
}

bool AFPSCharacter::IsAim() const
{
	return bIsAiming;
}

void AFPSCharacter::OnStartAiming()
{
	SetAiming(true);
	bWantsToRun = false;


	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AimSound, GetActorLocation(), GetActorRotation());
}

void AFPSCharacter::OnStopAiming()
{
	SetAiming(false);
}

void AFPSCharacter::OnStartFire()
{		
	
	bWantsToRun = false;
	WeaponComponent->StartFire();
}







// Health Function
void AFPSCharacter::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT(" Player %s is Dead: "), *GetName());
	TPSMesh->SetSimulatePhysics(true);
	
	GetCharacterMovement()->DisableMovement();
	//SetLifeSpan(0.1f);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation(), GetActorRotation());
	GetWorld()->SpawnActor<AActor>(SpawnActorAfterDeath, GetActorLocation(), GetActorRotation());
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();
	Destroy();
}



void AFPSCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void AFPSCharacter::OnArmorChanged(float Armor, float ArmorDelta)
{
	ArmorTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Armor)));
}

// TEST Function

void AFPSCharacter::LaunchCharacterToRocket()
{	
	FVector LaunchVector = FVector(0.0f, 0.0f, 1000.0f);
	AFPSCharacter::LaunchCharacter(LaunchVector, false, true);
}


