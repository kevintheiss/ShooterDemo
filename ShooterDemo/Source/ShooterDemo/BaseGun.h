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
};
