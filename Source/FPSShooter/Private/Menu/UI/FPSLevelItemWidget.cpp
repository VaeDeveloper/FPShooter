// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/FPSLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UFPSLevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelSelectButton)
	{
		LevelSelectButton->OnClicked.AddDynamic(this, &UFPSLevelItemWidget::OnLevelItemClicked);
	}
}

void UFPSLevelItemWidget::OnLevelItemClicked()
{
	
	OnLevelSelected.Broadcast(LevelData);
}

void UFPSLevelItemWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if (LevelTextBlock)
	{
		LevelTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
	}

	if (LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelThumb);
	}
}

void UFPSLevelItemWidget::SetSelected(bool IsSelected)
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(IsSelected ?  ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}




