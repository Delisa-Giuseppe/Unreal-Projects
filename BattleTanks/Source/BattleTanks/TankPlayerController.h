// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = .5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = .33333f;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;

	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;

protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
	ATank * GetControlledTank() const;
	UFUNCTION(BluePrintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent * AimingRef);
};
