// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/FPSMenuUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/FPSLevelItemWidget.h"

void UFPSMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UFPSMenuUserWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UFPSMenuUserWidget::OnQuitGame);
	}

	InitLevelItem();
}






void UFPSMenuUserWidget::InitLevelItem()
{
	const auto FPSGameInstance = GetFPSGameInstance();
	if (!FPSGameInstance) return;

	checkf(FPSGameInstance->GetLevelData().Num() != 0, TEXT("Level data must not be empty"));

	if (!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

	for (auto LevelData : FPSGameInstance->GetLevelData())
	{
		const auto LevelItemWidget = CreateWidget<UFPSLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
		if (!LevelItemWidget) continue;

		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this, &UFPSMenuUserWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}

	if (FPSGameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(FPSGameInstance->GetLevelData()[0]);
	}
	else
	{
		OnLevelSelected(FPSGameInstance->GetStartupLevel());
	}
}

void UFPSMenuUserWidget::OnLevelSelected(const FLevelData& Data)
{
	
	const auto FPSGameInstance = GetFPSGameInstance();
	if (!FPSGameInstance) return;

	FPSGameInstance->SetStartupLevel(Data);

	for (auto LevelItemWidget : LevelItemWidgets)
	{
		if (LevelItemWidget)
		{	
			
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

void UFPSMenuUserWidget::OnStartGame()
{
	PlayAnimation(HideAnimation);
	
}

void UFPSMenuUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation != HideAnimation) return;

	const auto FPSGameInstance = GetFPSGameInstance();
	if (!FPSGameInstance) return;

	UGameplayStatics::OpenLevel(this, FPSGameInstance->GetStartupLevel().LevelName);
}

void UFPSMenuUserWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

UFPSGameInstance* UFPSMenuUserWidget::GetFPSGameInstance() const
{
	if (!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<UFPSGameInstance>();
}
