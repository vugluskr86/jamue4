// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidRingActor.h"
#include "Materials/MaterialInstanceDynamic.h"

#include<random>
#include<cmath>
#include<chrono>

// Sets default values
AAsteroidRingActor::AAsteroidRingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   generator = std::mt19937(Seed);
   uniform01 = std::uniform_real_distribution<double>(0.0, 1.0);
}

// Called when the game starts or when spawned
void AAsteroidRingActor::BeginPlay()
{
	Super::BeginPlay();
	
   Spawn();
}

// Called every frame
void AAsteroidRingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FRotator AAsteroidRingActor::FRandomRotator()
{
   const float pitch = FMath::FRandRange(-180.f, 180.f);
   const float yaw = FMath::FRandRange(-180.f, 180.f);
   const float roll = FMath::FRandRange(-180.f, 180.f);
   return FRotator(pitch, yaw, roll);
}

void AAsteroidRingActor::Spawn()
{
   generator.seed(Seed);

   TArray<UInstancedStaticMeshComponent*> InstancedList;
   GetComponents(InstancedList);
   for (int i = 0; i < InstancedList.Num(); i++) {
      InstancedList[i]->DestroyComponent(true);
   }

   for (int i = 0; i < aAsteroidActors.Num(); i++) {
      aAsteroidActors[i]->Destroy();
   }

   aAsteroidActors.Empty();

   for (int i = 0; i < InstancedSpawn.Num(); i++) {
      auto def = InstancedSpawn[i];
      SpawnInstanced(def);
   }

   for (int i = 0; i < ActorsSpawn.Num(); i++) {
      auto def = ActorsSpawn[i];
      SpawnActors(def);
   }
}

void AAsteroidRingActor::SpawnInstanced(const FAsteroidInstancedSpawnParamsRing& options)
{
   FTransform local = GetTransform();

   UInstancedStaticMeshComponent *ISMComp = NewObject<UInstancedStaticMeshComponent>(this);

   ISMComp->RegisterComponent();
   ISMComp->SetStaticMesh(options.StaticMesh);
   ISMComp->SetMaterial(0, UMaterialInstanceDynamic::Create(options.Material, this));
   ISMComp->SetFlags(RF_Transactional);
   
   const int32 AsteroidCount = options.MinAsteroid + (options.MaxAsteroid * uniform01(generator));

   auto wallRadius = (options.OuterRadius - options.InnerRadius) * 0.5f;
   auto ringRadius = wallRadius + options.InnerRadius; // ( ( max - min ) / 2 ) + min


   for (int32 i = 0; i < AsteroidCount; i++) {
      auto scale = options.MinScale + (options.MaxScale * uniform01(generator));
      const FVector ScaleVector(scale, scale, scale);
      const FRotator Rotator = FRandomRotator();
      const FVector SpawnPosVector = local.GetTranslation() + GetRandomPositionInTorus(ringRadius, wallRadius);
      FTransform Transform(Rotator, SpawnPosVector, ScaleVector);
      ISMComp->AddInstance(Transform);
   }
}

FVector AAsteroidRingActor::GetRandomPositionInTorus(double ringRadius, double wallRadius)
{
   auto rndAngle = 6.28 * uniform01(generator);

   auto cX = sin(rndAngle);
   auto cZ = cos(rndAngle);

   FVector ringPos(cX, 0, cZ);
   ringPos *= ringRadius;

   double theta = 2 * PI * uniform01(generator);
   double phi = PI * uniform01(generator);

   auto x = sin(theta) * cos(phi);
   auto y = sin(theta) * sin(phi);
   auto z = cos(theta);

   FVector sPos = FVector(x, y, z) * wallRadius;

   return (ringPos + sPos);
}

void AAsteroidRingActor::SpawnActors(const FAsteroidActorsSpawnParamsRing& options)
{
   FTransform local = GetTransform();

   UWorld* world = this->GetWorld();
   const int32 AsteroidCount = options.MinAsteroid + (options.MaxAsteroid * uniform01(generator));

   auto wallRadius = (options.OuterRadius - options.InnerRadius) * 0.5f;
   auto ringRadius = wallRadius + options.InnerRadius;

   for (int32 i = 0; i < AsteroidCount; i++) {


      auto scale = options.MinScale + (options.MaxScale * uniform01(generator));

      const FVector ScaleVector(
         scale * (0.8 + (1.2 * uniform01(generator))),
         scale * (0.8 + (1.2 * uniform01(generator))),
         scale * (0.8 + (1.2 * uniform01(generator)))
      );
      const FVector SpawnPosVector = local.GetTranslation() + GetRandomPositionInTorus(ringRadius, wallRadius);

      FActorSpawnParameters SpawnInfo;
      SpawnInfo.Owner = this;

      AActor* act = world->SpawnActor<AActor>(options.ActorClass, SpawnPosVector, FRotator(0, 0, 0), SpawnInfo);
      act->SetActorScale3D(ScaleVector);
      aAsteroidActors.Add(act);
   }
}

#if WITH_EDITOR  
void AAsteroidRingActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
   Spawn();

   // Call the base class version  
   Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif