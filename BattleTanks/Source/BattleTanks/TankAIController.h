// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float MaxDistancePlayer = 3000.f;

	virtual void Tick(float DeltaTime) override;

};
