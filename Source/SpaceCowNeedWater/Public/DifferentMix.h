// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DifferentMix.generated.h"

class ARockActor;
class AGameModeBase;

/**
 * 
 */
UCLASS()
class SPACECOWNEEDWATER_API UDifferentMix : public UObject
{
	GENERATED_BODY()
   UDifferentMix(const FObjectInitializer& ObjectInitializer);

public:
   static ARockActor* RookActorpProt_;

   static UDifferentMix* Singeleton_;
   static AGameModeBase* GameMode_;

   static UDifferentMix* GetInstance()
   { return UDifferentMix::Singeleton_; }
};
