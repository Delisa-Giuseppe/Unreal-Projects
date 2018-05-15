// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }

	FVector LaunchVelocity;
	float Time = GetWorld()->GetTimeSeconds();
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTurret(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%f, aim solution found"), Time);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f, no aim solution found"), Time);
	}
}

void UTankAimingComponent::SetBarrel(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurret(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTurret(FVector AimDirection) const
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Rotate(DeltaRotation.Yaw);
}

