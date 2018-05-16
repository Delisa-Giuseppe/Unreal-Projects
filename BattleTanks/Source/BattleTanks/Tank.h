// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeSeconds = 3.f;
	UTankAimingComponent * TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent * TankMovementComponent = nullptr;
	// Sets default values for this pawn's properties
	UPROPERTY(EditDefaultsOnly, Category = FireSystem)
	TSubclassOf<AProjectile> ProjectileBluePrint;
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel * BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret * TurretToSet);
	UFUNCTION(BlueprintCallable, Category = FireSystem)
	void Fire();

private:
	double LastFireTime = 0;
};
