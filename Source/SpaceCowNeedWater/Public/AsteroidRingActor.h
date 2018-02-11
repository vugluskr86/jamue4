// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include<random>
#include<cmath>
#include<chrono>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "AsteroidRingActor.generated.h"


USTRUCT(BlueprintType)
struct FAsteroidInstancedSpawnParamsRing
{
   GENERATED_BODY()

   UPROPERTY(EditAnywhere) UStaticMesh* StaticMesh;
   UPROPERTY(EditAnywhere) UMaterial* Material;
   UPROPERTY(EditAnywhere) int32 MinAsteroid;
   UPROPERTY(EditAnywhere) int32 MaxAsteroid;
   UPROPERTY(EditAnywhere) float OuterRadius;
   UPROPERTY(EditAnywhere) float InnerRadius;
   UPROPERTY(EditAnywhere) float MinScale;
   UPROPERTY(EditAnywhere) float MaxScale;
};


USTRUCT(BlueprintType)
struct FAsteroidActorsSpawnParamsRing
{
   GENERATED_BODY()

   UPROPERTY(EditAnywhere) TSubclassOf<class AActor> ActorClass;
   UPROPERTY(EditAnywhere) int32 MinAsteroid;
   UPROPERTY(EditAnywhere) int32 MaxAsteroid;
   UPROPERTY(EditAnywhere) float OuterRadius;
   UPROPERTY(EditAnywhere) float InnerRadius;
   UPROPERTY(EditAnywhere) float MinScale;
   UPROPERTY(EditAnywhere) float MaxScale;
};

UCLASS()
class SPACECOWNEEDWATER_API AAsteroidRingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidRingActor();

protected:
   std::mt19937 generator;
   std::uniform_real_distribution<double> uniform01;

   FVector GetRandomPositionInTorus(double ringRadius, double wallRadius);

   TArray<AActor*> aAsteroidActors;
   FRotator FRandomRotator();

   void SpawnInstanced(const FAsteroidInstancedSpawnParamsRing& options);
   void SpawnActors(const FAsteroidActorsSpawnParamsRing& params);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR  
   virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

   UPROPERTY(EditAnywhere) FVector PivoiPos;
   UPROPERTY(EditAnywhere) int32 Seed;
   UPROPERTY(EditAnywhere) TArray<FAsteroidInstancedSpawnParamsRing> InstancedSpawn;
   UPROPERTY(EditAnywhere) TArray<FAsteroidActorsSpawnParamsRing> ActorsSpawn;
   UFUNCTION(BlueprintCallable) void Spawn();
};
