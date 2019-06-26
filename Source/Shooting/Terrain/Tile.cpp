// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Engine\World.h"
#include "DrawDebugHelpers.h"
#include "NavMesh\NavMeshBoundsVolume.h"
#include "NavigationSystem.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Warning, TEXT("RETURN NAV MESH start"));
	if (nav_mesh_bound_volume != NULL && NavMeshBoundVolumePool != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("RETURN NAV MESH end"));
		NavMeshBoundVolumePool->AddActor(nav_mesh_bound_volume);
	}

	while (actors_on_tile.Num() != 0)
	{
		AActor* actor = actors_on_tile.Pop();
		if (actor != NULL)
		{
			actor->Destroy();
		}
	}
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActor(TSubclassOf<AActor> spawned_type, int min_num, int max_num, float radius, float min_scale, float max_scale)
{
	int spawn_num = FMath::RandRange(min_num, max_num);

	for (size_t i = 0; i < spawn_num; i++)
	{
		FVector spawn_point(0, 0, 0);
		float scale = FMath::FRandRange(min_scale, max_scale);
		if (GetEmptyLocation(radius * scale, spawn_point))
		{
			float rotation = FMath::FRandRange(-180, 180);
			FSpawnArgs args(spawn_point, FRotator(0, rotation, 0), FVector(scale));
			PlaceActor(spawned_type, args);
		}
	}
}

void ATile::PlaceAIPawn(TSubclassOf<APawn> spawned_type, int min_num, int max_num)
{
	int spawn_num = FMath::RandRange(min_num, max_num);
	for (size_t i = 0; i < spawn_num; i++)
	{
		FVector spawn_point(0, 0, 0);
		if (GetEmptyLocation(100, spawn_point))
		{
			APawn* spawned_actor = GetWorld()->SpawnActor<APawn>(spawned_type);
			spawned_actor->SetActorRelativeLocation(spawn_point);
			spawned_actor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
			spawned_actor->SpawnDefaultController();
			spawned_actor->Tags.Add(FName("Enemy"));
		}
	}

}

void ATile::SetPool(UActorPool * pool)
{
	NavMeshBoundVolumePool = pool;

	if (NavMeshBoundVolumePool != NULL)
	{
		AActor* nav_mesh = NavMeshBoundVolumePool->Pull();
		if (nav_mesh != NULL)
		{
			nav_mesh->SetActorLocation(GetActorLocation() + nav_mesh_volume_offset);
			nav_mesh_bound_volume = nav_mesh;
			FNavigationSystem::Build(*GetWorld());
		}
	}
}

bool ATile::CanSpawnLocation(FVector location, float radius)
{
	FHitResult result;

	FVector global_location = ActorToWorld().TransformPosition(location);

	bool has_hit = GetWorld()->SweepSingleByChannel(
		result,
		global_location,
		global_location + FVector(0, 0, 0.1),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(radius)
	);
	return !has_hit;
}

bool ATile::GetEmptyLocation(float radius, FVector& result)
{
	FVector min(0, -2000, 200);
	FVector max(4000, 2000, 200);
	FBox box(min, max);

	const int kMaxAttemp = 100;

	for (size_t i = 0; i < kMaxAttemp; i++)
	{
		FVector spawn_point = FMath::RandPointInBox(box);

		if (CanSpawnLocation(spawn_point, radius))
		{
			result = spawn_point;
			return true;
		}
	}

	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> spawned_type, FSpawnArgs& spawn_args)
{
	AActor* spawned_actor = GetWorld()->SpawnActor(spawned_type);
	spawned_actor->SetActorRelativeLocation(spawn_args.location);
	spawned_actor->SetActorRotation(spawn_args.rotation);
	spawned_actor->SetActorScale3D(spawn_args.scale);
	spawned_actor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	actors_on_tile.Push(spawned_actor);
}

