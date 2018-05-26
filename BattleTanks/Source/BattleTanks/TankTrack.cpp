// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTank()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxAcceleration * TankRoot->GetMass();
	FVector ForceLocation = GetComponentLocation();
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTank();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}
