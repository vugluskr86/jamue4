// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RockActor.generated.h"

UCLASS()
class SPACECOWNEEDWATER_API ARockActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockActor();

protected:
	
   FVector RotateImpulseVector;
   int32 _forceCouner;

   // Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

   virtual void PostInitializeComponents();
};
