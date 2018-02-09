// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SpaceCowNeedWaterGameMode.h"
#include "SpaceCowNeedWaterPawn.h"
#include "ConstructorHelpers.h"

ASpaceCowNeedWaterGameMode::ASpaceCowNeedWaterGameMode()
{
	// set default pawn class to our flying pawn
	

		DefaultPawnClass = ASpaceCowNeedWaterPawn::StaticClass();
		//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/UFO.UFO"));
		//if (PlayerPawnBPClass.Succeeded()) DefaultPawnClass = PlayerPawnBPClass.Class;
}
