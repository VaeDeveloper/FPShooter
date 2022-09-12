// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSCoreTypes.h"
#include "FPSGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class FPSSHOOTER_API UFPSGameOverWidget : public UUserWidget
{
	GENERATED_BODY()


protected:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStateBox;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStateRowWidgetClass;

	virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChanged(EFPSMatchState State);
	void UpdatePlayersState();

	UFUNCTION()
	void OnResetLevel();
};
