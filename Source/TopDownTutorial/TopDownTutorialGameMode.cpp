// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownTutorialGameMode.h"
#include "TopDownTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopDownTutorialGameMode::ATopDownTutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
