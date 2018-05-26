// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankTurret.h"
#include "TankPlayerController.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet) || !ensure(TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

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
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTurret(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%f, aim solution found"), Time);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f, no aim solution found"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTurret(FVector AimDirection) const
{
	//ATankPlayerController * PlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	//FRotator CameraRotator = PlayerController->PlayerCameraManager->GetCameraLocation().ForwardVector.Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotation.Pitch);
	if (FMath::Abs(DeltaRotation.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotation.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotation.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(AimDirection, .35f);
}

void UTankAimingComponent::Fire()
{
	if (ensure(Barrel) && ensure(ProjectileBluePrint) && FiringState != EFiringState::Reloading)
	{
		AProjectile * Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->Shoot(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}


