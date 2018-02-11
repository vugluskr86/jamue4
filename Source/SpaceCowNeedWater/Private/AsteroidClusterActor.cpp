// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidClusterActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"


// Sets default values
AAsteroidClusterActor::AAsteroidClusterActor() : Seed(0), PivoiPos(0,0,0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   generator = std::mt19937(Seed);
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
   generator.seed(Seed);

   TArray<UInstancedStaticMeshComponent*> InstancedList;
   GetComponents(InstancedList);
   for (int i = 0; i < InstancedList.Num(); i++) {
      if (InstancedList[i]) {
         InstancedList[i]->DestroyComponent(false);
      }
   }

   for (int i = 0; i < aAsteroidActors.Num(); i++) {
      if (aAsteroidActors[i]) {
         aAsteroidActors[i]->Destroy();
      }
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

FRotator AAsteroidClusterActor::FRandomRotator()
{
   const float pitch = FMath::FRandRange(-180.f, 180.f);
   const float yaw = FMath::FRandRange(-180.f, 180.f);
   const float roll = FMath::FRandRange(-180.f, 180.f);
   return FRotator(pitch, yaw, roll);
}

void AAsteroidClusterActor::SpawnInstanced(const FAsteroidInstancedSpawnParamsCluster& params)
{
 
   const int32 AsteroidCount = params.MinAsteroid + (params.MaxAsteroid * uniform01(generator));
   
   if (AsteroidCount > 0) {

      UE_LOG(LogTemp, Log, TEXT("AAsteroidClusterActor::SpawnInstanced() %d"), AsteroidCount);

      UInstancedStaticMeshComponent *ISMComp = NewObject<UInstancedStaticMeshComponent>(this);
      
   //   ISMComp->SetWorldTransform(local);
      
      ISMComp->RegisterComponent();
      ISMComp->SetStaticMesh(params.StaticMesh);
      ISMComp->SetMaterial(0, UMaterialInstanceDynamic::Create(params.Material, this));
      ISMComp->SetFlags(RF_Transactional);
   
      for (int32 i = 0; i < AsteroidCount; i++) {

         double theta = 2 * PI * uniform01(generator);
         double phi = PI * uniform01(generator);
         auto r = (params.Radius * 0.1) + params.Radius * uniform01(generator);

         auto x = r * sin(theta) * cos(phi);
         auto y = r * sin(theta) * sin(phi);
         auto z = r * cos(theta);

         auto scale = params.MinScale + (params.MaxScale * uniform01(generator)); 

         const FVector ScaleVector(
            scale * (0.8 + (1.2 * uniform01(generator))),
            scale * (0.8 + (1.2 * uniform01(generator))),
            scale * (0.8 + (1.2 * uniform01(generator)))
         );
         const FRotator Rotator = FRandomRotator();
         const FVector SpawnPosVector = PivoiPos + FVector(x, y, z);


         FTransform Transform(Rotator, SpawnPosVector, ScaleVector);
         ISMComp->AddInstance(Transform);
      }
   }
}

void AAsteroidClusterActor::SpawnActors(const FAsteroidActorSpawnParamsCluster& params)
{
   FTransform local = GetTransform();
   const int32 AsteroidCount = params.MinAsteroid + (params.MaxAsteroid * uniform01(generator));
   UWorld* world = this->GetWorld();

   if (AsteroidCount) {

      UE_LOG(LogTemp, Log, TEXT("AAsteroidClusterActor::SpawnActors() %d"), AsteroidCount);

      for (int32 i = 0; i < AsteroidCount; i++) {

         double theta = 2 * PI * uniform01(generator);
         double phi = PI * uniform01(generator);
         auto r = (params.Radius * 0.1) + params.Radius * uniform01(generator);

         auto x = r * sin(theta) * cos(phi);
         auto y = r * sin(theta) * sin(phi);
         auto z = r * cos(theta);

         auto scale = params.MinScale + (params.MaxScale * uniform01(generator));

         const FVector ScaleVector(
            scale * (0.8 + (1.2 * uniform01(generator))),
            scale * (0.8 + (1.2 * uniform01(generator))),
            scale * (0.8 + (1.2 * uniform01(generator)))
         );
         const FVector SpawnPosVector = PivoiPos + FVector(x, y, z);

         FActorSpawnParameters SpawnInfo;
         SpawnInfo.Owner = this;
        
         AActor* act = world->SpawnActor<AActor>(params.ActorClass, SpawnPosVector, FRotator(0, 0, 0), SpawnInfo);
         act->SetActorScale3D(ScaleVector);
         aAsteroidActors.Add(act);
      }
   }
}

void AAsteroidClusterActor::PostInitializeComponents()
{
   Super::PostInitializeComponents();

   UE_LOG(LogTemp, Log, TEXT("AAsteroidClusterActor::PostInitializeComponents()"));
}

void AAsteroidClusterActor::OnConstruction(const FTransform& transform)
{
   Super::OnConstruction(transform);
}

#if WITH_EDITOR  
void AAsteroidClusterActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
   Spawn();

   // Call the base class version  
   Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif