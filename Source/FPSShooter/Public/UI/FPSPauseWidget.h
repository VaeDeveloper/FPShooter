// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSPauseWidget.generated.h"



class UButton;

UCLASS()
class FPSSHOOTER_API UFPSPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UWidgetAnimation* FadeAnimation;

	void PlayFadeAnimation();
protected:

	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	virtual void NativeOnInitialized() override;


private:
	
	UFUNCTION()
	void OnClearPause();

};
