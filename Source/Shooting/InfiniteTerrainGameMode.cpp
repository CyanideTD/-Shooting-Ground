// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "ShootingGameMode.h"
#include "NavMesh\NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bound Volume Pool"));
	Difficulty = 0;
}

void AInfiniteTerrainGameMode::PopulateBoundVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> iter(GetWorld());

	while (iter)
	{
		AddToPool(*iter);
		++iter;
	}
}

void AInfiniteTerrainGameMode::ChangeDifficulty()
{
	Difficulty = (Difficulty + 1) % 3;
}

int AInfiniteTerrainGameMode::GetDifficulty()
{
	return Difficulty;
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* volume_to_add)
{
	if (volume_to_add != NULL)
	{
		NavMeshBoundVolumePool->AddActor(volume_to_add);
	}
}