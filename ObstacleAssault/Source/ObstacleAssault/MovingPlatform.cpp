// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("Begin Play: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
	SetActorLocation(CurrentLocation);
	float PlatformDistanceToStart = FVector::Distance(StartLocation, CurrentLocation);

	if (PlatformDistanceToStart > MoveDistance)
	{
		float OverShoot = PlatformDistanceToStart - MoveDistance;
		FString Name = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s Total overshoot is: %f"), *Name, OverShoot);
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		// GetSafeNormal() -> just like i, j or k unit vectors. Have same direction but thedifferent is I set magnitude to 1 by GetSafeNormal() (birim vektör)
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
}