// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorPool.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnArgs
{
	GENERATED_USTRUCT_BODY()

public:
	FVector location;
	FRotator rotation;
	FVector scale;

	FSpawnArgs()
	{
		location = FVector(0.0);
		rotation = FRotator(0.0);
		scale = FVector(1.0);
	}

	FSpawnArgs(FVector l, FRotator r, FVector s) : location(l), rotation(r), scale(s) {}
};


UCLASS()
class SHOOTING_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Generate")
		void PlaceActor(TSubclassOf<AActor> spawned_type, int min_num = 1, int max_num = 1, float radius = 500, float min_scale = 1.0, float max_scale = 1.0);

	UFUNCTION(BlueprintCallable, Category = "Generate")
		void PlaceAIPawn(TSubclassOf<APawn> spawned_type, int min_num = 1, int max_num = 1);


	UFUNCTION(BlueprintCallable, Category = "Pool")
		void SetPool(UActorPool* pool);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	UPROPERTY(EditAnyWhere, Category = "Offset")
	FVector nav_mesh_volume_offset;

private:
	bool CanSpawnLocation(FVector location, float radius);
	bool GetEmptyLocation(float radius, FVector& result);
	void PlaceActor(TSubclassOf<AActor> spawned_type, FSpawnArgs& spawn_args);

private:
	UActorPool* NavMeshBoundVolumePool;
	AActor* nav_mesh_bound_volume;
	TArray<AActor*> actors_on_tile;
};
