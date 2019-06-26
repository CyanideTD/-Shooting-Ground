// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/ShootingProjectile.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTING_API AGun : public AActor
{
	GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class USkeletalMeshComponent* FP_Gun;

    /** Location on gun mesh where projectiles should spawn. */
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class USceneComponent* FP_MuzzleLocation;

    /** Location on VR gun mesh where projectiles should spawn. */
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class USceneComponent* VR_MuzzleLocation;
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
  
public:
    /** Projectile class to spawn */
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<class AShootingProjectile> ProjectileClass;

    /** Sound to play each time we fire */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class USoundBase* FireSound;

    /** AnimMontage to play each time we fire */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class UAnimMontage* FPFireAnimation;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* TPFireAnimation;

	/** AnimMontage to play each time we fire */
	UPROPERTY()
	bool IsPlayer;

    /** Whether to use motion controller location for aiming. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    uint32 bUsingMotionControllers : 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    UAnimInstance* AnimInstance;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    /** Fires a projectile. */
    UFUNCTION(BlueprintCallable, Category = "Input")
    void OnFire();

};
