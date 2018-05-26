// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class ATank;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringState : uint8 { Locked, Aiming, Reloading};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankBarrel * Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeSeconds = 3.f;

	UTankAimingComponent();
	
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	// Sets default values for this pawn's properties
	UPROPERTY(EditDefaultsOnly, Category = FireSystem)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = FireSystem)
	void Fire();

	EFiringState GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;

private:

	double LastFireTime = 0;
	FVector AimDirection;
	UTankTurret * Turret = nullptr;
	void MoveBarrelTurret(FVector AimDirection) const;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	bool IsBarrelMoving() const;
};
