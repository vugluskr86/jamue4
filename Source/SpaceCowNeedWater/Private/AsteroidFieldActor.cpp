// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidFieldActor.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AAsteroidFieldActor::AAsteroidFieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAsteroidFieldActor::BeginPlay()
{
	Super::BeginPlay();
	
   Build();
}

// Called every frame
void AAsteroidFieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAsteroidFieldActor::Build()
{
   for (int i = 0; i < FieldDef.Num(); i++) {
      auto def = FieldDef[i];

      const int32 AsteroidCount = FMath::FRandRange(def.MinAsteroid, def.MaxAsteroid);

      UWorld* world = this->GetWorld();

     // UE_LOG(LogTemp, Log, TEXT("AAsteroidFieldActor::Build()"));

      for (int32 i = 0; i < AsteroidCount; i++) {
         FVector SpawnPosVector;
         SpawnPosVector.X = FMath::FRandRange(def.MinPosDispersion, def.MaxPosDispersion);
         SpawnPosVector.Y = FMath::FRandRange(def.MinPosDispersion, def.MaxPosDispersion);
         SpawnPosVector.Z = FMath::FRandRange(def.MinPosDispersion, def.MaxPosDispersion);

         float scale = FMath::FRandRange(def.MinScale, def.MaxScale);

         FVector ScaleVector;
         ScaleVector.X = scale * FMath::FRandRange(0.8, 1.2);
         ScaleVector.Y = scale * FMath::FRandRange(0.8, 1.2);
         ScaleVector.Z = scale * FMath::FRandRange(0.8, 1.2);

       //  UE_LOG(LogTemp, Log, TEXT("POS %f %f %f"), SpawnPosVector.X, SpawnPosVector.Y, SpawnPosVector.Z);

         FActorSpawnParameters SpawnInfo;
         SpawnInfo.Owner = this;

         // world->SpawnActor<AActor>(AsteroidActorClass, SpawnPosVector,)

         AActor* act = world->SpawnActor<AActor>(def.AsteroidActorClass, SpawnPosVector, FRotator(0, 0, 0), SpawnInfo);
         act->SetActorScale3D(ScaleVector);
      }
   }

}

