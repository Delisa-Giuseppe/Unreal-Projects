// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	float ClampedSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float RotationChange = ClampedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	//AddRelativeRotation(FRotator(0, RelativeRotation.Yaw + RotationChange, 0));
	SetRelativeRotation(FRotator(0, RelativeRotation.Yaw + RotationChange, 0));
}
