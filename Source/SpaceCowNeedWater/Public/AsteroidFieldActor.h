// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidFieldActor.generated.h"

UCLASS()
class SPACECOWNEEDWATER_API AAsteroidFieldActor : public AActor
{
   GENERATED_BODY()

   // TArray<AActor*> Actors_;
public:	
	// Sets default values for this actor's properties
	AAsteroidFieldActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

   UPROPERTY(EditAnywhere)
   TSubclassOf<class AActor> AsteroidActorClass;

   UPROPERTY(EditAnywhere)
   int32 MinAsteroid;

   UPROPERTY(EditAnywhere)
   int32 MaxAsteroid;

   UPROPERTY(EditAnywhere)
   float MinScale;

   UPROPERTY(EditAnywhere)
   float MaxScale;

   UPROPERTY(EditAnywhere)
   float MinPosDispersion;

   UPROPERTY(EditAnywhere)
   float MaxPosDispersion;
   
   UFUNCTION(BlueprintCallable)
   void Build(UWorld* world);
};
