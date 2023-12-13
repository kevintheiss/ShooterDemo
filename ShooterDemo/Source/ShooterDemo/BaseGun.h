// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGun.generated.h"

UCLASS()
class SHOOTERDEMO_API ABaseGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGun();

	// Called when the player shoots
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Root scene component for attachments
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	// BaseGun skeletal mesh
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	// Particle system for muzzle flash effect
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	// Particle system for shot impact effect
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	// Maximum range of the gun
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	// Return the controller pointer for the gun's owner pawn
	AController* GetOwnerController() const;

	/*
	 * Checks the result of a line trace from the gun
	 * 
	 * @param	Hit  Out paramerter reference to the struct containing information about one hit of the trace
	 * @param	ShotDirection  Out parameter reference to the directional vector of the line trace
	 * @returns true if the line trace reaches its maximum range
	 */
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
};
