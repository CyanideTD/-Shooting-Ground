// Fill out your copyright notice in the Description page of Project Settings.


#include "Mannquain.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMannquain::AMannquain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FPCamera->bUsePawnControlRotation = true;

	FPArm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	FPArm->SetOnlyOwnerSee(true);
	FPArm->SetupAttachment(FPCamera);
	FPArm->bCastDynamicShadow = false;
	FPArm->CastShadow = false;
	FPArm->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FPArm->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void AMannquain::BeginPlay()
{
	Super::BeginPlay();
	
	if (GunBlueprint == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing"));
		return;
	}
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);

	if (IsPlayerControlled())
	{
		Gun->AnimInstance = FPArm->GetAnimInstance();
		Gun->AttachToComponent(FPArm, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Gun->IsPlayer = true;
	}
	else
	{
		Gun->AnimInstance = GetMesh()->GetAnimInstance();
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Gun->IsPlayer = false;
	}

	if (InputComponent != NULL)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannquain::PullTrigger);
	}
}

void AMannquain::UnPossessed()
{
	Super::UnPossessed();
	if (Gun != NULL)
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
}

// Called every frame
void AMannquain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannquain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannquain::PullTrigger()
{
	Gun->OnFire();
}
