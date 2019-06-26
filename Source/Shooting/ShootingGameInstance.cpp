// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameInstance.h"

UShootingGameInstance::UShootingGameInstance(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	difficulty = 0;
}

int UShootingGameInstance::GetDiffculty()
{
	return difficulty;
}

void UShootingGameInstance::SetDifficulty(int diff)
{
	if (diff >= 0 && diff < 3)
	{
		difficulty = diff;
	}
}

void UShootingGameInstance::ChangeDifficulty()
{
	difficulty = (difficulty + 1) % 3;
}
