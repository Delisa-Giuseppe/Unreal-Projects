// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	float ClampedSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float ElevationChange = ClampedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float ClampedElevation = FMath::Clamp<float>(ElevationChange + RelativeRotation.Pitch, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}
