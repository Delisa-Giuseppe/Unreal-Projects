// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

USTRUCT()
struct FMyPlayerViewPoint {

	GENERATED_USTRUCT_BODY()
	FVector Location;
	FRotator Rotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINIGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	FMyPlayerViewPoint PlayerWP;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPhysicsHandleComponent * PhysicsHandle = nullptr;
	UInputComponent * Input = nullptr;
	float Reach = 100.f;

	void GetPhysicsHandleComponent();
	void GetInputComponent();
	const FHitResult GrabberObject();
	void Grab();
	void Release();
};
