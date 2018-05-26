// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDistancePlayer = 8000.f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	UTankAimingComponent * AimingComponent = nullptr;

};
