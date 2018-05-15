// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	float ClampedSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float RotationChange = ClampedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	//UE_LOG(LogTemp, Warning, TEXT("CHANGE : %f"), RotationChange);
	UE_LOG(LogTemp, Warning, TEXT("%f"), FMath::Abs(RelativeRotation.Yaw + RotationChange));
	//float ClampedRotation = FMath::Clamp<float>(RotationChange, 0, 360);
	SetRelativeRotation(FRotator(0, RelativeRotation.Yaw + RotationChange, 0));
}
