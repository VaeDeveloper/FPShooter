// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Components/TimelineComponent.h"
#include "FPSCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UFPSHealthComponent;
class UTextRenderComponent;
class UFPSWeaponComponent;
class UCameraShakeBase;
class USoundCue;



UENUM()
enum class EWallRunSide : uint8
{
	None,
	Left,
	Right
};

UCLASS()
class FPSSHOOTER_API AFPSCharacter : public ACharacter 
{
	GENERATED_BODY()


public:

	AFPSCharacter(const FObjectInitializer& ObjInit);

	void OnStartAiming();
	void OnStopAiming();


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* HandMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* TPSMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	UFPSHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	UFPSWeaponComponent* WeaponComponent;	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	UTextRenderComponent* ArmorTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpMovement")
	FVector2D LandedDamageVel = FVector2D(900.f, 1200.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpMovement")
	FVector2D DamageLanded = FVector2D(10.f, 100.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FName MaterialColorName = "Paint Color";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WallRun", meta = (UIMin = 0.f, ClampMin = 0.f))
	float MaxWallRunTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WallRun")
	UCurveFloat* CameraTiltCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> OnCroundShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PickUp")
	TSubclassOf<AActor> SpawnActorAfterDeath;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* AimSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* JumpVoiceSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* DeathSound;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraDefaultFOV = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraAimFOV = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomInterpSpeed = 20.f;

	float CameraCurrentFOV = 100.f;
	
	//Aiming
	void SetAiming(bool bNewAiming);

	//Ability
	void ActivateAbility();
	

	virtual void BeginPlay() override;
	virtual void OnDeath();
	


public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	//Run
	void OnStartRunning();
	void OnStopRunning();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;
	
	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsAim() const;

	UFUNCTION(BlueprintCallable, Category = "WallRun")
	bool IsWallRun() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FRotator GetAimOffsets() const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);


	void SetPlayerColor(const FLinearColor& Color);



	FORCEINLINE USkeletalMeshComponent* GetWeaponAttachmentMesh() const { return HandMesh; }

	void LaunchCharacterToRocket(); // Test Function

	bool bWantsToRun = false;

	bool IsMovingForward = false;
	
private:

	// Aim
	
	bool bIsAiming = false;
	
	void OnStartFire();
	
	//Movement
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void Turn(float Amount);
	void LookUp(float Amount);
	
	UFUNCTION()
	void OnCroundLanded(const FHitResult& Hit);
	

	

	// Function Capsule Hit
	UFUNCTION()
	void OnPlayerCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Wall Run
	void StartWallRun(EWallRunSide Side, const FVector& Direction);
	void StopWallRun();
	void UpdateWallRun();
	void GetWallRunSideAndDirections(const FVector& HitNormal, EWallRunSide& OutSide, FVector& OutDirection) const;
	bool IsSurfaceWallRunning(const FVector& SurfaceNormal) const;
	bool AreRequiredKeyDown(EWallRunSide Side) const;

	float ForwardAxis = 0.f;
	float RightAxis = 0.f;
	bool bIsWallRunning = false;


	EWallRunSide CurrentWallRunSide = EWallRunSide::None;
	FVector CurrentWallRunDirection = FVector::ZeroVector;
	FTimerHandle WallRunTimer;

	//Camera Wall Run
	FTimeline CameraTiltTimeline;
	
	UFUNCTION()
	void UpdateCameraTilt(float Value);

	FORCEINLINE void EndCameraTilt() { CameraTiltTimeline.Reverse(); }
	FORCEINLINE void BeginCameraTilt() { CameraTiltTimeline.Play(); }

	//Death
	
	void OnHealthChanged(float Health, float HealthDelta);
	void OnArmorChanged(float Armor, float ArmorDelta);

	




};
