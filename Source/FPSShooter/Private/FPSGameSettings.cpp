// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameSetting, All, All);


void UFPSGameSettings::SetName(const FString& InName)
{
    Name = InName;
}

void UFPSGameSettings::SetOption(const TArray<FSettingOption>& InOptions)
{
    Options = InOptions;
}

FSettingOption UFPSGameSettings::GetCurrentOption() const
{
    const int32 CurrentValue = GetCurrentValue();
    const auto Option = Options.FindByPredicate([&](const auto& Opt) {return CurrentValue == Opt.Value; });
    if (!Option)
    {
        UE_LOG(LogGameSetting, Error, TEXT("No option"));
        return FSettingOption{};
    }

    return *Option;
}

FString UFPSGameSettings::GetName() const
{
    return Name;
}

void UFPSGameSettings::AddGetter(TFunction<int32()> Func)
{
    Getter = Func;
}

void UFPSGameSettings::AddSetter(TFunction<void(int32)> Func)
{
    Setter = Func;
}

void UFPSGameSettings::ApplyNextOption()
{
    const int32 CurrentIndex = GetCurrentIndex();
    if (CurrentIndex == INDEX_NONE) return;

    const int32 NextIndex = (CurrentIndex + 1) % Options.Num();
    SetCurrentValue(Options[NextIndex].Value);
}

void UFPSGameSettings::ApplyPrevOption()
{
    const int32 CurrentIndex = GetCurrentIndex();
    if (CurrentIndex == INDEX_NONE) return;

    const int32 PrevIndex = CurrentIndex == 0 ? Options.Num() - 1 : CurrentIndex - 1;
    SetCurrentValue(Options[PrevIndex].Value);
}

int32 UFPSGameSettings::GetCurrentValue() const
{
    if (!Getter)
    {
        UE_LOG(LogGameSetting, Error, TEXT("Getter function is not set for %s"), *Name);

        return INDEX_NONE;
    }
    return Getter();
}

void UFPSGameSettings::SetCurrentValue(int32 Value)
{
    if (!Setter)
    {
        UE_LOG(LogGameSetting, Error, TEXT("Setter function is not set for %s"), *Name);

        return;
    }
    Setter(Value);
}

int32 UFPSGameSettings::GetCurrentIndex() const
{
    const int32 CurrentValue = GetCurrentValue();

    return Options.IndexOfByPredicate([&](const auto& Opt) {return CurrentValue == Opt.Value; });
}
