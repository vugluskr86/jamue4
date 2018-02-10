// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include<random>
#include<cmath>
#include<chrono>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "AsteroidClusterActor.generated.h"

USTRUCT(BlueprintType)
struct FAsteroidInstancedSpawnParamsCluster
{
   GENERATED_BODY()

   UPROPERTY(EditAnywhere) UStaticMesh* StaticMesh;
   UPROPERTY(EditAnywhere) UMaterial* Material;
   UPROPERTY(EditAnywhere) int32 MinAsteroid;
   UPROPERTY(EditAnywhere) int32 MaxAsteroid;
   UPROPERTY(EditAnywhere) float Radius;
   UPROPERTY(EditAnywhere) float MinScale;
   UPROPERTY(EditAnywhere) float MaxScale;
};

USTRUCT(BlueprintType)
struct FAsteroidActorSpawnParamsCluster
{
   GENERATED_BODY()

   UPROPERTY(EditAnywhere) TSubclassOf<class AActor> ActorClass;
   UPROPERTY(EditAnywhere) int32 MinAsteroid;
   UPROPERTY(EditAnywhere) int32 MaxAsteroid;
   UPROPERTY(EditAnywhere) float Radius;
   UPROPERTY(EditAnywhere) float MinScale;
   UPROPERTY(EditAnywhere) float MaxScale;
};

UCLASS()
class SPACECOWNEEDWATER_API AAsteroidClusterActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidClusterActor();

protected:  
   std::mt19937 generator;
   std::uniform_real_distribution<double> uniform01;

   FRotator FRandomRotator();

   void SpawnInstanced(const FAsteroidInstancedSpawnParamsCluster& params);
   void SpawnActors(const FAsteroidActorSpawnParamsCluster& params);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

   UPROPERTY(EditAnywhere) TArray<FAsteroidInstancedSpawnParamsCluster> InstancedSpawn;
   UPROPERTY(EditAnywhere) TArray<FAsteroidActorSpawnParamsCluster> ActorsSpawn;
   UFUNCTION(BlueprintCallable) void Spawn();
};
