// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPSGoToMenuWidget.h"
#include "Components/Button.h"
#include "FPSGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UFPSGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UFPSGoToMenuWidget::OnGoToMenu);
	}
}

void UFPSGoToMenuWidget::OnGoToMenu()
{
	if (!GetWorld()) return;

	const auto FPSGameInstance = GetWorld()->GetGameInstance<UFPSGameInstance>();
	if (!FPSGameInstance) return;

	if (FPSGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("Error"));
		return;
	}



	UGameplayStatics::OpenLevel(this, FPSGameInstance->GetMenuLevelName());
}
