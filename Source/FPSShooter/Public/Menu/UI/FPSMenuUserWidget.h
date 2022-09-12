// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSCoreTypes.h"
#include "FPSMenuUserWidget.generated.h"



class UButton;
class UHorizontalBox;
class UFPSGameInstance;
class UFPSLevelItemWidget;


UCLASS()
class FPSSHOOTER_API UFPSMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemsBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HideAnimation;

	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
	

private:

	UPROPERTY()
	TArray<UFPSLevelItemWidget*> LevelItemWidgets;

	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	void InitLevelItem();
	void OnLevelSelected(const FLevelData& Data);
	UFPSGameInstance* GetFPSGameInstance() const;
};
