// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/FPSAnimNotify.h"



void UFPSAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}