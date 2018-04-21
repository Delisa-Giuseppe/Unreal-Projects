// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();

	//AActor * owner = GetOwner();
	//FRotator rotator = FRotator(0.f, -60.f, 0.f);

	//FString rot = owner->GetActorRotation().ToString();

	//UE_LOG(LogTemp, Warning, TEXT("ROTATION : %s"), *rot);
	//owner->SetActorRotation(rotator);
	//rot = owner->GetActorRotation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("ROTATION : %s"), *rot);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	FRotator rotator = FRotator(0.f, -60.f, 0.f);
	owner->SetActorRotation(rotator);
}

void UOpenDoor::CloseDoor()
{
	FRotator rotator = FRotator(0.f, 0.f, 0.f);
	owner->SetActorRotation(rotator);
}

