// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank * ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possesing a Tank"));
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("POSSESSED TANK : %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; };

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// De-project screen position of the crosshair into world direction
	FVector CameraWorldLocation;
	FVector LookDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
	{
		//Line-trace along that direction and check what hit
		FHitResult HitResult;
		FVector StartTrace = PlayerCameraManager->GetCameraLocation();
		FVector EndTrace = StartTrace + (LookDirection * LineTraceRange);
		
		if (GetWorld()->LineTraceSingleByChannel(
			HitResult,        //result
			StartTrace,    //start
			EndTrace, //end
			ECollisionChannel::ECC_Visibility
		))
		{
			HitLocation = HitResult.Location;
			return true;
		}
	}

	HitLocation = FVector(0);
	return false;
}
