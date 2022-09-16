#pragma once

#include "FPSCoreTypes.generated.h"



//WEAPONS
class AFPSBaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, AFPSBaseWeapon*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLastBulletSignature, AFPSBaseWeapon*);



USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets; // number of bullets

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
	int32 Clips; // number of clips

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite; // Is it infinite ammo???
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AFPSBaseWeapon> WeaponClasses;  // Class of Weapons

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage; // Reload Animation

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ShootAnimMontage; // Fire Animation

};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* MainIcon; // Weapon Icon Texture

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UMaterialInstance* CrosshairIcon; // Crosshair material


};

//HEALTH 

DECLARE_MULTICAST_DELEGATE(FOnDeath); // death delegate
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHeathChange, float, float); // health change delegate
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnArmorChange, float, float); // armor change delegate


class UNiagaraSystem;
class USoundCue;

USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Decal")
	UMaterialInterface* Material;  // Decal material

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Decal")
	FVector Size = FVector(10.f); // the size of decal

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Decal")
	float LifeTime = 5.f;  // lifetime of decal

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Decal")
	float FadeOutTime = 0.7f;  // Fadeout time of decal
};

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Decal")
	UNiagaraSystem* NiagaraEffect; // Impact Effect
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Decal")
	FDecalData DecalData; // Array Impact Decals

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* ImpactSound; // Impact Sound 

};

USTRUCT(BlueprintType)
struct	FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"));
	int32 PlayersNum = 2; // Number of players

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "4"));
	int32 RoundsNum = 4; // Number of rounds

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"));
	int32 RoundTime  = 10; // in seconds	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "10"));
	int32 StartRoundTime = 5; // in seconds	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "10"));
	int32 RespawnTime = 5; // in seconds

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	FLinearColor DefaultTeamColor = FLinearColor::Red; // Default team color

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	TArray<FLinearColor> TeamColors;  // Team Color array

};

UENUM(BlueprintType)
enum class EFPSMatchState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Pause, 
	GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangeSignature, EFPSMatchState);


USTRUCT(BlueprintType)
struct	FLevelData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FName LevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FName LevelDisplayName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	UTexture2D* LevelThumb;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelData&);