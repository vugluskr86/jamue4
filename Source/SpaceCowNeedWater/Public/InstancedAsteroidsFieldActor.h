// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "InstancedAsteroidsFieldActor.generated.h"

USTRUCT(BlueprintType)
struct FAsteroidInstancedFieldDef_Properties
{
   GENERATED_BODY()

   UPROPERTY(EditAnywhere)
      int32 MinAsteroid;

   UPROPERTY(EditAnywhere)
      int32 MaxAsteroid;

   UPROPERTY(EditAnywhere)
      float MinScale;

   UPROPERTY(EditAnywhere)
      float MaxScale;

   UPROPERTY(EditAnywhere)
      bool InitRandomRotate;
};


USTRUCT(BlueprintType)
struct FAsteroidInstancedFieldDef_Cube
{
   GENERATED_BODY()

   UPROPERTY(EditAnywhere)
      UStaticMesh* AsteroidStaticMeshClass;


   UPROPERTY(EditAnywhere)
      FAsteroidInstancedFieldDef_Properties Properties;

   UPROPERTY(EditAnywhere)
      FVector Dimension;

   UPROPERTY(EditAnywhere)
      float Distance;

   UPROPERTY(EditAnywhere)
      float DistanceDisperse;
};

USTRUCT(BlueprintType)
struct FAsteroidInstancedFieldDef_Sphere
{
   GENERATED_BODY()

   UPROPERTY(EditAnywhere)
      UStaticMesh* AsteroidStaticMeshClass;

   UPROPERTY(EditAnywhere)
      FAsteroidInstancedFieldDef_Properties Properties;

   UPROPERTY(EditAnywhere)
      float Radius;

   UPROPERTY(EditAnywhere)
      float Distance;

   UPROPERTY(EditAnywhere)
      float Count;

   UPROPERTY(EditAnywhere)
      float DistanceDisperse;
};

USTRUCT(BlueprintType)
struct FAsteroidInstancedFieldDef_Torus
{
   GENERATED_BODY()

      UPROPERTY(EditAnywhere)
      UStaticMesh* AsteroidStaticMeshClass;

   UPROPERTY(EditAnywhere)
      FAsteroidInstancedFieldDef_Properties Properties;

   UPROPERTY(EditAnywhere)
      float Radius;

   UPROPERTY(EditAnywhere)
      float Radius2;

   UPROPERTY(EditAnywhere)
      float Distance;

   UPROPERTY(EditAnywhere)
      float Count;

   UPROPERTY(EditAnywhere)
      float DistanceDisperse;
};

UCLASS()
class SPACECOWNEEDWATER_API AInstancedAsteroidsFieldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInstancedAsteroidsFieldActor();

protected:
   TArray<UInstancedStaticMeshComponent*> InstancedStaticMeshes;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

   virtual void OnConstruction(const FTransform& Transform) override;

   void BuildCube(const FAsteroidInstancedFieldDef_Cube& options);
   void BuildSphere(const FAsteroidInstancedFieldDef_Sphere& options);
   void BuildTorus(const FAsteroidInstancedFieldDef_Torus& options);

   FRotator FRandomRotator();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

   UPROPERTY(EditAnywhere)
      TArray<FAsteroidInstancedFieldDef_Cube> CubeDefs;

   UPROPERTY(EditAnywhere) TArray<FAsteroidInstancedFieldDef_Sphere> SphereDefs;

   UPROPERTY(EditAnywhere) TArray<FAsteroidInstancedFieldDef_Torus> TorusDefs;
   
   UFUNCTION(BlueprintCallable) void Build();
};
