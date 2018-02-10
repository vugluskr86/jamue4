// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidClusterActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"


// Sets default values
AAsteroidClusterActor::AAsteroidClusterActor() 
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   generator = std::mt19937(seed);
   uniform01 = std::uniform_real_distribution<double>(0.0, 1.0);
}

// Called when the game starts or when spawned
void AAsteroidClusterActor::BeginPlay()
{
	Super::BeginPlay();
	
   Spawn();
}

// Called every frame
void AAsteroidClusterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsteroidClusterActor::Spawn()
{
   for (int i = 0; i < InstancedSpawn.Num(); i++) {
      auto def = InstancedSpawn[i];
      SpawnInstanced(def);
   }

   for (int i = 0; i < ActorsSpawn.Num(); i++) {
      auto def = ActorsSpawn[i];
      SpawnActors(def);
   }
}

FRotator AAsteroidClusterActor::FRandomRotator()
{
   const float pitch = FMath::FRandRange(-180.f, 180.f);
   const float yaw = FMath::FRandRange(-180.f, 180.f);
   const float roll = FMath::FRandRange(-180.f, 180.f);
   return FRotator(pitch, yaw, roll);
}

void AAsteroidClusterActor::SpawnInstanced(const FAsteroidInstancedSpawnParamsCluster& params)
{
   FTransform local = GetTransform();

   const int32 AsteroidCount = FMath::FRandRange(params.MinAsteroid, params.MaxAsteroid);

   if (AsteroidCount > 0) {

      UE_LOG(LogTemp, Log, TEXT("AAsteroidClusterActor::SpawnInstanced() %d"), AsteroidCount);

      UInstancedStaticMeshComponent *ISMComp = NewObject<UInstancedStaticMeshComponent>(this);

      ISMComp->RegisterComponent();
      ISMComp->SetStaticMesh(params.StaticMesh);
      ISMComp->SetMaterial(0, UMaterialInstanceDynamic::Create(params.Material, this));
      ISMComp->SetFlags(RF_Transactional);

      for (int32 i = 0; i < AsteroidCount; i++) {

         double theta = 2 * PI * uniform01(generator);
         double phi = PI * uniform01(generator);
         auto r = params.Radius * uniform01(generator);

         auto x = r * sin(theta) * cos(phi);
         auto y = r * sin(theta) * sin(phi);
         auto z = r * cos(theta);

         auto scale = FMath::FRandRange(params.MinScale, params.MaxScale);

         const FVector ScaleVector(
            scale * FMath::FRandRange(0.8, 1.2),
            scale * FMath::FRandRange(0.8, 1.2),
            scale * FMath::FRandRange(0.8, 1.2)
         );
         const FRotator Rotator = FRandomRotator();
         const FVector SpawnPosVector = local.GetTranslation() + FVector(x, y, z);


         FTransform Transform(Rotator, SpawnPosVector, ScaleVector);
         ISMComp->AddInstance(Transform);
      }
   }
}

void AAsteroidClusterActor::SpawnActors(const FAsteroidActorSpawnParamsCluster& params)
{
   FTransform local = GetTransform();
   const int32 AsteroidCount = FMath::FRandRange(params.MinAsteroid, params.MaxAsteroid);
   UWorld* world = this->GetWorld();

   if (AsteroidCount) {

      UE_LOG(LogTemp, Log, TEXT("AAsteroidClusterActor::SpawnActors() %d"), AsteroidCount);

      for (int32 i = 0; i < AsteroidCount; i++) {

         auto phi = FMath::FRandRange(0.0, 2.0 * PI);
         auto costheta = FMath::FRandRange(-1.0, 1.0);
         auto u = FMath::FRandRange(0.0, 1.0);

         auto theta = acos(costheta);
         auto r = params.Radius * u;

         auto x = r * sin(theta) * cos(phi);
         auto y = r * sin(theta) * sin(phi);
         auto z = r * cos(theta);

         auto scale = FMath::FRandRange(params.MinScale, params.MaxScale);

         const FVector ScaleVector(
            scale * FMath::FRandRange(0.8, 1.2),
            scale * FMath::FRandRange(0.8, 1.2),
            scale * FMath::FRandRange(0.8, 1.2)
         );
         const FVector SpawnPosVector = local.GetTranslation() + FVector(x, y, z);

         FActorSpawnParameters SpawnInfo;
         SpawnInfo.Owner = this;

         AActor* act = world->SpawnActor<AActor>(params.ActorClass, SpawnPosVector, FRotator(0, 0, 0), SpawnInfo);
         act->SetActorScale3D(ScaleVector);
      }
   }
}
