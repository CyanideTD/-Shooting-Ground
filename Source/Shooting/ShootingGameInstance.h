// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShootingGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API UShootingGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UShootingGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere, Category = "Difficulty")
	int difficulty;

public:
	UFUNCTION(BlueprintCallable, Category = "Difficulty")
	int GetDiffculty();

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
	void SetDifficulty(int diff);

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
	void ChangeDifficulty();

};
