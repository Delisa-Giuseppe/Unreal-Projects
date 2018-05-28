// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AProjectile();
	void Shoot(float Speed);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UProjectileMovementComponent * ProjectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent * CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent * LaunchBlast = nullptr;
	
};
