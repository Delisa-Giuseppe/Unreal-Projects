// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(AimingComponent)) { return; }

	MoveToActor(PlayerTank, MaxDistancePlayer);

	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	if(AimingComponent->GetFiringState() == EFiringState::Locked)
	AimingComponent->Fire();
}



