// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootingGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API AInfiniteTerrainGameMode : public AShootingGameMode
{
	GENERATED_BODY()
	
public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundVolumePool();

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
	void ChangeDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
	int GetDifficulty();

private:
	void AddToPool(class ANavMeshBoundsVolume *volume_to_add);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nav Mesh Bounds Volume Pool")
	class UActorPool* NavMeshBoundVolumePool;

private:
	int Difficulty;
};
