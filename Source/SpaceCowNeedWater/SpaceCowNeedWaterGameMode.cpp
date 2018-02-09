// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SpaceCowNeedWaterGameMode.h"
#include "SpaceCowNeedWaterPawn.h"

#include "Public/DifferentMix.h"

ASpaceCowNeedWaterGameMode::ASpaceCowNeedWaterGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ASpaceCowNeedWaterPawn::StaticClass();

   UDifferentMix::Singeleton_ = NewObject<UDifferentMix>(UDifferentMix::StaticClass());

   UDifferentMix::GameMode_ = this;
}
