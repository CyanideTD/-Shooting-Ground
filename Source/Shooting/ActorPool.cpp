// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor * UActorPool::Pull()
{
	if (actor_pool.Num() == 0)
	{
		return nullptr;
	}

	return actor_pool.Pop(false);
}

void UActorPool::AddActor(AActor * actor)
{
	if (actor != NULL)
	{
		actor_pool.Push(actor);
	}
}
