// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SpaceCowNeedWaterGameMode.h"
#include "SpaceCowNeedWaterPawn.h"
#include "ConstructorHelpers.h"

#include "Public/DifferentMix.h"

ASpaceCowNeedWaterGameMode::ASpaceCowNeedWaterGameMode()
{
   DefaultPawnClass = ASpaceCowNeedWaterPawn::StaticClass();
//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/UFO.UFO"));
//if (PlayerPawnBPClass.Succeeded()) DefaultPawnClass = PlayerPawnBPClass.Class;

   UDifferentMix::Singeleton_ = NewObject<UDifferentMix>(UDifferentMix::StaticClass());

   UDifferentMix::GameMode_ = this;
}
