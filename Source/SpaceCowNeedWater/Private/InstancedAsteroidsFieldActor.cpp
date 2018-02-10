// Fill out your copyright notice in the Description page of Project Settings.

#include "InstancedAsteroidsFieldActor.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AInstancedAsteroidsFieldActor::AInstancedAsteroidsFieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInstancedAsteroidsFieldActor::BeginPlay()
{
	Super::BeginPlay();

   Build();
}

void AInstancedAsteroidsFieldActor::OnConstruction(const FTransform& Transform)
{
   Super::OnConstruction(Transform);

  // Build();
}

// Called every frame
void AInstancedAsteroidsFieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInstancedAsteroidsFieldActor::Build()
{
   UWorld* world = this->GetWorld();

   for (int i = 0; i < CubeDefs.Num(); i++) {

      auto def = CubeDefs[i];

     // const int32 AsteroidCount = FMath::FRandRange(def.Properties.MinAsteroid, def.Properties.MaxAsteroid);

     

      BuildCube(def);

    

     // for (int32 i = 0; i < AsteroidCount; i++) {}


      // UE_LOG(LogTemp, Log, TEXT("AAsteroidFieldActor::Build()"));

      /*
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
      */

   }

   for (int i = 0; i < SphereDefs.Num(); i++) {
      auto def = SphereDefs[i];

      // const int32 AsteroidCount = FMath::FRandRange(def.Properties.MinAsteroid, def.Properties.MaxAsteroid);
      
      BuildSphere(def);
   }

   for (int i = 0; i < TorusDefs.Num(); i++) {
      auto def = TorusDefs[i];

      // const int32 AsteroidCount = FMath::FRandRange(def.Properties.MinAsteroid, def.Properties.MaxAsteroid);

      BuildTorus(def);
   }
}

void AInstancedAsteroidsFieldActor::BuildCube(const FAsteroidInstancedFieldDef_Cube& options) 
{

   //FActorSpawnParameters SpawnInfo;
  // SpawnInfo.Owner = this;

   UInstancedStaticMeshComponent *ISMComp = NewObject<UInstancedStaticMeshComponent>(this);

  // UStaticMesh* mesh = NewObject<UStaticMesh>(options.AsteroidStaticMeshClass);

   ISMComp->RegisterComponent();
   ISMComp->SetStaticMesh(options.AsteroidStaticMeshClass);
   ISMComp->SetFlags(RF_Transactional);

   for (int32 x = 0; x < options.Dimension.X; x++) {
      for (int32 y = 0; y < options.Dimension.X; y++) {
         for (int32 z = 0; z < options.Dimension.Z; z++) {

            FVector SpawnPosVector;
            SpawnPosVector.X = x * options.Distance;
            SpawnPosVector.Y = y * options.Distance;
            SpawnPosVector.Z = z * options.Distance;

            FTransform Transform(SpawnPosVector);
                    
            ISMComp->AddInstance(Transform);
         }
      }
   }

   InstancedStaticMeshes.Add(ISMComp);
}

void AInstancedAsteroidsFieldActor::BuildSphere(const FAsteroidInstancedFieldDef_Sphere& options)
{
   UInstancedStaticMeshComponent *ISMComp = NewObject<UInstancedStaticMeshComponent>(this);

   ISMComp->RegisterComponent();
   ISMComp->SetStaticMesh(options.AsteroidStaticMeshClass);
   ISMComp->SetFlags(RF_Transactional);

   auto r_step = (options.Radius * 2.0f) / options.Count;
   for (int32 x = -options.Radius; x < options.Radius; x += r_step) {
      for (int32 y = -options.Radius; y < options.Radius; y += r_step) {
         for (int32 z = -options.Radius; z < options.Radius; z += r_step) {

            FVector SpawnPosVector;
            SpawnPosVector.X = x * options.Distance;
            SpawnPosVector.Y = y * options.Distance;
            SpawnPosVector.Z = z * options.Distance;

            if(x*x + y*y + z*z < options.Radius * options.Radius) {
              
               UE_LOG(LogTemp, Log, TEXT("POS %f %f %f"), SpawnPosVector.X, SpawnPosVector.Y, SpawnPosVector.Z);

               FTransform Transform(SpawnPosVector);

               ISMComp->AddInstance(Transform);
            }

         }
      }
   }

   InstancedStaticMeshes.Add(ISMComp);
}

void AInstancedAsteroidsFieldActor::BuildTorus(const FAsteroidInstancedFieldDef_Torus& options)
{
   UInstancedStaticMeshComponent *ISMComp = NewObject<UInstancedStaticMeshComponent>(this);

   ISMComp->RegisterComponent();
   ISMComp->SetStaticMesh(options.AsteroidStaticMeshClass);
   ISMComp->SetFlags(RF_Transactional);

   auto r_step = (options.Radius * 2.0f) / options.Count;
   for (int32 x = -options.Radius; x < options.Radius; x += r_step) {
      for (int32 y = -options.Radius; y < options.Radius; y += r_step) {
         for (int32 z = -options.Radius; z < options.Radius; z += r_step) {

            FVector SpawnPosVector;
            SpawnPosVector.X = x * options.Distance;
            SpawnPosVector.Y = y * options.Distance;
            SpawnPosVector.Z = z * options.Distance;

            auto xy = (sqrt(x*x + y*y) - options.Radius);
            auto left = xy * xy + z * z;

            if (left < options.Radius2 * options.Radius2) {

               UE_LOG(LogTemp, Log, TEXT("POS %f %f %f"), SpawnPosVector.X, SpawnPosVector.Y, SpawnPosVector.Z);

               FTransform Transform(SpawnPosVector);

               ISMComp->AddInstance(Transform);
            }

         }
      }
   }

   InstancedStaticMeshes.Add(ISMComp);
}