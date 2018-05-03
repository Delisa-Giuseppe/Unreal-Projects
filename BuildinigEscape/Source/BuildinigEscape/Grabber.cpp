// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Engine/World.h"

struct PlayerViewPoint
{
	FVector Location;
	FRotator Rotation;
};

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	GetInputComponent();
	GetPhysicsHandleComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerWP.Location, PlayerWP.Rotation);
	FVector Position = PlayerWP.Location + PlayerWP.Rotation.Vector() * Reach;
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(Position);
	}
		
}

void UGrabber::GetPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
		UE_LOG(LogTemp, Error, TEXT("Missing UPhysicsHandleComponent for the Actor : %s"), *GetOwner()->GetName());
}

void UGrabber::GetInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!Input)
		UE_LOG(LogTemp, Error, TEXT("Missing UInputComponent for the Actor : %s"), *GetOwner()->GetName());

	Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);

}

const FHitResult UGrabber::GrabberObject()
{
	FVector LineReachEnd = PlayerWP.Location + PlayerWP.Rotation.Vector() * Reach;

	FCollisionQueryParams CollisionParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit, PlayerWP.Location, LineReachEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), CollisionParams);
	return Hit;
}

void UGrabber::Grab()
{
	FHitResult Hit = GrabberObject();
	AActor * HitActor = Hit.GetActor();
	if (HitActor)
	{
		UPrimitiveComponent * ComponentToGrab = Hit.GetComponent();
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), ComponentToGrab->GetOwner()->GetActorRotation());
		//UE_LOG(LogTemp, Warning, TEXT("Collision Object : %s"), *ComponentToGrab->GetOwner()->GetName());
		//PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

