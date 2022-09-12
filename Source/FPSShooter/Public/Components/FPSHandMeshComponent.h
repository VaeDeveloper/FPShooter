// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPSHandMeshComponent.generated.h"




UCLASS()
class FPSSHOOTER_API UFPSHandMeshComponent : public USkeletalMeshComponent
{
public:
	UPROPERTY(EditAnywhere, Category = Mesh)
	float DesiredHorizontalFov = 77.f;

	GENERATED_BODY()
	

	
	
};
