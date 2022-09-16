// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSGameSettings.generated.h"

USTRUCT()
struct FSettingOption
{
	GENERATED_BODY()

	FString Name;

	int32 Value;
};

UCLASS()
class FPSSHOOTER_API UFPSGameSettings : public UObject
{
	GENERATED_BODY()

public:
	void SetName(const FString& Name);
	void SetOption(const TArray<FSettingOption>& Option);


	FSettingOption GetCurrentOption() const;
	FString	GetName() const;
	void AddGetter(TFunction<int32()> Func);
	void AddSetter(TFunction<void(int32)> Func);

	void ApplyNextOption();
	void ApplyPrevOption();

private:
	FString Name;
	TArray<FSettingOption> Options;

	TFunction<int32()> Getter;
	TFunction<void(int32)> Setter;	

	int32 GetCurrentValue() const;
	void SetCurrentValue(int32 Value);
	int32 GetCurrentIndex() const;
};
