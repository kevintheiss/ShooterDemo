// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterDemoGameMode.h"
#include "ShooterDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShooterDemoGameMode::AShooterDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
