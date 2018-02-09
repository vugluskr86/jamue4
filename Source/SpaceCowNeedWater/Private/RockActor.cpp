// Fill out your copyright notice in the Description page of Project Settings.

#include "RockActor.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ARockActor::ARockActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARockActor::BeginPlay()
{
	Super::BeginPlay();

   UStaticMeshComponent* root = Cast<UStaticMeshComponent>(this->GetRootComponent());
   
   FVector ImpulseVector;
   ImpulseVector.X = FMath::FRandRange(0.0, 100.0);
   ImpulseVector.Y = FMath::FRandRange(0.0, 100.0);
   ImpulseVector.Z = FMath::FRandRange(0.0, 100.0);

   root->AddTorque(ImpulseVector, NAME_None, true);
}

// Called every frame
void ARockActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

   UE_LOG(LogTemp, Log, TEXT("ARockActor::Tick()"));

   UStaticMeshComponent* root = Cast<UStaticMeshComponent>(this->GetRootComponent());
   
   FVector Origin;
   root->AddRadialForce(GetActorLocation(), 100.f, 1000.f, ERadialImpulseFalloff::RIF_Constant, true);
}

