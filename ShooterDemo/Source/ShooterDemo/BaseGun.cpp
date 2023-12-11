// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABaseGun::ABaseGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Set Mesh and attach it to Root
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AController* ABaseGun::GetOwnerController() const
{
	// Gun's owner pawn
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	// Return nullptr if OwnerPawn is nullptr
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}

	// Return OwnerPawn's controller
	return OwnerPawn->GetController();
}

bool ABaseGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	// Store result pointer of GetOwnerController
	AController* OwnerController = GetOwnerController();

	// Return false if OwnerController is nullptr
	if (OwnerController == nullptr)
	{
		return false;
	}

	// Location and rotation of the line trace's origin point
	FVector Location;
	FRotator Rotation;

	// Get the player's viewpoint at Location and Rotation
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location: (%f, %f)"), Location.X, Location.Y);

	// Set ShotDirection to the rotation vector pointing away from the origin point
	ShotDirection = -Rotation.Vector();

	// The end point vector of the line trace, which stops at MaxRange
	FVector End = Location + (-Rotation.Vector() * MaxRange);

	// Struct that defines parameters passed into line trace collision
	FCollisionQueryParams Params;

	// Ignore the BaseGun and the owning actor in the line trace
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	// Return true if the line trace reaches MaxRange
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_Camera, Params);
}

void ABaseGun::PullTrigger()
{
	// Store result pointer of GetOwnerController
	AController* OwnerController = GetOwnerController();
	// Return out of the function if MuzzleFlash is nullptr
	if (MuzzleFlash == nullptr)
	{
		return;
	}

	// Play MuzzleFlash effect
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	
	// Location and rotation of the line trace's origin point
	FVector Location;
	FRotator Rotation;

	// Get the player's viewpoint at Location and Rotation
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);

	if (bSuccess)
	{
		DrawDebugPoint(GetWorld(), Location, 20, FColor::Red, true);
	}
}

