// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSCoreTypes.h"
#include "FPSLevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;


UCLASS()
class FPSSHOOTER_API UFPSLevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnLevelSelectedSignature OnLevelSelected;

	void SetLevelData(const FLevelData& Data);
	FLevelData GetLevelData() const { return LevelData; }

	void SetSelected(bool IsSelected);

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* LevelImage;

	UPROPERTY(meta = (BindWidget))
	UImage* FrameImage;
	

	virtual void NativeOnInitialized() override;

private:
	FLevelData LevelData;


	UFUNCTION()
	void OnLevelItemClicked();
};
