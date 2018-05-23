// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class ATank;
class UTankBarrel;
class UTankTurret;

UENUM()
enum class EFiringState : uint8 { Locked, Aiming, Reloading};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankBarrel * Barrel = nullptr;
	UTankAimingComponent();
	void AimAt(FVector HitLocation, float LaunchSpeed);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Locked;

private:
	UTankTurret * Turret = nullptr;
	void MoveBarrelTurret(FVector AimDirection) const;
};
