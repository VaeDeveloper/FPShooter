// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "FPSSpectatorPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;

UCLASS()
class FPSSHOOTER_API AFPSSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	AFPSSpectatorPawn();

	virtual void BeginPlay() override;


protected:
	UPROPERTY(VisibleAnywhere, Category = "StaticMesh")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* CameraComponent;


};
