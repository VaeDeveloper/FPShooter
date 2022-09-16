// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/FPSSettingOptionWidget.h"
#include "FPSGameSettings.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UFPSSettingOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(SettingDisplayName);
	check(SettingCurrentValue);
	check(NextSettingButton);
	check(PrevSettingButton);

	NextSettingButton->OnClicked.AddDynamic(this, &ThisClass::OnNextSetting);
	PrevSettingButton->OnClicked.AddDynamic(this, &ThisClass::OnPrevSetting);
}

void UFPSSettingOptionWidget::Init(UFPSGameSettings* InSetting)
{
	Setting = MakeWeakObjectPtr(InSetting);
	check(Setting.IsValid());

	UpdateTexts();
}

void UFPSSettingOptionWidget::UpdateTexts()
{
	if (Setting.IsValid())
	{
		SettingDisplayName->SetText(FText::FromString(Setting->GetName()));
		SettingCurrentValue->SetText(FText::FromString(Setting->GetCurrentOption().Name));
	}

}

void UFPSSettingOptionWidget::OnNextSetting()
{
	if (Setting.IsValid())
	{
		Setting->ApplyNextOption();
		SettingCurrentValue->SetText(FText::FromString(Setting->GetCurrentOption().Name));
	}
}

void UFPSSettingOptionWidget::OnPrevSetting()
{
	if (Setting.IsValid())
	{
		Setting->ApplyPrevOption();
		SettingCurrentValue->SetText(FText::FromString(Setting->GetCurrentOption().Name));
	}
}
