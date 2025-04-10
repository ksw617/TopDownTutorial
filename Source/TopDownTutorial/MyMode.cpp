// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMode.h"
#include "MyPlayer.h"
#include "UObject/ConstructorHelpers.h"

AMyMode::AMyMode()
{

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
