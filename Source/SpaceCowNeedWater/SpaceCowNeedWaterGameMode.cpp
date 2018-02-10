// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SpaceCowNeedWaterGameMode.h"
#include "SpaceCowNeedWaterPawn.h"
#include "ConstructorHelpers.h"

ASpaceCowNeedWaterGameMode::ASpaceCowNeedWaterGameMode()
{
   DefaultPawnClass = ASpaceCowNeedWaterPawn::StaticClass();
}
