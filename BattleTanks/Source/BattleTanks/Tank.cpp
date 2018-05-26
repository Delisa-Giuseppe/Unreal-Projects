// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UStaticMeshComponent * TankRoot = Cast<UStaticMeshComponent>(GetRootComponent());
	if (TankRoot)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Velocity: %s"), *TankRoot->GetPhysicsLinearVelocity().ToString());
		FVector ActualVelocity = TankRoot->GetPhysicsLinearVelocity();
		FVector ClampedVelocity = FVector(FMath::Clamp(ActualVelocity.X, -MaxSpeed, MaxSpeed), FMath::Clamp(ActualVelocity.Y, -MaxSpeed, MaxSpeed), FMath::Clamp(ActualVelocity.Z, -MaxSpeed, MaxSpeed / 6));
		TankRoot->SetPhysicsLinearVelocity(ClampedVelocity, false);
	}
}
