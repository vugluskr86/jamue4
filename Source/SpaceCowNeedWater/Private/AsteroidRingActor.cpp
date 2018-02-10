// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidRingActor.h"
#include "Materials/MaterialInstanceDynamic.h"


// Sets default values
AAsteroidRingActor::AAsteroidRingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
   UInstancedStaticMeshComponent *ISMComp = NewObject<UInstancedStaticMeshComponent>(this);

   ISMComp->RegisterComponent();
   ISMComp->SetStaticMesh(options.StaticMesh);
   ISMComp->SetMaterial(0, UMaterialInstanceDynamic::Create(options.Material, this));
   ISMComp->SetFlags(RF_Transactional);
   
   const int32 AsteroidCount = FMath::FRandRange(options.MinAsteroid, options.MaxAsteroid);

   for (int32 i = 0; i < AsteroidCount; i++) {

      auto phi = FMath::FRandRange(0.0, 2.0 * PI);
      auto costheta = FMath::FRandRange(-1.0, 1.0);
      auto u = FMath::FRandRange(0.0, 1.0);

      auto theta = acos(costheta);
      auto r = options.Radius2 * u * u * u;

      auto x = (options.Radius + r * cos(theta)) * cos(phi);
      auto y = (options.Radius + r * cos(theta)) * sin(phi);
      auto z = r * sin(theta);

      auto scale = FMath::FRandRange(options.MinScale, options.MaxScale);

      const FVector ScaleVector(
         scale * FMath::FRandRange(0.8, 1.2),
         scale * FMath::FRandRange(0.8, 1.2),
         scale * FMath::FRandRange(0.8, 1.2)
      );
      const FRotator Rotator = FRandomRotator();
      const FVector SpawnPosVector(x, y, z);

      FTransform Transform(Rotator, SpawnPosVector, ScaleVector);
      ISMComp->AddInstance(Transform);
   }
}

void AAsteroidRingActor::SpawnActors(const FAsteroidActorsSpawnParamsRing& options)
{
   UWorld* world = this->GetWorld();
   const int32 AsteroidCount = FMath::FRandRange(options.MinAsteroid, options.MaxAsteroid);

   for (int32 i = 0; i < AsteroidCount; i++) {

      auto phi = FMath::FRandRange(0.0, 2.0 * PI);
      auto costheta = FMath::FRandRange(-1.0, 1.0);
      auto u = FMath::FRandRange(0.0, 1.0);

      auto theta = acos(costheta);
      auto r = options.Radius2 * u * u * u;

      auto x = (options.Radius + r * cos(theta)) * cos(phi);
      auto y = (options.Radius + r * cos(theta)) * sin(phi);
      auto z = r * sin(theta);

      auto scale = FMath::FRandRange(options.MinScale, options.MaxScale);

      const FVector ScaleVector(
         scale * FMath::FRandRange(0.8, 1.2),
         scale * FMath::FRandRange(0.8, 1.2),
         scale * FMath::FRandRange(0.8, 1.2)
      );
      const FVector SpawnPosVector(x, y, z);

      FActorSpawnParameters SpawnInfo;
      SpawnInfo.Owner = this;

      AActor* act = world->SpawnActor<AActor>(options.ActorClass, SpawnPosVector, FRotator(0, 0, 0), SpawnInfo);
      act->SetActorScale3D(ScaleVector);
   }
}