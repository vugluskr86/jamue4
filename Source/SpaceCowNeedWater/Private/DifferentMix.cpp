// Fill out your copyright notice in the Description page of Project Settings.

#include "DifferentMix.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

#include "RTTI.h"
#include "RockActor.h"

AGameModeBase* UDifferentMix::GameMode_ = nullptr;
UDifferentMix* UDifferentMix::Singeleton_ = nullptr;

ARockActor* UDifferentMix::RookActorpProt_ = nullptr;

UDifferentMix::UDifferentMix(const FObjectInitializer& ObjectInitializer)
   : Super(ObjectInitializer)
{
   if (UDifferentMix::Singeleton_ == nullptr) {
      UDifferentMix::RookActorpProt_ = RTTI::GetResouce<ARockActor>(TEXT("/Game/Blueprints/BP_RockActor"));

      UDifferentMix::Singeleton_ = this;
   }
}