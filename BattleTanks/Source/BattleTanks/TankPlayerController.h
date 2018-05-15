// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

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

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = .5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = .33333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	ATank * GetControlledTank() const;
	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	
};
