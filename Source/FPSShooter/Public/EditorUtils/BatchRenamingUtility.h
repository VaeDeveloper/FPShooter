// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"

#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundWave.h"
#include "Engine/Texture.h"
#include "Blueprint/UserWidget.h"
#include "Animation/MorphTarget.h"
#include "Components/SkeletalMeshComponent.h"
#include "BatchRenamingUtility.generated.h"




UCLASS()
class FPSSHOOTER_API UBatchRenamingUtility : public UAssetActionUtility
{
	GENERATED_BODY()

public:

	UFUNCTION(CallInEditor)
	void RenameSelectedAssets(FString SearchPattern, FString ReplacePattern, ESearchCase::Type SearchCase);

	UFUNCTION(CallInEditor)
	void AddPrefixes();

	UFUNCTION(CallInEditor)
	void CleanUpFolders(FString ParentFolder = FString("/Game"));

private:

	const TMap<UClass*, FString> PrefixMap = {
		{UBlueprint::StaticClass(), TEXT("BP_")},
		{UStaticMesh::StaticClass(), TEXT("SM_")},
		{UMaterial::StaticClass(), TEXT("M_")},
		{UMaterialInstance::StaticClass(), TEXT("MI_")},
		{UMaterialFunctionInterface::StaticClass(), TEXT("MF_")},
		{UParticleSystem::StaticClass(), TEXT("PS_")},
		{USoundCue::StaticClass(), TEXT("SC_")},
		{USoundWave::StaticClass(), TEXT("S_")},
		{UTexture::StaticClass(), TEXT("T_")},
		{UTexture2D::StaticClass(), TEXT("T_")},
		{UUserWidget::StaticClass(), TEXT("UW_")},
		{UMorphTarget::StaticClass(), TEXT("MT_")},
		{USkeletalMeshComponent::StaticClass(), TEXT("SK_")}
	};

	/**
	* Prints a message to the screen 
	* @param Message - the message to print
	* #param Color - Color message use
	**/
	void PrintToScreen(FString Message, FColor Color);



	/**
	* Prints a message to the screen
	* @param Method - the method that was use
	* #param Counter - How many object were affected  use
	**/
	void GiveFeedback(FString Method, uint32 Counter);
};
