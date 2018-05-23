// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!ensure(LeftTrackToSet) || !ensure(RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::MoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::TurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIMoveVelocity = MoveVelocity.GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(AIForwardVector, AIMoveVelocity);
	MoveForward(ForwardThrow);

	float TurnMovement = FVector::CrossProduct(AIForwardVector, AIMoveVelocity).Z;
	TurnRight(TurnMovement);
}

