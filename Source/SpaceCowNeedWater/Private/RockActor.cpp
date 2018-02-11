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
   
   if (root) {
      FVector TorqueVector;
      TorqueVector.X = FMath::FRandRange(-100, 100);
      TorqueVector.Y = FMath::FRandRange(-100, 100);
      TorqueVector.Z = FMath::FRandRange(-100, 100);

      root->AddTorqueInRadians(TorqueVector, NAME_None, true);

      FVector ImpulseVector;
      ImpulseVector.X = FMath::FRandRange(1, 10);
      ImpulseVector.Y = FMath::FRandRange(1, 10);
      ImpulseVector.Z = FMath::FRandRange(1, 10);
      root->AddImpulse(ImpulseVector, NAME_None, true);
   }
}

// Called every frame
void ARockActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

   //UStaticMeshComponent* root = Cast<UStaticMeshComponent>(this->GetRootComponent());
   
   //FVector Origin;
   //root->AddRadialForce(GetActorLocation(), 100.f, 1000.f, ERadialImpulseFalloff::RIF_Constant, true);
}


void ARockActor::PostInitializeComponents()
{
   Super::PostInitializeComponents();
}
