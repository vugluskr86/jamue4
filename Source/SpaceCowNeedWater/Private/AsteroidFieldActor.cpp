// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidFieldActor.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AAsteroidFieldActor::AAsteroidFieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   AsteroidActorClass = nullptr;
   MinAsteroid = 10;
   MaxAsteroid = 100;
   MinScale = 0.1f;
   MaxScale = 10.0f;
   MinPosDispersion = 200.0f;
   MaxPosDispersion = 1000.0f;
}

// Called when the game starts or when spawned
void AAsteroidFieldActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsteroidFieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsteroidFieldActor::Build(UWorld* world)
{
   FVector SpawnPosVector;
   SpawnPosVector.X = FMath::FRandRange(MinPosDispersion, MaxPosDispersion);
   SpawnPosVector.Y = FMath::FRandRange(MinPosDispersion, MaxPosDispersion);
   SpawnPosVector.Z = FMath::FRandRange(MinPosDispersion, MaxPosDispersion);

   FVector ScaleVector;
   SpawnPosVector.X = FMath::FRandRange(MinScale, MaxScale);
   SpawnPosVector.Y = FMath::FRandRange(MinScale, MaxScale);
   SpawnPosVector.Z = FMath::FRandRange(MinScale, MaxScale);

   const int32 AsteroidCount = FMath::FRandRange(MinAsteroid, MaxAsteroid);

   for (int32 i = 0; i < AsteroidCount; i++) {
      //world->SpawnActor<AActor>(AsteroidActorClass, SpawnPosVector, FRotator(0, 0, 0), SpawnInfo);
   }
}

