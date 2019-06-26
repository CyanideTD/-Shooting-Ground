// Fill out your copyright notice in the Description page of Project Settings.


#include "MeadowComponent.h"

// Sets default values for this component's properties
UMeadowComponent::UMeadowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMeadowComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SpawnGrass();
}


// Called every frame
void UMeadowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMeadowComponent::SpawnGrass()
{
	for (size_t i = 0; i < SpawnCount; i++)
	{
		FVector spawn_point = FMath::RandPointInBox(SpawningExtents);
		AddInstance(FTransform(spawn_point));
	}
}

